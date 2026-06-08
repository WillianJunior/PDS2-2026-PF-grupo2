#include "doctest.h"

#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Comodo.hpp"

TEST_CASE("Construtor do Modo") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;

    SUBCASE("Modo guarda o nome corretamente") {
        Modo modo("Noturno", objetos, comodos, true, false);

        CHECK(modo.getNome() == "Noturno");
    }

    SUBCASE("Modo começa ligado") {
        Modo modo("Noturno", objetos, comodos, true, false);

        CHECK(modo.getAtivoModo() == true);
    }

    SUBCASE("Modo começa bloqueado") {
        Modo modo("Seguranca", objetos, comodos, false, true);

        CHECK(modo.getBloqueadoModo() == true);
    }
}

TEST_CASE("Alteracao de estado do Modo") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;

    Modo modo("Economia", objetos, comodos, false, false);

    SUBCASE("Ativar modo funciona") {
        modo.setAtivoModo(true);

        CHECK(modo.getAtivoModo() == true);
    }

    SUBCASE("Bloquear modo funciona") {
        modo.setBloqueadoModo(true);

        CHECK(modo.getBloqueadoModo() == true);
    }
}

TEST_CASE("Listas relacionadas ao Modo") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;

    Modo modo("Padrao", objetos, comodos, false, false);

    SUBCASE("Lista de objetos começa vazia") {
        CHECK(modo.getObjetosRelacionados().size() == 0);
    }

    SUBCASE("Lista de comodos começa vazia") {
        CHECK(modo.getComodosRelacionados().size() == 0);
    }
}