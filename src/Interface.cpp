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
            std::string nomeCasa;
            std::cout << "\nDigite o nome da sua nova Smarthome: ";
            std::getline(std::cin, nomeCasa);
            
            std::string idGerado = std::to_string(rand() % 10000); 
            
            usuarioLogado->criarSmarthome(idGerado, nomeCasa);
            
            std::cout << "Smarthome '" << nomeCasa << "' criada com sucesso!\n";
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

    Conta novaConta(id, nome, email, senha, ehAdulto);

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
        std::cout << "3. Relatorio de Consumo de Energia\n";
        std::cout << "4. Voltar para Minhas Smarthomes\n";
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
                std::cout << "\n[Acessando modulo de Comodos... (Em construcao)]\n";
                break;
            case 2:
                std::cout << "\n[Acessando modulo de Modos... (Em construcao)]\n";
                break;
            case 3:
                std::cout << "\n[Gerando relatorio... (Em construcao)]\n";
                break;
            case 4:
                std::cout << "\nSaindo da casa " << casa->getNome() << "...\n";
                return;
            default:
                std::cout << "\nOpcao invalida! Escolha de 1 a 4.\n";
                break;
        }
    }
}