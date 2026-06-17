#include "Interface.hpp"
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
            std::cout << "\n[Em construcao: Direcionando para Login...]\n";
            break;
        case 2:
            std::cout << "\n[Direcionando para Cadastro de Nova Conta...]\n";
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

void Interface::exibirMenuConta() {}
void Interface::realizarLogin() {}

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