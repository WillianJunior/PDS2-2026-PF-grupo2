#include "Interface.hpp"
#include "Smarthome.hpp"
#include <iostream>

Interface::Interface() : sistemaLogin(std::vector<Conta>()) {
    Conta adminTeste("1", "Administrador", "admin@smarthome.com", "12345678", true);
    sistemaLogin.criarConta(adminTeste);
}

void Interface::iniciar() {
    std::cout << "======================================\n";
    std::cout << "   BEM-VINDO AO SISTEMA SMARTHOME\n";
    std::cout << "======================================\n";

    while (true) {
        if (usuarioLogado == nullptr) {
            exibirMenuInicial();
        } else {
            exibirMenuConta();
        }
    }
}

void Interface::exibirMenuInicial() {
    std::cout << "\n======================================\n";
    std::cout << "          MENU INICIAL - LOGIN        \n";
    std::cout << "======================================\n";
    std::cout << "1. Entrar (Login)\n";
    std::cout << "2. Cadastrar Nova Conta\n";
    std::cout << "3. Sair do Programa\n";
    std::cout << "Escolha uma opcao: ";

    int opcao;
    if (!(std::cin >> opcao)) {
        std::cin.clear();
        std::string lixo;
        std::getline(std::cin, lixo);
        std::cout << "Opcao invalida! Digite apenas numeros.\n";
        return;
    }
    std::cin.ignore();

    switch (opcao) {
        case 1:
            std::cout << "\nDirecionando para Login...\n";
            realizarLogin();
            break;
        case 2:
            std::cout << "\nDirecionando para Cadastro de Nova Conta...\n";
            cadastrarConta();
            break;
        case 3:
            std::cout << "\nEncerrando o sistema. Ate breve!\n";
            exit(0);
        default:
            std::cout << "\nOpcao invalida! Escolha 1, 2 ou 3.\n";
            break;
    }
}

void Interface::exibirMenuConta() {
    std::cout << "\n======================================\n";
    std::cout << "   PAINEL DA CONTA [" << usuarioLogado->getNome() << "]\n";
    std::cout << "======================================\n";
    std::cout << "1. Criar nova Smarthome\n";
    std::cout << "2. Acessar minhas Smarthomes\n";
    std::cout << "3. Fazer Logout\n";
    std::cout << "Escolha uma opcao: ";
    
    int op;
    if (!(std::cin >> op)) {
        std::cin.clear();
        std::string lixo;
        std::getline(std::cin, lixo);
        std::cout << "Opcao invalida! Digite apenas numeros.\n";
        return;
    }
    std::cin.ignore();
    
    switch (op) {
        case 1: {
            if (!usuarioLogado->isPerfilAdulto()) {
                std::cout << "\n[ACESSO NEGADO] Controle Parental: Perfis infantis nao podem criar Smarthomes.\n";
                break;
            }

            std::string nomeCasa;
            bool sucesso = false;
            int tentativas = 0;
            while (!sucesso && tentativas < 3) {
                std::cout << "\nDigite o nome da sua nova Smarthome: ";
                std::getline(std::cin, nomeCasa);

                std::string idGerado = std::to_string(rand() % 10000);

                try {
                    usuarioLogado->criarSmarthome(idGerado, nomeCasa);
                    std::cout << "Smarthome '" << nomeCasa << "' criada com sucesso!\n";
                    sucesso = true;
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Erro: " << e.what() << "\n";
                    std::cerr << "Tentativa " << (tentativas+1) << " falhou. Tente novamente...\n";
                    tentativas++;
                }
                catch (...) {
                    std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                }
            }

            if (!sucesso) {
                std::cerr << "Falha após 3 tentativas.\n";
            }
            break;
        }
        case 2:
            exibirMenuSmarthome();
            break;
        case 3:
            usuarioLogado.reset();
            std::cout << "\nLogout efetuado com sucesso.\n";
            break;
        default:
            std::cout << "\nOpcao invalida! Escolha 1, 2 ou 3.\n";
            break;
    }
}

void Interface::exibirMenuSmarthome() {
    std::cout << "\n======================================\n";
    std::cout << "          MINHAS SMARTHOMES\n";
    std::cout << "======================================\n";

    std::vector<Smarthome*> casas = usuarioLogado->getSmarthomes();

    if (casas.empty()) {
        std::cout << "Voce ainda nao possui nenhuma Smarthome cadastrada.\n";
        std::cout << "Retornando ao menu anterior...\n";
        return;
    }

    for (size_t i = 0; i < casas.size(); i++) {
        std::cout << i + 1 << ". " << casas[i]->getNome() << "\n";
    }
    
    int opcaoVoltar = casas.size() + 1;
    std::cout << opcaoVoltar << ". Voltar ao Menu Anterior\n";
    std::cout << "Escolha uma casa para acessar (ou " << opcaoVoltar << " para voltar): ";

    int op;
    if (!(std::cin >> op)) {
        std::cin.clear();
        std::string lixo;
        std::getline(std::cin, lixo);
        std::cout << "Opcao invalida! Digite apenas numeros.\n";
        return;
    }
    std::cin.ignore();

    if (op == opcaoVoltar) {
        return;
    } else if (op > 0 && op <= (int)casas.size()) {
        Smarthome* casaEscolhida = casas[op - 1];
        
        std::cout << "\n[Entrando na casa: " << casaEscolhida->getNome() << " ...]\n";
        
        gerenciarSmarthome(casaEscolhida); 
    } else {
        std::cout << "\nOpcao invalida!\n";
    }
}

void Interface::realizarLogin() {
    std::string email, senha;

    std::cout << "\n--- TELA DE LOGIN ---\n";
    std::cout << "Digite seu e-mail: ";
    std::getline(std::cin, email);
    std::cout << "Digite sua senha: ";
    std::getline(std::cin, senha);

    if (sistemaLogin.autenticarConta(email, senha)) {
        std::cout << "\nLogin realizado com sucesso!\n";
        
        std::vector<Conta> lista = sistemaLogin.getContasCadastradas();
        for (size_t i = 0; i < lista.size(); i++) {
            if (lista[i].getEmail() == email) {
                usuarioLogado = std::make_unique<Conta>(lista[i]);
                break;
            }
        }
        std::cout << "Bem-vindo(a), " << usuarioLogado->getNome() << "!\n";
    } else {
        std::cout << "\nErro de autenticacao! E-mail ou senha incorretos ou conta bloqueada.\n";
    }
}

void Interface::cadastrarConta() {
    std::string id, nome, email, senha;
    char tipoPerfil;
    bool ehAdulto = true;

    std::cout << "\n--- CADASTRO DE NOVA CONTA ---\n";
    std::cout << "ID unico da conta: ";
    std::getline(std::cin, id);
    std::cout << "Nome completo: ";
    std::getline(std::cin, nome);
    std::cout << "E-mail de acesso: ";
    std::getline(std::cin, email);
    std::cout << "Senha de acesso: ";
    std::getline(std::cin, senha);
    std::cout << "Tipo de perfil - Adulto ou Infantil? (A/I): ";
    std::cin >> tipoPerfil;
    std::cin.ignore();

    if (tipoPerfil == 'i' || tipoPerfil == 'I') {
        ehAdulto = false;
    }

    Conta novaConta("", "", "", "", true);

    try {
        novaConta = Conta(id, nome, email, senha, ehAdulto);
    } 
    catch (const std::invalid_argument& e) {
        std::cerr << "Erro ao criar conta: " << e.what() << "\n";
        return;
    } catch (...) {
        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
    }

    if (!novaConta.validarFormatoEmail()) {
        std::cout << "\nErro no cadastro: Formato de e-mail invalido (deve conter '@').\n";
        return;
    }

    if (!novaConta.validarSenha()) {
        std::cout << "\nErro no cadastro: A senha precisa ter pelo menos 8 caracteres.\n";
        return;
    }

    sistemaLogin.criarConta(novaConta);
    std::cout << "\nConta cadastrada com sucesso! Voce ja pode entrar no sistema.\n";
}

void Interface::gerenciarSmarthome(Smarthome* casa) {
    while (true) {
        std::cout << "\n======================================\n";
        std::cout << "   GERENCIANDO: " << casa->getNome() << "\n";
        std::cout << "======================================\n";
        std::cout << "1. Gerenciar Comodos (Adicionar/Remover)\n";
        std::cout << "2. Gerenciar Modos da Casa\n";
        std::cout << "3. Criar Casa Padrao\n";
        std::cout << "4. Mostrar Planta da Casa\n";
        std::cout << "5. Relatorio de Consumo de Energia\n";
        std::cout << "6. Voltar para Minhas Smarthomes\n";
        std::cout << "Escolha uma opcao: ";

        int op;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::string lixo;
            std::getline(std::cin, lixo);
            std::cout << "Opcao invalida! Digite apenas numeros.\n";
            continue;
        }
        std::cin.ignore();

        switch (op) {
            case 1:
                exibirMenuComodos(casa);
                break;

            case 2:
                exibirMenuModos(casa);
                break;

            case 3:
                criarCasaPadrao(casa);
                break;

            case 4:
                mostrarPlantaCasa(casa);
                break;

            case 5: {
                std::cout << "\n--- RELATORIO DE ENERGIA ---\n";
                float consumoTotal = usuarioLogado->gerarRelatorioDeEnergia(casa);

                std::cout << "Consumo medio total da casa '" << casa->getNome() << "': "
                          << consumoTotal << " kWh\n";
                std::cout << "----------------------------\n";
                break;
            }

            case 6:
                std::cout << "\nSaindo da casa " << casa->getNome() << "...\n";
                return;

            default:
                std::cout << "\nOpcao invalida! Escolha de 1 a 6.\n";
                break;
        }
    }
}

void Interface::exibirMenuComodos(Smarthome* casa) {
    while (true) {
        std::cout << "\n--- GERENCIAR COMODOS [" << casa->getNome() << "] ---\n";
        std::cout << "1. Listar Comodos\n";
        std::cout << "2. Adicionar novo Comodo\n";
        std::cout << "3. Remover Comodo\n";
        std::cout << "4. Acessar um Comodo Especifico\n";
        std::cout << "5. Voltar\n";
        std::cout << "Escolha uma opcao: ";
        int op;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::string lixo;
            std::getline(std::cin, lixo);
            std::cout << "Opcao invalida! Digite apenas numeros.\n";
            continue;
        }
        std::cin.ignore();

        switch (op) {
            case 1:
                std::cout << "\n[Lista de Comodos]\n";
                if (casa->getQuantidadeComodos() == 0) {
                    std::cout << "Nenhum comodo cadastrado nesta casa.\n";
                } else {
                    casa->printComodosInfo();
                }
                break;
            case 2: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Apenas adultos podem adicionar comodos.\n";
                    break;
                }
                std::string nomeComodo;
                bool sucesso = false;
                int tentativas = 0;

                while (!sucesso && tentativas < 3) {
                    std::cout << "Digite o nome do novo comodo (ex: Sala de Estar): ";
                    std::getline(std::cin, nomeComodo);

                    try {
                        usuarioLogado->criarComodo(casa, nomeComodo);
                        std::cout << "Comodo '" << nomeComodo << "' criado com sucesso!\n";
                        sucesso = true;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Erro: " << e.what() << "\n";
                        std::cerr << "Tentativa " << (tentativas+1) << " falhou. Tente novamente...\n";
                        tentativas++;
                    } catch (...) {
                        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha após 3 tentativas.\n";
                }

                break;
            }
            case 3: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Apenas adultos podem remover comodos.\n";
                    break;
                }
                std::string nomeComodo;
                std::cout << "Digite o nome do comodo a ser removido: ";
                std::getline(std::cin, nomeComodo);
                try {
                    usuarioLogado->apagarComodo(casa, nomeComodo);
                    std::cout << "Comando de remocao executado.\n";
                }
                catch(std::invalid_argument& e) {
                    std::cerr << "Erro: " << e.what() << '\n';
                } catch (...) {
                    std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                }
                
                break;
            }
            case 4: {
                std::string nomeComodo;
                std::cout << "Digite o nome exato do comodo que deseja acessar: ";
                std::getline(std::cin, nomeComodo);
                
                Comodo* comodoEncontrado = casa->getComodo(nomeComodo);
                
                if (comodoEncontrado != nullptr) {
                    gerenciarComodoEspecifico(casa, comodoEncontrado);
                } else {
                    std::cout << "Comodo '" << nomeComodo << "' nao encontrado!\n";
                }
                break;
            }
            case 5:
                return;
            default:
                std::cout << "Opcao invalida! Escolha de 1 a 5.\n";
                break;
        }
    }
}

void Interface::gerenciarComodoEspecifico(Smarthome* casa, Comodo* comodo) {
    while (true) {
        std::cout << "\n--- DENTRO DE: " << comodo->getNome() << " ---\n";
        std::cout << "1. Adicionar Objeto Inteligente (Lâmpada, TV, etc)\n";
        std::cout << "2. Remover Objeto Inteligente\n";
        std::cout << "3. Adicionar Sensor\n";
        std::cout << "4. Remover Sensor\n";
        std::cout << "5. Listar Dispositivos neste Comodo\n";
        std::cout << "6. Voltar para Menu da Casa\n";
        std::cout << "Escolha uma opcao: ";

        int op;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::string lixo;
            std::getline(std::cin, lixo);
            std::cout << "Opcao invalida! Digite apenas numeros.\n";
            continue;
        }
        std::cin.ignore();

        switch (op) {
            case 1: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Nao e permitido adicionar objetos.\n";
                    break;
                }
                std::string nomeObjeto;
                bool sucesso = false;
                int tentativas = 0;

                while (!sucesso && tentativas < 3) {
                    std::cout << "Digite o nome do novo objeto (ex: Lampada): ";
                    std::getline(std::cin, nomeObjeto);

                    try {
                        usuarioLogado->criarObjeto(casa, comodo, nomeObjeto);
                        std::cout << "Objeto '" << nomeObjeto << "' adicionado com sucesso!\n";
                        sucesso = true;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Erro: " << e.what() << "\n";
                        std::cerr << "Tentativa " << (tentativas+1) << " falhou. Tente novamente...\n";
                        tentativas++;
                    } catch (...) {
                        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha após 3 tentativas.\n";
                }

                break;
            }
            case 2: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Nao e permitido remover objetos.\n";
                    break;
                }
                std::string nomeObjeto;
                std::cout << "Digite o nome do objeto a ser removido: ";
                std::getline(std::cin, nomeObjeto);
                try {
                    usuarioLogado->apagarObjeto(casa, comodo, nomeObjeto);
                    std::cout << "Comando de remocao executado.\n";
                }
                catch(std::invalid_argument& e) {
                    std::cerr << "Erro: " << e.what() << '\n';
                } catch (...) {
                    std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                }
                break;
            }
            case 3: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Nao e permitido adicionar sensores.\n";
                    break;
                }
                std::string nomeSensor;
                bool sucesso = false;
                int tentativas = 0;

                while (!sucesso && tentativas < 3) {
                    std::cout << "Digite o nome do novo sensor (ex: Sensor de Presenca): ";
                    std::getline(std::cin, nomeSensor);

                    try {
                        usuarioLogado->criarSensor(casa, comodo, nomeSensor);
                        std::cout << "Sensor '" << nomeSensor << "' adicionado com sucesso!\n";
                        sucesso = true;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Erro: " << e.what() << "\n";
                        std::cerr << "Tentativa " << (tentativas+1) << " falhou. Tente novamente...\n";
                        tentativas++;
                    } catch (...) {
                        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha após 3 tentativas.\n";
                }
                break;
            }
            case 4: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Nao e permitido remover sensores.\n";
                    break;
                }
                std::string nomeSensor;
                std::cout << "Digite o nome do sensor a ser removido: ";
                std::getline(std::cin, nomeSensor);
                try {
                    usuarioLogado->apagarSensor(casa, comodo, nomeSensor);
                    std::cout << "Comando de remocao executado.\n";
                }
                catch(std::invalid_argument& e) {
                    std::cerr << "Erro: " << e.what() << '\n';
                } catch (...) {
                    std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                }
                break;
            }
            case 5:
                std::cout << "\n[Dispositivos em " << comodo->getNome() << "]\n";
                comodo->printObjetosInfo();
                comodo->printSensoresInfo();
                break;
            case 6:
                return;
            default:
                std::cout << "Opcao invalida! Escolha de 1 a 6.\n";
                break;
        }
    }
}

void Interface::exibirMenuModos(Smarthome* casa) {
    while (true) {
        std::cout << "\n--- GERENCIAR MODOS [" << casa->getNome() << "] ---\n";
        std::cout << "1. Listar Modos da Casa\n";
        std::cout << "2. Criar novo Modo\n";
        std::cout << "3. Remover Modo\n";
        std::cout << "4. Acessar um Modo Especifico\n";
        std::cout << "5. Voltar\n";
        std::cout << "Escolha uma opcao: ";

        int op;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::string lixo;
            std::getline(std::cin, lixo);
            std::cout << "Opcao invalida! Digite apenas numeros.\n";
            continue;
        }
        std::cin.ignore();

        switch (op) {
            case 1:
                std::cout << "\n[Lista de Modos]\n";
                if (casa->getQuantidadeModos() == 0) {
                    std::cout << "Nenhum modo cadastrado nesta casa.\n";
                } else {
                    casa->printModosInfo();
                }
                break;
            case 2: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Apenas adultos criam Modos.\n";
                    break;
                }
                std::string nomeModo;
                bool sucesso = false;
                int tentativas = 0;

                while (!sucesso && tentativas < 3) {
                    std::cout << "Digite o nome do novo modo (ex: Modo Cinema): ";
                    std::getline(std::cin, nomeModo);

                    try {
                        usuarioLogado->criarModo(casa, nomeModo);
                        std::cout << "Modo '" << nomeModo << "' criado com sucesso!\n";
                        sucesso = true;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Erro: " << e.what() << "\n";
                        std::cerr << "Tentativa " << (tentativas+1) << " falhou. Tente novamente...\n";
                        tentativas++;
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha após 3 tentativas.\n";
                }

                break;
            }
            case 3: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Apenas adultos removem Modos.\n";
                    break;
                }
                std::string nomeModo;
                std::cout << "Digite o nome do modo a ser removido: ";
                std::getline(std::cin, nomeModo);
                try {
                    usuarioLogado->apagarModo(casa, nomeModo);
                    std::cout << "Comando de remocao executado.\n";
                }
                catch(std::invalid_argument& e) {
                    std::cerr << "Erro: " << e.what() << '\n';
                } catch (...) {
                    std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                }
                break;
            }
            case 4: {
                std::string nomeModo;
                std::cout << "Digite o nome exato do modo que deseja acessar: ";
                std::getline(std::cin, nomeModo);

                gerenciarModoEspecifico(casa, nomeModo);
                break;
            }
            case 5:
                return;
            default:
                std::cout << "Opcao invalida! Escolha de 1 a 5.\n";
                break;
        }
    }
}

void Interface::gerenciarModoEspecifico(Smarthome* casa, std::string nomeModo) {
    Modo* modo = casa->getModo(nomeModo);

    if (modo == nullptr) {
        std::cout << "Modo '" << nomeModo << "' nao encontrado!\n";
        return;
    }

    while (true) {
        std::cout << "\n--- MODO: " << modo->getNome() << " ---\n";
        std::cout << "1. Listar comodos associados\n";
        std::cout << "2. Adicionar comodo ao modo\n";
        std::cout << "3. Remover comodo do modo\n";
        std::cout << "4. Voltar\n";
        std::cout << "Escolha uma opcao: ";

        int op;
        if (!(std::cin >> op)) {
            std::cin.clear();
            std::string lixo;
            std::getline(std::cin, lixo);
            std::cout << "Opcao invalida! Digite apenas numeros.\n";
            continue;
        }
        std::cin.ignore();

        switch (op) {
            case 1: {
                std::vector<Comodo*> comodos = modo->getComodosRelacionados();

                if (comodos.empty()) {
                    std::cout << "Nenhum comodo associado a este modo.\n";
                } else {
                    std::cout << "Comodos associados:\n";
                    for (Comodo* c : comodos) {
                        if (c != nullptr) {
                            std::cout << "- " << c->getNome() << "\n";
                        }
                    }
                }
                break;
            }

            case 2: {
                std::string nomeComodo;
                std::cout << "Digite o nome do comodo que deseja associar: ";
                std::getline(std::cin, nomeComodo);

                Comodo* comodo = casa->getComodo(nomeComodo);

                if (comodo == nullptr) {
                    std::cout << "Comodo '" << nomeComodo << "' nao encontrado!\n";
                    break;
                }

                try {
                    modo->adicionarComodoRelacionado(comodo);
                    std::cout << "Comodo '" << nomeComodo << "' associado ao modo '" 
                              << modo->getNome() << "' com sucesso!\n";
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << "\n";
                }

                break;
            }

            case 3: {
                std::string nomeComodo;
                std::cout << "Digite o nome do comodo que deseja remover do modo: ";
                std::getline(std::cin, nomeComodo);

                try {
                    modo->removerComodoRelacionado(nomeComodo);
                    std::cout << "Comodo '" << nomeComodo << "' removido do modo '" 
                              << modo->getNome() << "' com sucesso!\n";
                } catch (const std::exception& e) {
                    std::cerr << "Erro: " << e.what() << "\n";
                }

                break;
            }

            case 4:
                return;

            default:
                std::cout << "Opcao invalida! Escolha de 1 a 4.\n";
                break;
        }
    }
}

void Interface::criarCasaPadrao(Smarthome* casa) {
    int qtdQuartos;
    int qtdBanheiros;
    char temSala;
    char temCozinha;
    char temEscritorio;

    std::cout << "\n--- CRIAR CASA PADRAO ---\n";

    std::cout << "Quantidade de quartos: ";
    std::cin >> qtdQuartos;

    std::cout << "Quantidade de banheiros: ";
    std::cin >> qtdBanheiros;

    std::cout << "Possui sala? (S/N): ";
    std::cin >> temSala;

    std::cout << "Possui cozinha? (S/N): ";
    std::cin >> temCozinha;

    std::cout << "Possui escritorio? (S/N): ";
    std::cin >> temEscritorio;

    std::cin.ignore();

    for (int i = 1; i <= qtdQuartos; i++) {
        try {
            usuarioLogado->criarComodo(casa, "Quarto " + std::to_string(i));
        } catch (...) {}
    }

    for (int i = 1; i <= qtdBanheiros; i++) {
        try {
            usuarioLogado->criarComodo(casa, "Banheiro " + std::to_string(i));
        } catch (...) {}
    }

    if (temSala == 'S' || temSala == 's') {
        try {
            usuarioLogado->criarComodo(casa, "Sala");
        } catch (...) {}
    }

    if (temCozinha == 'S' || temCozinha == 's') {
        try {
            usuarioLogado->criarComodo(casa, "Cozinha");
        } catch (...) {}
    }

    if (temEscritorio == 'S' || temEscritorio == 's') {
        try {
            usuarioLogado->criarComodo(casa, "Escritorio");
        } catch (...) {}
    }

    std::cout << "\nCasa padrao personalizada criada com sucesso!\n";
}

void Interface::mostrarPlantaCasa(Smarthome* casa) {
    std::cout << "\n======================================\n";
    std::cout << "        PLANTA DA CASA: " << casa->getNome() << "\n";
    std::cout << "======================================\n";

    const std::vector<Comodo>& comodos = casa->getComodos();

    if (comodos.empty()) {
        std::cout << "Nenhum comodo cadastrado para exibir.\n";
        return;
    }

    const std::vector<Modo>& modos = casa->getListaModos();

    for (const auto& comodo : comodos) {

        std::cout << "+----------------------+\n";
        std::cout << "| " << comodo.getNome() << "\n";
        std::cout << "+----------------------+\n";

        bool possuiModo = false;

        for (const auto& modo : modos) {

            std::vector<Comodo*> relacionados = modo.getComodosRelacionados();

            for (Comodo* c : relacionados) {

                if (c != nullptr && c->getNome() == comodo.getNome()) {

                    std::cout << "   [Modo: "
                              << modo.getNome()
                              << "]\n";

                    possuiModo = true;
                }
            }
        }

        if (!possuiModo) {
            std::cout << "   [Nenhum modo associado]\n";
        }

        std::cout << std::endl;
    }
}