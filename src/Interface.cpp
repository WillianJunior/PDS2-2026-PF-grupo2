#include "Interface.hpp"
#include "Smarthome.hpp"
#include <iostream>

Interface::Interface()
    : sistemaLogin(std::vector<std::unique_ptr<Conta>>{})
{
    auto adminTeste =
        std::make_unique<Conta>(
            "1",
            "Administrador",
            "admin@smarthome.com",
            "12345678",
            true
        );

    sistemaLogin.criarConta(std::move(adminTeste));
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
            usuarioLogado = nullptr;
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

    const std::vector<std::unique_ptr<Smarthome>>& casas = usuarioLogado->getSmarthomes();

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
        Smarthome* casaEscolhida = casas[op - 1].get();
        
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

        for (const auto& conta : sistemaLogin.getContasCadastradas()) {
            if (conta->getEmail() == email) {
                usuarioLogado = conta.get();
                break;
            }
        }

        std::cout << "Bem-vindo(a), "
                  << usuarioLogado->getNome()
                  << "!\n";
    }
    else {
        std::cout
            << "\nErro de autenticacao! "
            << "E-mail ou senha incorretos ou conta bloqueada.\n";
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

    try {
        auto novaConta =
            std::make_unique<Conta>(
                id,
                nome,
                email,
                senha,
                ehAdulto
            );

        if (!novaConta->validarFormatoEmail()) {
            std::cout
                << "\nErro no cadastro: Formato de e-mail invalido "
                << "(deve conter '@').\n";
            return;
        }

        if (!novaConta->validarSenha()) {
            std::cout
                << "\nErro no cadastro: A senha precisa ter "
                << "pelo menos 8 caracteres.\n";
            return;
        }

        sistemaLogin.criarConta(std::move(novaConta));

        std::cout
            << "\nConta cadastrada com sucesso! "
            << "Voce ja pode entrar no sistema.\n";
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Erro ao criar conta: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr
            << "Erro inesperado capturado. "
            << "Verifique os dados e tente novamente.\n";
    }
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
        std::cout << "6. Testar comunicacao entre dispositivos\n";
        std::cout << "7. Simular falha em dispositivo\n";
        std::cout << "8. Reparar dispositivo\n";
        std::cout << "9. Listar dispositivos em falha\n";
        std::cout << "10. Voltar para Menu da Casa\n";
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
                int tipoObjeto;
                bool sucesso = false;
                int tentativas = 0;

                while (!sucesso && tentativas < 3) {
                    std::cout << "Digite o nome do novo objeto: ";
                    std::getline(std::cin, nomeObjeto);

                    std::cout << "\nEscolha o tipo do objeto:\n";
                    std::cout << "1. Luz\n";
                    std::cout << "2. TV\n";
                    std::cout << "3. Caixa de Som\n";
                    std::cout << "4. Ar Condicionado\n";
                    std::cout << "5. Portao\n";
                    std::cout << "6. Termostato\n";
                    std::cout << "Opcao: ";

                    if (!(std::cin >> tipoObjeto)) {
                        std::cin.clear();
                        std::string lixo;
                        std::getline(std::cin, lixo);
                        std::cout << "Tipo invalido. Digite apenas numeros.\n";
                        tentativas++;
                        continue;
                    }

                    std::cin.ignore();

                    try {
                        usuarioLogado->criarObjetoPorTipo(casa, comodo, nomeObjeto, tipoObjeto);
                        std::cout << "Objeto '" << nomeObjeto << "' adicionado com sucesso!\n";
                        sucesso = true;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Erro: " << e.what() << "\n";
                        tentativas++;
                    } catch (...) {
                        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                        tentativas++;
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha apos 3 tentativas.\n";
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
                } catch (std::invalid_argument& e) {
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
                        tentativas++;
                    } catch (...) {
                        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha apos 3 tentativas.\n";
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
                } catch (std::invalid_argument& e) {
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

            case 6: {
                std::string nome1, nome2;
                std::cout << "Digite o nome do primeiro dispositivo: ";
                std::getline(std::cin, nome1);

                std::cout << "Digite o nome do segundo dispositivo: ";
                std::getline(std::cin, nome2);

                ObjetoInteligente* obj1 = nullptr;
                ObjetoInteligente* obj2 = nullptr;

                for (ObjetoInteligente* obj : comodo->getObjetos()) {
                    if (obj != nullptr) {
                        if (obj->getNome() == nome1) obj1 = obj;
                        if (obj->getNome() == nome2) obj2 = obj;
                    }
                }

                if (obj1 == nullptr || obj2 == nullptr) {
                    std::cout << "Um ou ambos os dispositivos nao foram encontrados.\n";
                    break;
                }

                if (obj1->comunicaCom(*obj2)) {
                    std::cout << obj1->getNome() << " pode se comunicar com "
                              << obj2->getNome() << ".\n";
                    std::cout << "Protocolo compartilhado: "
                              << obj1->getProtocoloComoString() << "\n";
                } else {
                    std::cout << obj1->getNome() << " NAO pode se comunicar com "
                              << obj2->getNome() << ".\n";
                    std::cout << "Protocolos: " << obj1->getProtocoloComoString()
                              << " e " << obj2->getProtocoloComoString() << "\n";
                }

                break;
            }

            case 7: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Apenas adultos podem simular falhas.\n";
                    break;
                }

                std::string nomeObjeto;
                std::cout << "Digite o nome do dispositivo que entrara em falha: ";
                std::getline(std::cin, nomeObjeto);

                bool encontrado = false;

                for (ObjetoInteligente* obj : comodo->getObjetos()) {
                    if (obj != nullptr && obj->getNome() == nomeObjeto) {
                        obj->simularFalha();
                        std::cout << "Falha simulada no dispositivo '" << obj->getNome() << "'.\n";
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    std::cout << "Dispositivo nao encontrado.\n";
                }

                break;
            }

            case 8: {
                if (!usuarioLogado->isPerfilAdulto()) {
                    std::cout << "\n[ACESSO NEGADO] Controle Parental: Apenas adultos podem reparar dispositivos.\n";
                    break;
                }

                std::string nomeObjeto;
                std::cout << "Digite o nome do dispositivo que deseja reparar: ";
                std::getline(std::cin, nomeObjeto);

                bool encontrado = false;

                for (ObjetoInteligente* obj : comodo->getObjetos()) {
                    if (obj != nullptr && obj->getNome() == nomeObjeto) {
                        obj->repararFalha();
                        std::cout << "Dispositivo '" << obj->getNome() << "' reparado com sucesso.\n";
                        encontrado = true;
                        break;
                    }
                }

                if (!encontrado) {
                    std::cout << "Dispositivo nao encontrado.\n";
                }

                break;
            }

            case 9: {
                bool encontrouFalha = false;

                std::cout << "\n[Dispositivos em falha no comodo " << comodo->getNome() << "]\n";

                for (ObjetoInteligente* obj : comodo->getObjetos()) {
                    if (obj != nullptr && obj->estaEmFalha()) {
                        std::cout << "- " << obj->getNome()
                                  << " | Protocolo: "
                                  << obj->getProtocoloComoString()
                                  << "\n";
                        encontrouFalha = true;
                    }
                }

                if (!encontrouFalha) {
                    std::cout << "Nenhum dispositivo em falha neste comodo.\n";
                }

                break;
            }

            case 10:
                return;

            default:
                std::cout << "Opcao invalida! Escolha de 1 a 10.\n";
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
                int tipoModo;
                bool sucesso = false;
                int tentativas = 0;

                while (!sucesso && tentativas < 3) {
                    std::cout << "Digite o nome do novo modo (ex: Modo Cinema): ";
                    std::getline(std::cin, nomeModo);

                    std::cout << "\nEscolha o tipo do modo:\n";
                    std::cout << "1. Modo comum\n";
                    std::cout << "2. Modo Cinema\n";
                    std::cout << "3. Modo Noturno\n";
                    std::cout << "4. Modo Trabalho\n";
                    std::cout << "5. Modo Ausente\n";
                    std::cout << "6. Modo Festa\n";
                    std::cout << "7. Modo Economia\n";
                    std::cout << "Opcao: ";

                    if (!(std::cin >> tipoModo)) {
                        std::cin.clear();
                        std::string lixo;
                        std::getline(std::cin, lixo);
                        std::cout << "Tipo invalido. Digite apenas numeros.\n";
                        tentativas++;
                        continue;
                    }

                    std::cin.ignore();

                    try {
                        usuarioLogado->criarModoPorTipo(casa, nomeModo, tipoModo);
                        std::cout << "Modo '" << nomeModo << "' criado com sucesso!\n";
                        sucesso = true;
                    } catch (const std::invalid_argument& e) {
                        std::cerr << "Erro: " << e.what() << "\n";
                        std::cerr << "Tentativa " << (tentativas + 1) << " falhou. Tente novamente...\n";
                        tentativas++;
                    } catch (...) {
                        std::cerr << "Erro inesperado capturado. Verifique os dados e tente novamente.\n";
                        tentativas++;
                    }
                }

                if (!sucesso) {
                    std::cerr << "Falha apos 3 tentativas.\n";
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
        std::cout << "4. Ligar modo\n";
        std::cout << "5. Desligar modo\n";
        std::cout << "6. Voltar\n";
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

                    std::cout << "Comodo '" << nomeComodo
                              << "' associado ao modo '"
                              << modo->getNome()
                              << "' com sucesso!\n";

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

                    std::cout << "Comodo '" << nomeComodo
                              << "' removido do modo '"
                              << modo->getNome()
                              << "' com sucesso!\n";

                } catch (const std::exception& e) {

                    std::cerr << "Erro: " << e.what() << "\n";
                }

                break;
            }

            case 4: {

    bool temObjetoRestrito = false;

    for (Comodo* c : modo->getComodosRelacionados()) {

        if (c != nullptr) {

            for (ObjetoInteligente* obj : c->getObjetos()) {

                if (obj != nullptr && obj->getRestricaoAdulto()) {
                    temObjetoRestrito = true;
                }
            }
        }
    }

    if (temObjetoRestrito && !usuarioLogado->isPerfilAdulto()) {

        std::cout << "\n[ACESSO NEGADO] Controle Parental: "
                  << "este modo controla objetos restritos.\n";

        break;
    }

    modo->setAtivoModo(true);
    modo->executarNosComodosRelacionados();

    std::cout << "Modo '" << modo->getNome()
              << "' ligado e executado nos comodos associados.\n";

    break;
}

case 5: {

    bool temObjetoRestrito = false;

    for (Comodo* c : modo->getComodosRelacionados()) {

        if (c != nullptr) {

            for (ObjetoInteligente* obj : c->getObjetos()) {

                if (obj != nullptr && obj->getRestricaoAdulto()) {
                    temObjetoRestrito = true;
                }
            }
        }
    }

    if (temObjetoRestrito && !usuarioLogado->isPerfilAdulto()) {

        std::cout << "\n[ACESSO NEGADO] Controle Parental: "
                  << "este modo controla objetos restritos.\n";

        break;
    }

    modo->setAtivoModo(false);
    modo->executarNosComodosRelacionados();

    std::cout << "Modo '" << modo->getNome()
              << "' desligado nos comodos associados.\n";

    break;
}

            case 6:

                return;

            default:

                std::cout << "Opcao invalida! Escolha de 1 a 6.\n";
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

    std::cout << "Quantidade de quartos (0 a 3): ";
    if (!(std::cin >> qtdQuartos) || qtdQuartos < 0 || qtdQuartos > 3) {
        std::cin.clear();
        std::string lixo;
        std::getline(std::cin, lixo);
        std::cout << "Quantidade invalida de quartos.\n";
        return;
    }

    std::cout << "Quantidade de banheiros (0 a 2): ";
    if (!(std::cin >> qtdBanheiros) || qtdBanheiros < 0 || qtdBanheiros > 2) {
        std::cin.clear();
        std::string lixo;
        std::getline(std::cin, lixo);
        std::cout << "Quantidade invalida de banheiros.\n";
        return;
    }

    std::cout << "Possui sala? (S/N): ";
    std::cin >> temSala;

    std::cout << "Possui cozinha? (S/N): ";
    std::cin >> temCozinha;

    std::cout << "Possui escritorio? (S/N): ";
    std::cin >> temEscritorio;

    std::cin.ignore();

    if (temSala != 'S' && temSala != 's' && temSala != 'N' && temSala != 'n') {
        std::cout << "Resposta invalida para sala.\n";
        return;
    }

    if (temCozinha != 'S' && temCozinha != 's' && temCozinha != 'N' && temCozinha != 'n') {
        std::cout << "Resposta invalida para cozinha.\n";
        return;
    }

    if (temEscritorio != 'S' && temEscritorio != 's' && temEscritorio != 'N' && temEscritorio != 'n') {
        std::cout << "Resposta invalida para escritorio.\n";
        return;
    }

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

    const std::vector<std::unique_ptr<Comodo>>& comodos = casa->getComodos();
    const std::vector<Modo>& modos = casa->getListaModos();

    if (comodos.empty()) {
        std::cout << "Nenhum comodo cadastrado para exibir.\n";
        return;
    }

    for (const auto& comodo : comodos) {

        std::cout << "+----------------------+\n";

        std::string nome = comodo->getNome();
        std::cout << "| " << nome;

        for (size_t i = 0; i < 20 - nome.size(); i++) {
            std::cout << " ";
        }

        std::cout << "|\n";

        bool possuiModo = false;

        for (const auto& modo : modos) {
            std::vector<Comodo*> relacionados = modo.getComodosRelacionados();

            for (Comodo* c : relacionados) {
                if (c != nullptr && c->getNome() == comodo->getNome()) {

                    std::string texto = "Modo: " + modo.getNome();

                    std::cout << "| " << texto;

                    for (size_t i = 0; i < 20 - texto.size(); i++) {
                        std::cout << " ";
                    }

                    std::cout << "|\n";

                    possuiModo = true;
                }
            }
        }

        if (!possuiModo) {

            std::string texto = "Modo: nenhum";

            std::cout << "| " << texto;

            for (size_t i = 0; i < 20 - texto.size(); i++) {
                std::cout << " ";
            }

            std::cout << "|\n";
        }

        std::cout << "+----------------------+\n\n";
    }
}
