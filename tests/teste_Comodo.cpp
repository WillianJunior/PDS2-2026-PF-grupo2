#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <string>
#include <vector>
#include <functional>

#include "Comodo.hpp"
#include "ObjetoInteligente.hpp"
#include "Smarthome.hpp"
#include "Sensor.hpp"
#include "Modo.hpp"
#include "Conta.hpp"

static ObjetoInteligente DummyObjetoComodo() {
    std::vector<Sensor*> sensores;
    std::vector<std::string> status = {"on", "off"};
    float consumo = 5.0f;
    std::vector<std::function<void()>> funcoes = {[]{}};
    std::vector<std::function<void()>> funcoesRestritas = {[]{}};

    return ObjetoInteligente(false, sensores, status, consumo, funcoes, funcoesRestritas);
}

static Sensor DummySensorComodo() {
    std::vector<ObjetoInteligente*> objetosConectados;
    std::vector<Modo*> modosConectados;

    return Sensor(true, true, objetosConectados, modosConectados);
}

static Modo DummyModoComodo() {
    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;

    return Modo(objetos, comodos, true, false);
}

TEST_CASE("TESTE 1 construtor - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    CHECK(comodoTeste.getNome() == "comodoTeste");
    CHECK(comodoTeste.getSmarthome() == &smarthome);

    SUBCASE("nome vazio") {
        Comodo comodoVazio("", &smarthome);
        CHECK(comodoVazio.getNome() == "");
    }

    SUBCASE("ponteiro smarthome nullptr") {
        Comodo comodoNull("comodoTeste", nullptr);
        CHECK(comodoNull.getSmarthome() == nullptr);
    }

    SUBCASE("nome longo") {
        std::string longName(1000, 'A');
        Comodo comodoLongo(longName, &smarthome);
        CHECK(comodoLongo.getNome().size() == 1000);
    }
}

TEST_CASE("TESTE 2 adicionarObjeto - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto obj = DummyObjetoComodo();

    comodoTeste.adicionarObjeto(&obj);

    CHECK(comodoTeste.getObjetos().size() == 1);

    SUBCASE("ponteiro nullptr nao adiciona") {
        comodoTeste.adicionarObjeto(nullptr);
        CHECK(comodoTeste.getObjetos().size() == 1);
    }

    SUBCASE("objeto repetido nao duplica") {
        comodoTeste.adicionarObjeto(&obj);
        CHECK(comodoTeste.getObjetos().size() == 1);
    }
}

TEST_CASE("TESTE 3 adicionarSensor - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto sensor = DummySensorComodo();

    comodoTeste.adicionarSensor(&sensor);

    CHECK(comodoTeste.getSensores().size() == 1);

    SUBCASE("ponteiro nullptr nao adiciona") {
        comodoTeste.adicionarSensor(nullptr);
        CHECK(comodoTeste.getSensores().size() == 1);
    }

    SUBCASE("sensor repetido nao duplica") {
        comodoTeste.adicionarSensor(&sensor);
        CHECK(comodoTeste.getSensores().size() == 1);
    }
}

TEST_CASE("TESTE 4 adicionarModo - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto modo = DummyModoComodo();

    comodoTeste.adicionarModo(&modo);

    CHECK(comodoTeste.getModos().size() == 1);

    SUBCASE("modo repetido nao duplica") {
        comodoTeste.adicionarModo(&modo);
        CHECK(comodoTeste.getModos().size() == 1);
    }

    SUBCASE("modo nullptr nao adiciona") {
        comodoTeste.adicionarModo(nullptr);
        CHECK(comodoTeste.getModos().size() == 1);
    }
}

TEST_CASE("TESTE 5 entrarConta - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    comodoTeste.entrarConta(&contaTeste);

    CHECK(comodoTeste.getContasPresentes().size() == 1);

    SUBCASE("mais de uma conta") {
        Conta contaTeste2("2", "Usuario B", "usuarioB@email.com", "senha456", true);
        comodoTeste.entrarConta(&contaTeste2);
        CHECK(comodoTeste.getContasPresentes().size() == 2);
    }

    SUBCASE("conta nullptr nao adiciona") {
        comodoTeste.entrarConta(nullptr);
        CHECK(comodoTeste.getContasPresentes().size() == 1);
    }
}

TEST_CASE("TESTE 6 sairConta - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    comodoTeste.entrarConta(&contaTeste);
    CHECK(comodoTeste.getContasPresentes().size() == 1);

    comodoTeste.sairConta();
    CHECK(comodoTeste.getContasPresentes().size() == 0);

    SUBCASE("sair sem conta nao quebra") {
        comodoTeste.sairConta();
        CHECK(comodoTeste.getContasPresentes().size() == 0);
    }
}

TEST_CASE("TESTE 7 removerObjeto - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto obj = DummyObjetoComodo();

    comodoTeste.adicionarObjeto(&obj);
    CHECK(comodoTeste.getObjetos().size() == 1);

    comodoTeste.removerObjeto(&obj);
    CHECK(comodoTeste.getObjetos().size() == 0);
}