#include <vector>
#include <string>
#include <iostream>
#include "Smarthome.hpp"
#include "Sensor.hpp"
#include "doctest.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN



   // SmartHome(Conta usuario, string nome);
TEST_CASE("TESTE 1 construtor - Smarthome"){
    std::string id = "1";
    Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(contaTeste, "Minha Casa");
    
    CHECK(smarthome.getNomeUsuario() == "Usuario A");
    CHECK(smarthome.getNome() == "Minha Casa");
        SUBCASE("TESTE 1.1 nome da smarthome eh vazio"){
            Smarthome smarthome2(contaTeste, "");
            CHECK(smarthome2.getNome() == "");
            CHECK(smarthome.getNomeUsuario() == "Usuario A");
        }
        SUBCASE("TESTE 1.2 usuario da smarthome tem nome vazio"){
            std::string id2 = "2";
            Conta contaTeste2(id2, "", "usuario@email.com", "senha12", true);
            Smarthome smarthome3(contaTeste2, "Minha Casa");
            CHECK(smarthome3.getNomeUsuario() == "");
            CHECK(smarthome3.getNome() == "Minha Casa");
        }
        SUBCASE("TESTE 1.3nome da smarthome eh longo"){
            std::string longName(1000, 'A');
            Smarthome smarthome4(contaTeste, longName);
            CHECK(smarthome4.getNome().size() = 1000);
        }
        SUBCASE("TESTE 1.4 nome do usuario da smarthome eh longo"){
            std::string longName(1000, 'A');
            std :: string id3 = "3";
            Smarthome smarthome5(contaTeste, longName);
            Conta contaTeste3(id3, longName, "user@email.com", "senha1", true);
            CHECK(smarthome5.getNome().size() = 1000);
        }
 }
    //void adicionarModo(Modo& modo);                  isso é referencia? preciso testar nullptr?
TEST_CASE("TESTE 2 adicionarModo - Smarthome"){
    std::string id = "1";
    Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome casaTeste(contaTeste, "Minha Casa");          

    std::vector<ObjetoInteligente> objetos; //vazios por enquanto
    std::vector<Comodo> comodos;

    Modo modoTeste(objetos, comodos, true, false);
    casaTeste.adicionarModo(modoTeste);

    CHECK(casaTeste.getQuantidadeModos() == 1);
        SUBCASE("TESTE 2.1 adiciona modos iguais"){
            Modo modoTeste(objetos, comodos, true, false);
            casaTeste.adicionarModo(modoTeste);
            CHECK(casaTeste.getQuantidadeModos() == 1);
            Modo modoTeste(objetos, comodos, true, false);
            casaTeste.adicionarModo(modoTeste); 
            CHECK(casaTeste.getQuantidadeModos() == 1); 
        }
    }

    //void adicionarComodo(Comodo& comodo);
TEST_CASE("TESTE 3 adicionarComodo - Smarthome"){
    std::string id = "1";
    Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome casaTeste(contaTeste, "Minha Casa");

    Comodo comodoTeste("comodoTeste", &casaTeste);
    casaTeste.adicionarComodo(comodoTeste);

    CHECK(casaTeste.getQuantidadeComodos() == 1);
        SUBCASE("TESTE 3.1 adiciona comodos iguais"){
            Comodo comodoTeste("comodoTeste", &casaTeste);
            casaTeste.adicionarComodo(comodoTeste);
            CHECK(casaTeste.getQuantidadeComodos() == 1);
            Comodo comodoTeste("comodoTeste", &casaTeste);
            casaTeste.adicionarComodo(comodoTeste); 
            CHECK(casaTeste.getQuantidadeComodos() == 1); 
        }
}

    //void adicionarObjeto(Objeto& objeto);
TEST_CASE("TESTE 4 adicionarObjeto - Smarthome"){
    std::string id = "1";
    Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<Sensor> sensores;
    std::vector<std::string> statusPossiveis = { "Ligado", "Desligado" };
    float consumoMedio = 11.5f;

    std::vector<std::function<void()>> funcoes = { [](){ /* ação fake */ } };
    std::vector<std::function<void()>> funcoesRestritas = { [](){ /* ação restrita fake */ } };

    ObjetoInteligente objetoTeste(false, sensores, statusPossiveis, consumoMedio, funcoes, funcoesRestritas);
    casaTeste.adicionarObjeto(objetoTeste);

    CHECK(casaTeste.getQuantidadeObjetos() == 1);
        SUBCASE("TESTE 4.1 adiciona objetos iguais"){
            ObjetoInteligente objetoTeste(false, sensores, statusPossiveis, consumoMedio, funcoes, funcoesRestritas);
            casaTeste.adicionarObjeto(objetoTeste);
            CHECK(casaTeste.getQuantidadeObjetos() == 1);
            ObjetoInteligente objetoTeste(false, sensores, statusPossiveis, consumoMedio, funcoes, funcoesRestritas);
            casaTeste.adicionarObjeto(objetoTeste); 
            CHECK(casaTeste.getQuantidadeObjetos() == 1); 
        }
    }




