#include <vector>
#include <string>
#include <iostream>

#include "Smarthome.hpp"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include "Comodo.hpp"

#include "doctest.h"


TEST_CASE("TESTE 1 construtor - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome smarthome(contaTeste, "Minha Casa");

    CHECK(smarthome.getNome() == "Minha Casa");

    SUBCASE("TESTE 1.1 nome da smarthome eh vazio") {

        Smarthome smarthome2(contaTeste, "");

        CHECK(smarthome2.getNome() == "");
    }

    SUBCASE("TESTE 1.3 nome da smarthome eh longo") {

        std::string longName(1000, 'A');

        Smarthome smarthome4(contaTeste, longName);

        CHECK(smarthome4.getNome().size() == 1000);
    }
}

TEST_CASE("TESTE 2 adicionarModo - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;

    Modo modoTeste(objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);

    CHECK(casaTeste.getQuantidadeModos() == 1);
}

TEST_CASE("TESTE 3 adicionarComodo - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    Comodo comodoTeste("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(comodoTeste);

    CHECK(casaTeste.getQuantidadeComodos() == 1);
}

TEST_CASE("TESTE 4 adicionarObjeto - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<Sensor*> sensores;

    std::vector<std::string> statusPossiveis = {
        "Ligado",
        "Desligado"
    };

    float consumoMedio = 11.5f;

    std::vector<std::function<void()>> funcoes = {
        [](){}
    };

    std::vector<std::function<void()>> funcoesRestritas = {
        [](){}
    };

    ObjetoInteligente objetoTeste(
        false,
        sensores,
        statusPossiveis,
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(objetoTeste);

    CHECK(casaTeste.getQuantidadeObjetos() == 1);
}