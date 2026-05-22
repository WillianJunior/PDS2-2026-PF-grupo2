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

    return Sensor(true, true, objetosConectados, modosConectados);
}

TEST_CASE("Construtor ObjetoInteligente inicializa corretamente") {
    Sensor sensor = DummySensorObjeto();

    std::vector<Sensor*> sensores = {&sensor};
    std::vector<std::string> status = {"Ligado", "Desligado"};
    float consumo = 12.5f;
    std::vector<std::function<void()>> funcoes = {[](){}, [](){}};
    std::vector<std::function<void()>> funcoesRestritas = {[](){}};

    ObjetoInteligente obj(
        true,
        sensores,
        status,
        consumo,
        funcoes,
        funcoesRestritas
    );

    CHECK(obj.getSensores().size() == 1);
    CHECK(obj.getConsumoMedioDeEnergia() == 12.5f);
    CHECK(obj.getFuncoes().size() == 2);
    CHECK(obj.getFuncoesRestritas().size() == 1);

    SUBCASE("ObjetoInteligente pode ser criado com valores vazios") {
        ObjetoInteligente objVazio(false, {}, {}, 0.0f, {}, {});
        CHECK(objVazio.getSensores().empty());
        CHECK(objVazio.getStatus() == "");
        CHECK(objVazio.getFuncoes().empty());
    }

    SUBCASE("ObjetoInteligente com funcoes vazias") {
        ObjetoInteligente objFuncoes(false, {}, {}, 1.0f, {[](){}}, {});
        CHECK(objFuncoes.getFuncoes().size() == 1);
    }
}

TEST_CASE("Status pode ser definido e recuperado") {
    ObjetoInteligente obj(
        false,
        {},
        {"Ligado", "Desligado"},
        5.0f,
        {},
        {}
    );

    obj.setStatusAtual("Ligado");
    CHECK(obj.getStatus() == "Ligado");

    obj.setStatusAtual("Desligado");
    CHECK(obj.getStatus() == "Desligado");
}