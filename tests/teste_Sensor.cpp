#include "doctest.h"

#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"

#include <vector>

TEST_CASE("Teste 01: Inicializacao do Sensor") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor("sensorTeste", true, false, &comodo, objetos, modos);

    CHECK(sensor.getEstaLigado() == true);
    CHECK(sensor.getEstaAtivado() == false);

    SUBCASE("Nome vazio lança exceção") {
        std::vector<ObjetoInteligente*> objetos;
        std::vector<Modo*> modos;
        Comodo comodo("Sala", nullptr);
        CHECK_THROWS_WITH(Sensor("", true, false, &comodo, objetos, modos),
            "Nome do Sensor nao pode ser vazio - Tente novamente...");
    }

    SUBCASE("Nome longo lança exceção") {
        std::string longName(25, 'A');
        std::vector<ObjetoInteligente*> objetos;
        std::vector<Modo*> modos;
        Comodo comodo("Sala", nullptr);
        CHECK_THROWS_WITH(Sensor(longName, true, false, &comodo, objetos, modos),
            "Nome do Sensor nao pode ter tamanho maior que 20 - Tente novamente...");
    }

    SUBCASE("Nome com caracteres inválidos lança exceção") {
        std::vector<ObjetoInteligente*> objetos;
        std::vector<Modo*> modos;
        Comodo comodo("Sala", nullptr);
        CHECK_THROWS_WITH(Sensor("Sensor@", true, false, &comodo, objetos, modos),
            "Nome do Sensor com usos de caracteres invalidos - Tente novamente...");
    }
}

TEST_CASE("Teste 02: Metodo setEstaLigado") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor("sensorTeste", false, false, &comodo, objetos, modos);

    sensor.setEstaLigado(1);

    CHECK(sensor.getEstaLigado() == true);
}

TEST_CASE("Teste 03: Metodo setEstaAtivado") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor("sensorTeste", true, false, &comodo, objetos, modos);

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
        &comodo,
        objetos,
        modos
    );

    Sensor sensor2(
        "SensorTeste",
        true,
        false,
        &comodo,
        objetos,
        modos
    );

    CHECK(sensor1 == sensor2);
}

TEST_CASE("checarAmbiente encontra condicoes existentes") { //consertar inconsistencias no funcionamento

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("Sala", nullptr);

    comodo.adicionarCondicao("quente");
    comodo.adicionarCondicao("iluminado");

    Sensor sensor(
        "SensorTeste",
        true,
        true,
        &comodo,
        objetos,
        modos
    );

    CHECK(sensor.checarAmbiente("quente"));
    CHECK(sensor.checarAmbiente("iluminado"));
    CHECK_FALSE(sensor.checarAmbiente("frio"));

    SUBCASE("Condicao vazia lança exceção") {
        std::vector<ObjetoInteligente*> objetos;
        std::vector<Modo*> modos;
        Comodo comodo("Sala", nullptr);
        Sensor sensor("SensorTeste", true, true, &comodo, objetos, modos);
        CHECK_THROWS_WITH(sensor.checarAmbiente(""),
            "Condicao vazia passada para checarAmbiente no Sensor SensorTeste");
    }

}

TEST_CASE("ativarModo ativa um modo") {

    Comodo comodo("Sala", nullptr);

    Sensor sensor(
        "SensorTeste",
        true,
        true,
        &comodo,
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

    SUBCASE("Modo nulo lança exceção") {
        Comodo comodo("Sala", nullptr);
        Sensor sensor("SensorTeste", true, true, &comodo, {}, {});
        CHECK_THROWS_WITH(sensor.ativarModo(nullptr),
            "Tentativa de ativar modo nulo pelo Sensor SensorTeste");
    }

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
        &comodo,
        {},
        {}
    );

    CHECK_FALSE(executou);

    sensor.ativarObjeto(&objeto, 0);

    CHECK(executou);

    SUBCASE("Objeto nulo lança exceção") {
        Comodo comodo("Sala", nullptr);
        Sensor sensor("SensorTeste", true, true, &comodo, {}, {});
        CHECK_THROWS_WITH(sensor.ativarObjeto(nullptr, 0),
            "Tentativa de ativar objeto nulo pelo Sensor SensorTeste");
    }

    SUBCASE("Index fora do intervalo lança exceção") {
        bool executou = false;
        std::vector<std::function<void()>> funcoes = { [&executou]() { executou = true; } };
        ObjetoInteligente objeto("objetoTeste", false, {}, {}, "", 0.0f, funcoes, {});
        Comodo comodo("Sala", nullptr);
        Sensor sensor("SensorTeste", true, true, &comodo, {}, {});
        CHECK_THROWS_WITH(sensor.ativarObjeto(&objeto, 5),
            "Index de funcao invalido para objeto objetoTeste");
    }

}