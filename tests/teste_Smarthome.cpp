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

    CHECK(smarthome.getUsuario().getNome() == contaTeste.getNome());

    SUBCASE("TESTE 1.1 nome da smarthome nao pode ser vazio") {

        CHECK_THROWS(Smarthome(contaTeste, ""));
    }

    SUBCASE("TESTE 1.2 nome da smarthome eh longo") {

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
    std::string nome;

    Modo modoTeste(objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);

    CHECK(casaTeste.getQuantidadeModos() == 1);

    SUBCASE("TESTE 2.1 modo duplicado nao adiciona") {
        casaTeste.adicionarModo(modoTeste);
       CHECK(casaTeste.getQuantidadeModos() == 1);
    }
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

    SUBCASE("TESTE 3.1 comodo duplicado nao adiciona") {
        casaTeste.adicionarComodo(comodoTeste);
       CHECK(casaTeste.getQuantidadeComodos() == 1);
    }

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

    SUBCASE("TESTE 4.1 objeto duplicado nao adiciona"){
        casaTeste.adicionarObjeto(objetoTeste);
        CHECK(casaTeste.getQuantidadeObjetos() == 1);
    }
}
TEST_CASE("TESTE 5 removerComodo - Smarthome"){
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

    casaTeste.removerComodo(comodoTeste);

    CHECK(casaTeste.getQuantidadeComodos() == 0);
}

// ---- implementação incompleta dos metodos seguintes -----

TEST_CASE("TESTE 6 printComodosInfo - Smarthome"){
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

    casaTeste.printComodosInfo();
    //CHECK();
}
TEST_CASE("TESTE 7 printObjetosInfo - Smarthome"){
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

    casaTeste.printObjetosInfo();
    //CHECK();
}
TEST_CASE("TESTE 8 printModosInfo - Smarthome"){
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
    std::string nome;

    Modo modoTeste(objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);

    casaTeste.printModosInfo();
    //CHECK();
}