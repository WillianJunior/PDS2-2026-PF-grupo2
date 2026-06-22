#include "doctest.h"

#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Comodo.hpp"
#include "Smarthome.hpp"
#include "Conta.hpp"

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

TEST_CASE("Associacao de comodos aos modos") {

    Conta usuario("1", "Maria", "maria@gmail.com", "12345678", true);
    Smarthome casa(&usuario, "Casa");

    Comodo sala("Sala", &casa);
    Comodo quarto("Quarto", &casa);

    Modo modo("Cinema", {}, {}, false, false);

    SUBCASE("Adicionar um comodo") {

        modo.adicionarComodoRelacionado(&sala);

        CHECK(modo.getComodosRelacionados().size() == 1);
        CHECK(modo.getComodosRelacionados()[0]->getNome() == "Sala");
    }

    SUBCASE("Adicionar dois comodos") {

        modo.adicionarComodoRelacionado(&sala);
        modo.adicionarComodoRelacionado(&quarto);

        CHECK(modo.getComodosRelacionados().size() == 2);
    }

    SUBCASE("Adicionar comodo repetido deve lancar excecao") {

        modo.adicionarComodoRelacionado(&sala);

        CHECK_THROWS(modo.adicionarComodoRelacionado(&sala));
    }

    SUBCASE("Adicionar ponteiro nulo deve lancar excecao") {

        CHECK_THROWS(modo.adicionarComodoRelacionado(nullptr));
    }
}

TEST_CASE("Remocao de comodos dos modos") {

    Conta usuario("1", "Maria", "maria@gmail.com", "12345678", true);
    Smarthome casa(&usuario, "Casa");

    Comodo sala("Sala", &casa);
    Comodo quarto("Quarto", &casa);

    Modo modo("Cinema", {}, {}, false, false);

    SUBCASE("Remover um comodo existente") {

        modo.adicionarComodoRelacionado(&sala);

        modo.removerComodoRelacionado("Sala");

        CHECK(modo.getComodosRelacionados().empty());
    }

    SUBCASE("Remover entre dois comodos") {

        modo.adicionarComodoRelacionado(&sala);
        modo.adicionarComodoRelacionado(&quarto);

        modo.removerComodoRelacionado("Sala");

        CHECK(modo.getComodosRelacionados().size() == 1);
        CHECK(modo.getComodosRelacionados()[0]->getNome() == "Quarto");
    }

    SUBCASE("Remover comodo inexistente deve lancar excecao") {

        CHECK_THROWS(modo.removerComodoRelacionado("Sala"));
    }
}