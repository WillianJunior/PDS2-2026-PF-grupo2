#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "Modo.hpp"

TEST_CASE("Modo começa ligado") {

    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;

    Modo modo(objetos, comodos, true, false);

    CHECK(modo.getAtivoModo() == true);
}

TEST_CASE("Modo começa bloqueado") {

    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;

    Modo modo(objetos, comodos, false, true);

    CHECK(modo.getBloqueadoModo() == true);
}

TEST_CASE("Ativar modo funciona") {

    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;

    Modo modo(objetos, comodos, false, false);

    modo.setAtivoModo(true);

    CHECK(modo.getAtivoModo() == true);
}

TEST_CASE("Bloquear modo funciona") {

    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;

    Modo modo(objetos, comodos, false, false);

    modo.setBloqueadoModo(true);

    CHECK(modo.getBloqueadoModo() == true);
}

TEST_CASE("Lista de objetos começa vazia") {

    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;

    Modo modo(objetos, comodos, false, false);

    CHECK(modo.getObjetosRelacionados().size() == 0);
}

TEST_CASE("Lista de comodos começa vazia") {

    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;

    Modo modo(objetos, comodos, false, false);

    CHECK(modo.getComodosRelacionados().size() == 0);
}