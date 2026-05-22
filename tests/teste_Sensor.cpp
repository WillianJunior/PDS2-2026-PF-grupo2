#include "doctest.h"

#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"

#include <vector>

TEST_CASE("Teste 01: Inicializacao do Sensor") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Sensor sensor(true, false, objetos, modos);

    CHECK(sensor.getEstaLigado() == true);
    CHECK(sensor.getEstaAtivado() == false);
}

TEST_CASE("Teste 02: Metodo setEstaLigado") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Sensor sensor(false, false, objetos, modos);

    sensor.setEstaLigado();

    CHECK(sensor.getEstaLigado() == false);
}

TEST_CASE("Teste 03: Metodo setEstaAtivado") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Sensor sensor(true, false, objetos, modos);

    sensor.setEstaAtivado();

    CHECK(sensor.getEstaAtivado() == false);
}