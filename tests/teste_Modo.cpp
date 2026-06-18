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

    SUBCASE("Nome do modo nao pode ser vazio") {
        CHECK_THROWS(Modo("", objetos, comodos, true, false));
    }

    SUBCASE("Nome do modo nao pode ser maior que 20 caracteres") {
        CHECK_THROWS(Modo("AAAAAAAAAAAAAAAAAAAAAA", objetos, comodos, true, false));
    }

    SUBCASE("Nome do modo nao pode conter caracteres invalidos") {
        CHECK_THROWS(Modo("&&##$$", objetos, comodos, true, false));
    }

    SUBCASE("Modo começa ligado") {
        Modo modo("Noturno", objetos, comodos, true, false);

        CHECK(modo.getAtivoModo() == true);
    }

    SUBCASE("Modo começa bloqueado e desligado") {
        Modo modo("Seguranca", objetos, comodos, true, true);

        CHECK(modo.getBloqueadoModo() == true);
        CHECK(modo.getAtivoModo() == false);
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

    SUBCASE("Modo bloqueado nao pode ser ativado") {
        modo.setBloqueadoModo(true);
        modo.setAtivoModo(true);

        CHECK(modo.getAtivoModo() == false);
    }

    SUBCASE("Bloquear modo desativa o modo") {
        modo.setAtivoModo(true);
        modo.setBloqueadoModo(true);

        CHECK(modo.getAtivoModo() == false);
        CHECK(modo.getBloqueadoModo() == true);
    }

    SUBCASE("Modo desbloqueado pode ser ativado novamente") {
        modo.setBloqueadoModo(true);
        modo.setBloqueadoModo(false);
        modo.setAtivoModo(true);

        CHECK(modo.getAtivoModo() == true);
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

TEST_CASE("Modo executa e e desfaz instrucao"){
    //teste de caso positivo
    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;
    Modo modo("Padrao", objetos, comodos, false, false);
        
    SUBCASE("executarInstrucao lança exceção") {
        CHECK_THROWS_WITH(modo.executarInstrucao(nullptr, nullptr),
            "Modo nao pode executar instrucao em Objeto nullptr");
    }

    SUBCASE("desfazerInstrucao lança exceção") {
        CHECK_THROWS_WITH(modo.desfazerInstrucao(nullptr, nullptr),
        "Modo nao pode desfazer instrucao em Objeto nullptr");
    }
}