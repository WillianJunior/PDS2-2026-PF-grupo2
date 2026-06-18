#include "doctest.h"

#include <vector>
#include <string>
#include <functional>

#include "ObjetoInteligente.hpp"
#include "Sensor.hpp"
#include "Modo.hpp"

static Sensor DummySensorObjeto() {
    std::vector<ObjetoInteligente*> objetosConectados;
    std::vector<Modo*> modosConectados;

    Comodo comodo("sala", nullptr);

    return Sensor(
        "sensorTeste",
        true,
        true,
        comodo,
        objetosConectados,
        modosConectados
    );
}

TEST_CASE("Construtor ObjetoInteligente inicializa corretamente") {
    Sensor sensor = DummySensorObjeto();

    std::vector<Sensor*> sensores = {&sensor};
    std::vector<std::string> status = {"Ligado", "Desligado"};
    float consumo = 12.5f;
    std::vector<std::function<void()>> funcoes = {[](){}, [](){}};
    std::vector<std::function<void()>> funcoesRestritas = {[](){}};

    ObjetoInteligente obj(
        "objetoTeste",
        true,
        sensores,
        status,
        "statusTeste",
        consumo,
        funcoes,
        funcoesRestritas
    );

    CHECK(obj.getSensores().size() == 1);
    CHECK(obj.getConsumoMedioDeEnergia() == 12.5f);
    CHECK(obj.getFuncoes().size() == 2);
    CHECK(obj.getFuncoesRestritas().size() == 1);

    SUBCASE("ObjetoInteligente pode ser criado com valores vazios menos nome") {
        ObjetoInteligente objVazio("ObjetoTeste", false, {}, {}, "", 0.0f, {}, {});
        CHECK(objVazio.getSensores().empty());
        CHECK(objVazio.getStatusAtual() == "");
        CHECK(objVazio.getFuncoes().empty());
    }

    SUBCASE("ObjetoInteligente com funcoes vazias") {
        ObjetoInteligente objFuncoes("ObjetoTeste", false, {}, {}, "", 1.0f, {[](){}}, {});
        CHECK(objFuncoes.getFuncoes().size() == 1);
    }

    SUBCASE("ObjetoInteligente com nome vazio"){
        CHECK_THROWS_WITH(ObjetoInteligente objNomeVazio("", false, {}, {}, "", 0.0f, {}, {}),
         "Nome do Objeto nao pode ser vazio - Tente novamente...");
    }

    SUBCASE("ObjetoInteligente com nome longo"){
        CHECK_THROWS_WITH(ObjetoInteligente objNomeLongo("Nomemuitoooolooongooo", false, {}, {}, "", 0.0f, {}, {}),
        "Nome do Objeto nao pode ter tamanho maior que 20 - Tente novamente...");
    }

    SUBCASE("ObjetoInteligente com nome com carcteres invalidos"){
        CHECK_THROWS_WITH(ObjetoInteligente objNomeInvalido("## $% ##", false, {}, {}, "", 0.0f, {}, {}),
        "Nome do Objeto com usos de caracteres invalidos - Tente novamente...");
    }
}

TEST_CASE("Status pode ser definido e recuperado") {
    ObjetoInteligente obj(
        "",
        false,
        {},
        {"Ligado", "Desligado"},
        "",
        5.0f,
        {},
        {}
    );

    obj.setStatusAtual("Ligado");
    CHECK(obj.getStatusAtual() == "Ligado");

    obj.setStatusAtual("Desligado");
    CHECK(obj.getStatusAtual() == "Desligado");

    SUBCASE("Status atual passado eh invalido"){
        CHECK_THROWS_WITH(obj.setStatusAtual("StatusInvalido"),
        "Status invalido para este objeto");
    }
}

TEST_CASE("getSensores retorna os sensores associados") {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Modo*> modos;

    Comodo comodo("sala", nullptr);

    Sensor sensor1(
        "sensor1",
        true,
        false,
        comodo,
        objetos,
        modos
    );

    Sensor sensor2(
        "sensor2",
        true,
        true,
        comodo,
        objetos,
        modos
    );

    std::vector<Sensor*> sensores = {&sensor1, &sensor2};

    ObjetoInteligente obj(
        "objetoTeste",
        false,
        sensores,
        {},
        "",
        0.0f,
        {},
        {}
    );

    std::vector<Sensor*> sensoresRetornados = obj.getSensores();

    CHECK(sensoresRetornados.size() == 2);
    CHECK(sensoresRetornados[0] == &sensor1);
    CHECK(sensoresRetornados[1] == &sensor2);
}

TEST_CASE("operador == detecta nome diferente") {

    ObjetoInteligente obj1(
        "Lampada",
        false,
        {},
        {},
        "",
        10.0f,
        {},
        {}
    );

    ObjetoInteligente obj2(
        "TV",
        false,
        {},
        {},
        "",
        10.0f,
        {},
        {}
    );

    CHECK_FALSE(obj1 == obj2);
}

TEST_CASE("getStatusPossiveis retorna os status corretos") {

    std::vector<std::string> status = {
        "Quente",
        "Frio",
        "Morno"
    };

    ObjetoInteligente obj(
        "objetoTeste",
        false,
        {},
        status,
        "Desligado",
        0.0f,
        {},
        {}
    );

    CHECK(obj.getStatusPossiveis() == status);
}

TEST_CASE("getConsumoMedioDeEnergia retorna o consumo correto") {

    ObjetoInteligente obj(
        "objetoTeste",
        false,
        {},
        {},
        "",
        15.5f,
        {},
        {}
    );

    CHECK(obj.getConsumoMedioDeEnergia() == doctest::Approx(15.5f));
}