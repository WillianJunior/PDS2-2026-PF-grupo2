#include "doctest.h"

#include <vector>
#include <string>
#include <functional>

#include "ObjetoInteligente.hpp"
#include "Sensor.hpp"
#include "Modo.hpp"
#include "Comodo.hpp"
#include "Conta.hpp"
#include "Smarthome.hpp"

static Sensor DummySensorObjeto() {
    static Conta contaTeste("1", "Maria", "maria@email.com", "senha123", true);
    static Smarthome smarthomeDummy(&contaTeste, "MinhaCasa");
    static Comodo comodoDummy("sala", &smarthomeDummy);

    std::vector<ObjetoInteligente*> objetosConectados;
    std::vector<Modo*> modosConectados;

    return Sensor(
        "sensorTeste",
        true,
        true,
        &comodoDummy,
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

    CHECK(obj.getNome() == "objetoTeste");
    CHECK(obj.getSensores().size() == 1);
    CHECK(obj.getConsumoMedioDeEnergia() == doctest::Approx(12.5f));
    CHECK(obj.getFuncoes().size() == 2);
    CHECK(obj.getFuncoesRestritas().size() == 1);
    CHECK(obj.getRestricaoAdulto() == true);

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

    SUBCASE("ObjetoInteligente com nome vazio") {
        CHECK_THROWS_WITH(
            ObjetoInteligente("", false, {}, {}, "", 0.0f, {}, {}),
            "Nome do Obejeto nao pode ser vazio - Tente novamente..."
        );
    }

    SUBCASE("ObjetoInteligente com nome longo") {
        CHECK_THROWS_WITH(
            ObjetoInteligente("Nomemuitoooolooongooo", false, {}, {}, "", 0.0f, {}, {}),
            "Nome do Objeto nao pode ter tamanho maior que 20 - Tente novamente..."
        );
    }

    SUBCASE("ObjetoInteligente com nome com caracteres invalidos") {
        CHECK_THROWS_WITH(
            ObjetoInteligente("## $% ##", false, {}, {}, "", 0.0f, {}, {}),
            "Nome do Objeto com usos de caracteres invalidos - Tente novamente..."
        );
    }
}

TEST_CASE("Status pode ser definido e recuperado") {
    ObjetoInteligente obj(
        "objetoTeste",
        false,
        {},
        {"Ligado", "Desligado"},
        "",
        5.0f,
        {},
        {}
    );

    SUBCASE("Define status Ligado") {
        obj.setStatusAtual("Ligado");
        CHECK(obj.getStatusAtual() == "Ligado");
    }

    SUBCASE("Define status Desligado") {
        obj.setStatusAtual("Desligado");
        CHECK(obj.getStatusAtual() == "Desligado");
    }

    SUBCASE("Status atual passado eh invalido") {
        CHECK_THROWS_WITH(
            obj.setStatusAtual("StatusInvalido"),
            "Status invalido para este objeto"
        );
    }
}

TEST_CASE("getSensores retorna os sensores associados") {
    Sensor sensor1 = DummySensorObjeto();
    Sensor sensor2 = DummySensorObjeto();

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

TEST_CASE("Objetos inteligentes especificos, protocolos, falhas e controle parental") {
    SUBCASE("Objetos possuem protocolos padrao corretos") {
        TV tv("TVSala");
        ArCondicionado ar("ArSala");
        CaixaDeSom som("SomSala");
        Portao portao("Portao");
        Termostato termostato("Termostato");

        CHECK(tv.getProtocolo() == Protocolo::WIFI);
        CHECK(ar.getProtocolo() == Protocolo::WIFI);
        CHECK(som.getProtocolo() == Protocolo::BLUETOOTH);
        CHECK(portao.getProtocolo() == Protocolo::ZIGBEE);
        CHECK(termostato.getProtocolo() == Protocolo::ZIGBEE);
    }

    SUBCASE("Objetos com mesmo protocolo conseguem se comunicar") {
        TV tv("TVSala");
        ArCondicionado ar("ArSala");
        Portao portao("Portao");
        Termostato termostato("Termostato");

        CHECK(tv.comunicaCom(ar));
        CHECK(ar.comunicaCom(tv));
        CHECK(portao.comunicaCom(termostato));
    }

    SUBCASE("Objetos com protocolos diferentes nao conseguem se comunicar") {
        TV tv("TVSala");
        CaixaDeSom som("SomSala");
        Portao portao("Portao");

        CHECK_FALSE(tv.comunicaCom(som));
        CHECK_FALSE(tv.comunicaCom(portao));
        CHECK_FALSE(som.comunicaCom(portao));
    }

    SUBCASE("Controle parental diferencia objetos restritos e liberados") {
        TV tv("TVSala");
        CaixaDeSom som("SomSala");
        ArCondicionado ar("ArSala");
        Portao portao("Portao");
        Luz luz("LuzSala");
        Termostato termostato("Termostato");

        CHECK(tv.getRestricaoAdulto());
        CHECK(som.getRestricaoAdulto());
        CHECK(ar.getRestricaoAdulto());
        CHECK(portao.getRestricaoAdulto());

        CHECK_FALSE(luz.getRestricaoAdulto());
        CHECK_FALSE(termostato.getRestricaoAdulto());
    }

    SUBCASE("Simular falha bloqueia alteracao de status") {
        TV tv("TVSala");

        CHECK_FALSE(tv.estaEmFalha());

        tv.simularFalha();

        CHECK(tv.estaEmFalha());
        CHECK_THROWS_WITH(
            tv.setStatusAtual("ligada"),
            "Objeto TVSala esta em falha"
        );
    }

    SUBCASE("Reparar falha permite alterar status novamente") {
        TV tv("TVSala");

        tv.simularFalha();
        CHECK(tv.estaEmFalha());

        tv.repararFalha();

        CHECK_FALSE(tv.estaEmFalha());
        CHECK_NOTHROW(tv.setStatusAtual("ligada"));
        CHECK(tv.getStatusAtual() == "ligada");
    }

    SUBCASE("ArCondicionado valida temperatura permitida") {
        ArCondicionado ar("ArSala");

        ar.setTemperatura(22.0f);
        CHECK(ar.getTemperatura() == doctest::Approx(22.0f));

        CHECK_THROWS(ar.setTemperatura(10.0f));
        CHECK_THROWS(ar.setTemperatura(35.0f));
    }

    SUBCASE("Termostato valida temperatura medida") {
        Termostato termostato("Termostato");

        termostato.setTemperaturaAtual(30.0f);
        CHECK(termostato.getTemperaturaAtual() == doctest::Approx(30.0f));

        CHECK_THROWS(termostato.setTemperaturaAtual(-20.0f));
        CHECK_THROWS(termostato.setTemperaturaAtual(100.0f));
    }

    SUBCASE("Objetos especificos alteram status corretamente") {
        Luz luz("LuzSala");
        CaixaDeSom som("SomSala");
        Portao portao("Portao");
        ArCondicionado ar("ArSala");

        luz.setStatusAtual(1);
        CHECK(luz.getStatusAtual() == "acesa");

        luz.setStatusAtual(0);
        CHECK(luz.getStatusAtual() == "apagada");

        som.setStatusAtual(2);
        CHECK(som.getStatusAtual() == "tocando música");

        portao.abrir();
        CHECK(portao.getStatusAtual() == "aberto");

        portao.fechar();
        CHECK(portao.getStatusAtual() == "fechado");

        ar.resfriar();
        CHECK(ar.getStatusAtual() == "resfriando");

        ar.desligar();
        CHECK(ar.getStatusAtual() == "desligado");
    }
}