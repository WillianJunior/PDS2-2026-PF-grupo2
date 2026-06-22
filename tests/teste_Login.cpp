#include "doctest.h"
#include "Login.hpp"

TEST_CASE("Login inicia sem contas") {

    std::vector<std::unique_ptr<Conta>> contas;

    Login login(std::move(contas));

    CHECK(login.getContasCadastradas().size() == 0);
}

TEST_CASE("Criacao de contas") {

    std::vector<std::unique_ptr<Conta>> contas;

    Login login(std::move(contas));

    SUBCASE("Criar uma conta") {
        auto conta = std::make_unique<Conta>("1", "Maria", "mariapaula@email.com", "123456", true);

        login.criarConta(std::move(conta));

        CHECK(login.getContasCadastradas().size() == 1);
    }

    SUBCASE("Nao permitir email duplicado") {
        auto conta1 = std::make_unique<Conta>("1", "Maria", "mariapaula@email.com", "123456", true);
        auto conta2 = std:: make_unique<Conta>("2", "Maria 2", "mariapaula@email.com", "abcdef", true);

        login.criarConta(std::move(conta1));
        login.criarConta(std::move(conta2));

        CHECK(login.getContasCadastradas().size() == 1);
    }
}

TEST_CASE("Autenticacao de contas") {

    std::vector<std::unique_ptr<Conta>> contas;
    contas.push_back(std::make_unique<Conta>("1", "Maria", "mariapaula@email.com", "123456", true));

    Login login(std::move(contas));

    SUBCASE("Email e senha corretos") {
        CHECK(login.autenticarConta("mariapaula@email.com", "123456") == true);
    }

    SUBCASE("Senha incorreta") {
        CHECK(login.autenticarConta("mariapaula@email.com", "senhaErrada") == false);
    }

    SUBCASE("Email inexistente") {
        CHECK(login.autenticarConta("naoexiste@email.com", "123456") == false);
    }

    SUBCASE("Conta bloqueada nao autentica") {
        login.bloquearConta("mariapaula@email.com");

        CHECK(login.autenticarConta("mariapaula@email.com", "123456") == false);
    }
}

TEST_CASE("Bloqueio de contas") {

    std::vector<std::unique_ptr<Conta>> contas;
    contas.push_back(std::make_unique<Conta>("1", "Maria", "mariapaula@email.com", "123456", true));

    Login login(std::move(contas));

    SUBCASE("Bloquear conta existente") {
        CHECK(login.bloquearConta("mariapaula@email.com") == true);
    }

    SUBCASE("Nao bloquear conta inexistente") {
        CHECK(login.bloquearConta("naoexiste@email.com") == false);
    }
}