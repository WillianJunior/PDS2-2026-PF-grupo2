#include "doctest.h"
#include "Login.hpp"

TEST_CASE("Login inicia sem contas") {

    std::vector<Conta> contas;

    Login login(contas);

    CHECK(login.getContasCadastradas().size() == 0);
}

TEST_CASE("Criacao de contas") {

    std::vector<Conta> contas;

    Login login(contas);

    SUBCASE("Criar uma conta") {
        Conta conta("1", "Maria", "mariapaula@email.com", "123456", true);

        login.criarConta(conta);

        CHECK(login.getContasCadastradas().size() == 1);
    }

    SUBCASE("Nao permitir email duplicado") {
        Conta conta1("1", "Maria", "mariapaula@email.com", "123456", true);
        Conta conta2("2", "Maria 2", "mariapaula@email.com", "abcdef", true);

        login.criarConta(conta1);
        login.criarConta(conta2);

        CHECK(login.getContasCadastradas().size() == 1);
    }
}

TEST_CASE("Autenticacao de contas") {

    Conta conta("1", "Maria", "mariapaula@email.com", "123456", true);

    std::vector<Conta> contas = {conta};

    Login login(contas);

    SUBCASE("Email e senha corretos") {
        CHECK(login.autenticarConta("mariapaula@email.com", "123456") == true);
    }

    SUBCASE("Senha incorreta") {
        CHECK(login.autenticarConta("mariapaula@email.com", "senhaErrada") == false);
    }

    SUBCASE("Email inexistente") {
        CHECK(login.autenticarConta("naoexiste@email.com", "123456") == false);
    }
}