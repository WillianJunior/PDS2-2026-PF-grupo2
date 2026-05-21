#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Login.hpp"

TEST_CASE("Login inicia sem contas") {

    std::vector<Conta> contas;

    Login login(contas);

    CHECK(login.getContasCadastradas().size() == 0);
}

TEST_CASE("Criar conta adiciona conta") {

    std::vector<Conta> contas;

    Login login(contas);

    Conta conta(
        "1",
        "Maria",
        "mariapaula@email.com",
        "123456",
        true
    );

    login.criarConta(conta);

    CHECK(login.getContasCadastradas().size() == 1);
}

TEST_CASE("Autenticar conta com dados corretos") {

    Conta conta(
        "1",
        "Maria",
        "mariapaula@email.com",
        "123456",
        true
    );

    std::vector<Conta> contas = {conta};

    Login login(contas);

    CHECK(login.autenticarConta(
        "mariapaula@email.com",
        "123456"
    ) == true);
}