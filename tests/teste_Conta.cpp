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

TEST_CASE("Testando a classe Conta - Chamadas de Metodos") {
    Conta conta("1", "Admin", "admin@smart.com", "admin1234", true);
    
    Smarthome sh("SH01", "Casa1");
    Comodo com("COM01", "Sala1");
    
    SUBCASE("Metodos de manipulacao da Smarthome e Comodos") {
        conta.criarSmarthome("sh1", "Casa");
        conta.apagarSmarthome(sh);
        conta.criarComodo(sh, "Sala");
        conta.apagarComodo(sh, "Sala");
    }

    SUBCASE("Metodos de manipulacao de Modos") {
        conta.criarModo(sh, "Seguranca");
        conta.apagarModo(sh, "Seguranca");
        conta.editarModo(sh, "Seguranca");
    }

    SUBCASE("Metodos de manipulacao de Objetos e Sensores") {
        conta.criarObjeto(sh, com, "SmartTV");
        conta.apagarObjeto(sh, com, "SmartTV");
        conta.moverObjeto(sh, com, "SmartTV", com);
        
        conta.criarSensor(sh, com, "Presenca");
        conta.apagarSensor(sh, com, "Presenca");
        conta.moverSensor(sh, com, "Presenca", com);
    }
    
    SUBCASE("Metodos de Relatorio") {
        CHECK(conta.gerarRelatorioDeEnergia(sh) == 42.0f);
    }
}