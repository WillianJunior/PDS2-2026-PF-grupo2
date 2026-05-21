#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Conta.hpp"

TEST_CASE("Testando a classe Conta - Gerenciamento de Dados Cadastrais") {
    Conta conta("123", "Aline Sayuri", "aline@ufmg.br", "senhA123", true);

    SUBCASE("Verificando se os getters retornam os valores corretos") {
        CHECK(conta.getId() == "123");
        CHECK(conta.getNome() == "Aline Sayuri");
        CHECK(conta.getEmail() == "aline@ufmg.br");
        CHECK(conta.isPerfilAdulto() == true);
    }
}

// teste somente considerando tamanho da senha: 8 caracteres forte, abaixo de 8 fraco.
// caso formos verificar uso de cartere especial, uso de letras maíusculas e minúsculas, será necessário implementar no conta.cpp futuramente.

TEST_CASE("Testando a classe Conta - Validacao de Seguranca e Controle Parental") {

    // Dois subcases, o primeiro com uma conta válida (o caminho "feliz") e o outro com uma conta inválida (dados errados).

    SUBCASE("Testando conta valida (Adulto, senha forte, e-mail correto)") {
        Conta contaValida("1", "User", "teste@dominio.com", "12345678", true);
        CHECK(contaValida.validarFormatoEmail() == true);
        CHECK(contaValida.validarSenha() == true);
        CHECK(contaValida.autenticar("12345678") == true);
        CHECK(contaValida.autenticar("senhaIncorreta") == false);
    }

    SUBCASE("Testando conta invalida (Infantil, senha fraca, e-mail incorreto)") {
        Conta contaInvalida("2", "User2", "formatodeemailinvalido", "1234", false);
        CHECK(contaInvalida.validarFormatoEmail() == false);
        CHECK(contaInvalida.validarSenha() == false);
        CHECK(contaInvalida.isPerfilAdulto() == false);
    }
}