#include "doctest.h"
#include "ObjetoInteligente.hpp"

Sensor DummySensor(){
   std::vector<ObjetoInteligente> objetosConectados;
   std::vector<Modo> modosConectados;
   return Sensor(true, true, objetosConectados, modosConectados);
}

TEST_CASE("Construtor ObjetoInteligente inicializa corretamente") {
    std::vector<Sensor> sensores = { DummySensor() };
    std::vector<std::string> status = { "Ligado", "Desligado" };
    float consumo = 12.5f;
    std::vector<std::function<void()>> funcoes = { [](){}, [](){} };
    std::vector<std::function<void()>> funcoesRestritas = { [](){} };

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
        ObjetoInteligente obj(false, {}, {}, 0.0f, {}, {});
        CHECK(obj.getSensores().empty());
        CHECK(obj.getStatus() == "");
        CHECK(obj.getFuncoes().empty());
    }
    SUBCASE("ObjetoInteligente com funcoes vazias"){
        ObjetoInteligente obj(false, {}, {}, 1.0f, { [](){} }, {});
        CHECK(obj.getFuncoes().size() == 1);
    }
    
    SUBCASE("ObjetoInteligente com consumo negativo"){
        CHECK_THROWS( ObjetoInteligente (false, {}, {"Ligado"}, -5.0f, {}, {}));
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

    SUBCASE("ObjetoInteligente tenta usar Status inexistente"){
        CHECK_THROWS(obj.setStatusAtual("Inexistente"));
    }
}
