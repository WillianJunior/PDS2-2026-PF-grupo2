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

    return Modo("ModoTeste", objetos, comodos, true, false);
}

TEST_CASE("TESTE 1 construtor - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    CHECK(comodoTeste.getNome() == "comodoTeste");
    CHECK(comodoTeste.getSmarthome() == &smarthome);

    SUBCASE("TESTE 1.1 nome nao pode ser vazio") {
        CHECK_THROWS(Comodo("", &smarthome));
    }

    SUBCASE("TESTE 1.2 ponteiro smarthome nao pode ser nullptr") {
        CHECK_THROWS (Comodo("comodoTeste", nullptr));
    }

    SUBCASE("TESTE 1.3 nome longo") {
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

    SUBCASE("TESTE 2.1 ponteiro nullptr nao adiciona") {
        comodoTeste.adicionarObjeto(nullptr);
        CHECK(comodoTeste.getObjetos().size() == 1);
    }

    SUBCASE("TESTE 2.2 objeto repetido nao duplica") {
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

    SUBCASE("TESTE 3.1 ponteiro nullptr nao adiciona") {
        comodoTeste.adicionarSensor(nullptr);
        CHECK(comodoTeste.getSensores().size() == 1);
    }

    SUBCASE("TESTE 3.2 sensor repetido nao duplica") {
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

    SUBCASE("TESTE 4.1 modo repetido nao duplica") {
        comodoTeste.adicionarModo(&modo);
        CHECK(comodoTeste.getModos().size() == 1);
    }

    SUBCASE("TESTE 4.2 modo nullptr nao adiciona") {
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

    SUBCASE("TESTE 5.1 mais de uma conta") {
        Conta contaTeste2("2", "Usuario B", "usuarioB@email.com", "senha456", true);
        comodoTeste.entrarConta(&contaTeste2);
        CHECK(comodoTeste.getContasPresentes().size() == 2);
    }

    SUBCASE("TESTE 5.2 conta nullptr nao adiciona") {
        comodoTeste.entrarConta(nullptr);
        CHECK(comodoTeste.getContasPresentes().size() == 1);
    }

    SUBCASE("TESTE 5.3 conta nao pode entrar duas vezes"){
        comodoTeste.entrarConta(&contaTeste);
        CHECK(comodoTeste.getContasPresentes().size() == 1);
    }
}

TEST_CASE("TESTE 6 sairConta - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Conta contaTeste2("2", "Usuario B", "usuariob@email.com", "senha1234", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);
    comodoTeste.entrarConta(&contaTeste);
    comodoTeste.entrarConta(&contaTeste2);

    CHECK(comodoTeste.getContasPresentes().size() == 2);
    CHECK(comodoTeste.getContasPresentes().front() == &contaTeste);

    comodoTeste.sairConta();
    CHECK(comodoTeste.getContasPresentes().size() == 1);
    CHECK(comodoTeste.getContasPresentes().front() == &contaTeste2);
    comodoTeste.sairConta();
    CHECK(comodoTeste.getContasPresentes().empty());

    SUBCASE("TESTE 6.1 sair sem conta nao quebra") {
        comodoTeste.sairConta();
        CHECK(comodoTeste.getContasPresentes().empty());
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

// ---- implementação incompleta dos metodos seguintes -----

TEST_CASE("TESTE 8 printObjetosInfo - Comodo"){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto obj = DummyObjetoComodo();

    comodoTeste.adicionarObjeto(&obj);
    
    comodoTeste.printObjetosInfo();
    //CHECK();
}
TEST_CASE("TESTE 9 printModosInfo - Comodo" ){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto modo = DummyModoComodo();

    comodoTeste.adicionarModo(&modo);

    comodoTeste.printModosInfo();
    // CHECK(); 

}

TEST_CASE("TESTE 10 printContasInfo - Comodo"){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    comodoTeste.entrarConta(&contaTeste);

    comodoTeste.printContasInfo();
    //CHECK();

}

TEST_CASE("TESTE 11 printSensoresInfo - Comodo"){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);
    
    auto sensor = DummySensorComodo();

    comodoTeste.adicionarSensor(&sensor);

    comodoTeste.printSensoresInfo();
   //CHECK();

}