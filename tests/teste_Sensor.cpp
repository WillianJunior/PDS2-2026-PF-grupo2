#include "doctest.h"

#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"

#include <vector>

TEST_CASE("Teste 01: Inicializacao do Sensor") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor("sensorTeste", true, false, comodo, objetos, modos);

    CHECK(sensor.getEstaLigado() == true);
    CHECK(sensor.getEstaAtivado() == false);
}

TEST_CASE("Teste 02: Metodo setEstaLigado") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor("sensorTeste", false, false, comodo, objetos, modos);

    sensor.setEstaLigado(1);

    CHECK(sensor.getEstaLigado() == true);
}

TEST_CASE("Teste 03: Metodo setEstaAtivado") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor("sensorTeste", true, false, comodo, objetos, modos);

    sensor.setEstaAtivado(1);

    CHECK(sensor.getEstaAtivado() == true);
}

TEST_CASE("operador == retorna true para sensores iguais") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("Sala", nullptr);

    Sensor sensor1(
        "SensorTeste",
        true,
        false,
        comodo,
        objetos,
        modos
    );

    Sensor sensor2(
        "SensorTeste",
        true,
        false,
        comodo,
        objetos,
        modos
    );

    CHECK(sensor1 == sensor2);
}

TEST_CASE("checarAmbiente encontra condicoes existentes") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("Sala", nullptr);

    comodo.adicionarCondicao("quente");
    comodo.adicionarCondicao("iluminado");

    Sensor sensor(
        "SensorTeste",
        true,
        true,
        comodo,
        objetos,
        modos
    );

    CHECK(sensor.checarAmbiente("quente"));
    CHECK(sensor.checarAmbiente("iluminado"));
    CHECK_FALSE(sensor.checarAmbiente("frio"));
}

TEST_CASE("ativarModo ativa um modo") {

    Comodo comodo("Sala", nullptr);

    Sensor sensor(
        "SensorTeste",
        true,
        true,
        comodo,
        {},
        {}
    );

    Modo modo(
        "ModoTeste",
        {},
        {},
        false,
        false
    );

    CHECK_FALSE(modo.getAtivoModo());

    sensor.ativarModo(&modo);

    CHECK(modo.getAtivoModo());
}

TEST_CASE("ativarObjeto executa a funcao selecionada") {

    bool executou = false;

    std::vector<std::function<void()>> funcoes = {
        [&executou]() {
            executou = true;
        }
    };

    ObjetoInteligente objeto(
        "objetoTeste",
        false,
        {},
        {},
        "",
        0.0f,
        funcoes,
        {}
    );

    Comodo comodo("Sala", nullptr);

    Sensor sensor(
        "SensorTeste",
        true,
        true,
        comodo,
        {},
        {}
    );

    CHECK_FALSE(executou);

    sensor.ativarObjeto(&objeto, 0);

    CHECK(executou);
}