#include "doctest.h"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include <vector>

// Comportamentos dos métodos ainda não implementados.

TEST_CASE("Teste 01: Inicializacao do Sensor") {
    std::vector<ObjetoInteligente> objetos;
    std::vector<Modo> modos;
    
    Sensor sensor(true, false, objetos, modos);

    CHECK(sensor.getEstaLigado() == true);
    CHECK(sensor.getEstaAtivado() == false);
}

TEST_CASE("Teste 02: Metodo setEstaLigado") {
    std::vector<ObjetoInteligente> objetos;
    std::vector<Modo> modos;
    Sensor sensor(false, false, objetos, modos); // Começa desligado

    sensor.setEstaLigado();

    CHECK(sensor.getEstaLigado() == true);
}

TEST_CASE("Teste 03: Metodo setEstaAtivado") {
    std::vector<ObjetoInteligente> objetos;
    std::vector<Modo> modos;
    Sensor sensor(true, false, objetos, modos); // Começa ativado = false

    sensor.setEstaAtivado();

    CHECK(sensor.getEstaAtivado() == true);
}

TEST_CASE("Teste 04: Ativacao de Modo") {
    std::vector<ObjetoInteligente> objetos;
    std::vector<Modo> modos;
    Sensor sensor(true, false, objetos, modos);
    Modo modoTeste;

    sensor.ativarModo(modoTeste);

    CHECK(sensor.getModosConectados().getNome() == modoTeste.getNome()); // Exemplo imaginando que Modo tem um getNome()
}