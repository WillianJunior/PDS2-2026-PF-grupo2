#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "Smarthome.hpp"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include "Comodo.hpp"

#include "doctest.h"


TEST_CASE("TESTE 1 construtor - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome smarthome(contaTeste, "Minha Casa");

    CHECK(smarthome.getNome() == "Minha Casa");

    CHECK(smarthome.getUsuario().getNome() == contaTeste.getNome());

    SUBCASE("TESTE 1.1 nome da smarthome nao pode ser vazio") {
    
        CHECK_THROWS_WITH( Smarthome(contaTeste, ""), "Nome da SmartHome nao pode ser vazio");
    }

    SUBCASE("TESTE 1.2  nome da smarthome eh longo"){
        std::string longName(21, 'A');

        CHECK_THROWS_WITH(Smarthome smarthome2(contaTeste, longName), "Nome da SmartHome nao pode ter tamanho maior que 20");
    }

    SUBCASE("TESTE 1.3 nome da smarthome contem caracteres invalidos") {
        std :: string InvalidName (10, '§');

        CHECK_THROWS_WITH(Smarthome (contaTeste, InvalidName), "Nome da SmartHome com usos de caracteres invalidos");
    }
}

TEST_CASE("TESTE 2 adicionarModo - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;
    std::string nome;

    Modo modoTeste("ModoTeste", objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);

    CHECK(casaTeste.getQuantidadeModos() == 1);

    SUBCASE("TESTE 2.1 modo duplicado nao adiciona") {
        casaTeste.adicionarModo(modoTeste);
       CHECK(casaTeste.getQuantidadeModos() == 1);
    }
}

TEST_CASE("TESTE 3 adicionarComodo - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    Comodo comodoTeste("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(comodoTeste);

    CHECK(casaTeste.getQuantidadeComodos() == 1);

    SUBCASE("TESTE 3.1 comodo duplicado nao adiciona") {
        casaTeste.adicionarComodo(comodoTeste);
       CHECK(casaTeste.getQuantidadeComodos() == 1);
    }

}

TEST_CASE("TESTE 4 adicionarObjeto - Smarthome") {

    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<Sensor*> sensores;

    std::vector<std::string> statusPossiveis = {
        "Ligado",
        "Desligado"
    };

    float consumoMedio = 11.5f;

    std::vector<std::function<void()>> funcoes = {
        [](){}
    };
    std::vector<std::function<void()>> funcoesRestritas = {
        [](){}
    };

    ObjetoInteligente objetoTeste(
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(objetoTeste);

    CHECK(casaTeste.getQuantidadeObjetos() == 1);

    SUBCASE("TESTE 4.1 objeto duplicado nao adiciona"){
        casaTeste.adicionarObjeto(objetoTeste);
        CHECK(casaTeste.getQuantidadeObjetos() == 1);
    }
}
TEST_CASE("TESTE 5 removerComodo - Smarthome"){
    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    Comodo comodoTeste("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(comodoTeste);

    CHECK(casaTeste.getQuantidadeComodos() == 1);

    casaTeste.removerComodo(comodoTeste);

    CHECK(casaTeste.getQuantidadeComodos() == 0);

    SUBCASE("TESTE 5.1 remocao de comodo nao existente na smarthome nao funciona"){
        Comodo comodoTeste2("comodoTeste2", &casaTeste);

        CHECK_THROWS_WITH(casaTeste.removerComodo(comodoTeste2), "Comodo comodoTeste2 nao encontrado na smarthome Minha Casa para remocao");
    }
}

// ---- implementação incompleta dos metodos seguintes -----

TEST_CASE("TESTE 6 printComodosInfo - Smarthome"){
    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    Comodo comodoTeste("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(comodoTeste);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    casaTeste.printComodosInfo();
    
    std::cout.rdbuf(oldCout);
    
    //CHECK(oss.str() == );
}

TEST_CASE("TESTE 7 printObjetosInfo - Smarthome"){
     std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<Sensor*> sensores;

    std::vector<std::string> statusPossiveis = {
        "Ligado",
        "Desligado"
    };

    float consumoMedio = 11.5f;

    std::vector<std::function<void()>> funcoes = {
        [](){}
    };

    std::vector<std::function<void()>> funcoesRestritas = {
        [](){}
    };

    ObjetoInteligente objetoTeste(
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(objetoTeste);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    casaTeste.printObjetosInfo();

    std::cout.rdbuf(oldCout);
    //CHECK();
}
TEST_CASE("TESTE 8 printModosInfo - Smarthome"){
     std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;
    std::string nome;

    Modo modoTeste("ModoTeste", objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);
    // Captura a saída do cout
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    casaTeste.printModosInfo();

    // Restaura cout
    std::cout.rdbuf(oldCout);

    CHECK(oss.str() == 
        "Smarthome Minha Casa de: Usuario A\n"
        "Modos presentes em Minha Casa :\n"
        "Nome do modo: ModoTeste\n"
        "Estado: Ligado\n"
        "Bloqueio: Desbloqueado\n"
        "Objetos relacionados: 0\n"
        "Comodos relacionados: 0\n"
    );
    SUBCASE("TESTE 8.1 smarthome sem modos nao imprime nada "){
        Smarthome casaTeste2(contaTeste, "Minha Casa2");
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        casaTeste2.printModosInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str().empty());
    }
}

TEST_CASE("TESTE 9 removerObjeto - Smarthome"){
    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");


    std::vector<Sensor*> sensores;

    std::vector<std::string> statusPossiveis = {
        "Ligado",
        "Desligado"
    };

    float consumoMedio = 11.5f;

    std::vector<std::function<void()>> funcoes = {
        [](){}
    };
    std::vector<std::function<void()>> funcoesRestritas = {
        [](){}
    };

    ObjetoInteligente objetoTeste(
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(objetoTeste);

    CHECK(casaTeste.getQuantidadeObjetos() == 1);

    casaTeste.removerObjeto("ObjetoTeste");

    CHECK(casaTeste.getQuantidadeObjetos() == 0);

    SUBCASE("TESTE 9.1 remocao de objeto nao existente na smarthome nao funciona"){
       ObjetoInteligente objetoTeste2(
        "ObjetoTeste2",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

        CHECK_THROWS_WITH(casaTeste.removerObjeto("ObjetoTeste2"), "Comodo ObjetoTeste2 nao encontrado na smarthome Minha Casa para remocao");
    }
}

TEST_CASE("TESTE 10 removerModo - Smarthome"){
    std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");


    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;
    std::string nome;

    Modo modoTeste("ModoTeste", objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);

    CHECK(casaTeste.getQuantidadeModos() == 1);

    casaTeste.removerObjeto("ModoTeste");

    CHECK(casaTeste.getQuantidadeObjetos() == 0);

    SUBCASE("TESTE 10.1 remocao de modo nao existente na smarthome nao funciona"){
       Modo modoTeste2("ModoTeste2", objetos, comodos, true, false);

        CHECK_THROWS_WITH(casaTeste.removerObjeto("ModoTeste2"), "Comodo ModoTeste2 nao encontrado na smarthome Minha Casa para remocao");
    }
}

TEST_CASE("TESTE 11 CaracteresValidos - Smarthome") {
     std::string id = "1";

    Conta contaTeste(
        id,
        "Usuario A",
        "usuarioA@email.com",
        "senha123",
        true
    );

    Smarthome casaTeste(contaTeste, "Minha Casa");

    SUBCASE("TESTE 11.5 nome valido - apenas letras e numeros") {
        CHECK(casaTeste.CaracteresValidos("Casa123") == true);
    }

    SUBCASE("TESTE 11.2 nome valido - com espaços") {
        CHECK(casaTeste.CaracteresValidos("Minha Casa") == true);
    }

    SUBCASE("TESTE 11.3 nome invalido - contem caractere especial") {
        CHECK(casaTeste.CaracteresValidos("Casa@123") == false);
    }

    SUBCASE("TESTE 11.4 nome invalido - contem símbolo §") {
        CHECK(casaTeste.CaracteresValidos("§c4s4§") == false);
    }

    SUBCASE("TESTE 11.5 nome vazio eh tecnicamente valido") {
        CHECK(casaTeste.CaracteresValidos("") == true);
        // Aqui eh invalido mas esse tipo de erro nao eh tratado nesse metodo
    }
}