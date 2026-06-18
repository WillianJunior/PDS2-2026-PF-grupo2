#include "doctest.h"

#include "Conta.hpp"
#include "Smarthome.hpp"
#include "Comodo.hpp"

TEST_CASE("Testando a classe Conta - Gerenciamento de Dados Cadastrais") {
    Conta conta("123", "Aline Sayuri", "aline@ufmg.br", "senhA123", true);

    SUBCASE("Verificando se os getters retornam os valores corretos") {
        CHECK(conta.getId() == "123");
        CHECK(conta.getNome() == "Aline Sayuri");
        CHECK(conta.getEmail() == "aline@ufmg.br");
        CHECK(conta.isPerfilAdulto() == true);
    }

    SUBCASE("Verificando bloqueio e desbloqueio da conta") {
        CHECK(conta.estaBloqueada() == false);

        conta.bloquear();

        CHECK(conta.estaBloqueada() == true);

        conta.desbloquear();

        CHECK(conta.estaBloqueada() == false);
    }
}

// ------------------------------------------------------------

TEST_CASE("Testando a classe Conta - Validacao de Seguranca e Controle Parental") {

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

// ------------------------------------------------------------

TEST_CASE("Testando a classe Conta - Chamadas de Metodos") {

    Conta conta("1", "Admin", "admin@smart.com", "admin1234", true);

    Conta dono("0", "Dono", "dono@email.com", "senha123", true);
    Smarthome sh(dono, "Casa1");

    Comodo com("Sala1", &sh);

    SUBCASE("Metodos de manipulacao da Smarthome e Comodos") {
        conta.criarSmarthome("sh1", "Casa");
        conta.apagarSmarthome(&sh);

        conta.criarComodo(&sh, "Sala");
        conta.apagarComodo(&sh, "Sala");
    }

    SUBCASE("Metodos de manipulacao de Modos") {
        conta.criarModo(&sh, "Seguranca");
        conta.apagarModo(&sh, "Seguranca");
    }

    SUBCASE("Metodos de manipulacao de Objetos e Sensores") {
        conta.criarObjeto(&sh, &com, "SmartTV");
        conta.apagarObjeto(&sh, &com, "SmartTV");
        conta.moverObjeto(&sh, &com, "SmartTV", &com);

        conta.criarSensor(&sh, &com, "Presenca");
        conta.apagarSensor(&sh, &com, "Presenca");
        conta.moverSensor(&sh, &com, "Presenca", &com);
    }

    SUBCASE("Metodos de Relatorio") {
        CHECK(conta.gerarRelatorioDeEnergia(&sh) == 0.0f);
    }
}