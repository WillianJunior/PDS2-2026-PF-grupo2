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

    Smarthome smarthome(&contaTeste, "Minha Casa");

    CHECK(smarthome.getNome() == "Minha Casa");

    CHECK(smarthome.getUsuario()->getNome() == contaTeste.getNome());

    SUBCASE("TESTE 1.1 nome da smarthome nao pode ser vazio") {
    
        CHECK_THROWS_WITH( Smarthome(&contaTeste, ""), "Nome da SmartHome nao pode ser vazio");
    }

    SUBCASE("TESTE 1.2  nome da smarthome eh longo"){
        std::string longName(21, 'A');

        CHECK_THROWS_WITH(Smarthome smarthome2(&contaTeste, longName), "Nome da SmartHome nao pode ter tamanho maior que 20");
    }

    SUBCASE("TESTE 1.3 nome da smarthome contem caracteres invalidos") {
         std::string InvalidName = "§c4s4§";

        CHECK_THROWS_WITH(Smarthome (&contaTeste, InvalidName), "Nome da SmartHome com usos de caracteres invalidos");
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

    auto comodoTeste = std::make_unique<Comodo> ("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(std::move(comodoTeste));

    CHECK(casaTeste.getQuantidadeComodos() == 1);

    SUBCASE("TESTE 3.1 comodo duplicado nao adiciona") {
       auto comodoTeste2 = std::make_unique<Comodo> ("comodoTeste", &casaTeste);
       casaTeste.adicionarComodo(std::move(comodoTeste2));
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

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

    auto objetoTeste = std::make_unique<ObjetoInteligente> (
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(std::move(objetoTeste));

    CHECK(casaTeste.getQuantidadeObjetos() == 1);

    SUBCASE("TESTE 4.1 objeto duplicado nao adiciona"){
        auto objetoTeste2 = std::make_unique<ObjetoInteligente> (
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
        );
        casaTeste.adicionarObjeto(std::move(objetoTeste2));
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

    auto comodoTeste = std::make_unique<Comodo> ("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(std::move(comodoTeste));

    CHECK(casaTeste.getQuantidadeComodos() == 1);
    Comodo* c = casaTeste.getComodo("comodoTeste");
    casaTeste.removerComodo(*c); 

    CHECK(casaTeste.getQuantidadeComodos() == 0);

    SUBCASE("TESTE 5.1 remocao de comodo nao existente na smarthome nao funciona"){
        CHECK_THROWS_WITH(casaTeste.removerComodoPorNome("comodoTeste2"),
        "Comodo comodoTeste2 nao encontrado na smarthome Minha Casa para remocao");
        //nao da pra usar removerComodo porque com nullptr da undefined behaviour
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

    auto comodoTeste = std::make_unique<Comodo>("comodoTeste", &casaTeste);

    casaTeste.adicionarComodo(std::move(comodoTeste));

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    casaTeste.printComodosInfo();
    
    std::cout.rdbuf(oldCout);
    
    
    std::istringstream iss(oss.str());
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(iss, linha)) {
        linhas.push_back(linha);
    }

    CHECK(linhas[0] =="Smarthome Minha Casa de: Usuario A");
    CHECK(linhas[1] =="Comodos presentes em Minha Casa :");
    CHECK(linhas[2] =="comodoTeste");
    CHECK(linhas[3] =="Iluminado Escuro Quente Frio Umido Seco Barulhento Silencioso ");
    CHECK(linhas[4] =="Comodo comodoTeste :");
    CHECK(linhas[5] =="Objetos inteligentes presentes em comodoTeste :");
    CHECK(linhas[6] =="Comodo comodoTeste :");
    CHECK(linhas[7] =="Modos presentes em comodoTeste :");
    CHECK(linhas[8] =="Comodo comodoTeste :");
    CHECK(linhas[9] =="Sensores presentes em comodoTeste :");
    CHECK(linhas[10] =="Comodo comodoTeste :");
    CHECK(linhas[11] =="Contas presentes em comodoTeste :");
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

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

    auto objetoTeste = std::make_unique<ObjetoInteligente> (
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(std::move(objetoTeste));

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    casaTeste.printObjetosInfo();

    std::cout.rdbuf(oldCout);
   std::istringstream iss(oss.str());
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(iss, linha)) {
        linhas.push_back(linha);
    }

    CHECK(linhas[0] == "Smarthome Minha Casa de: Usuario A");
    CHECK(linhas[1] == "Objetos Inteligentes presentes em Minha Casa :");
    CHECK(linhas[2] == "Objeto ObjetoTeste");
    CHECK(linhas[3] == "Objeto tem restrição parental? Nao");
    CHECK(linhas[4] == "Consumo médio de energia: 11.5");
    CHECK(linhas[5] == "Protocolo: WiFi");
    CHECK(linhas[6] == "Em falha? Nao");
    CHECK(linhas[7] == "Sensores conectados: ");
    CHECK(linhas[8] == "Status possíveis: Ligado Desligado ");
    CHECK(linhas[9] == "Status atual: Ligado");
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

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

    std::istringstream iss(oss.str());
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(iss, linha)) {
        linhas.push_back(linha);
    }

    CHECK(linhas[0] =="Smarthome Minha Casa de: Usuario A");
    CHECK(linhas[1] == "Modos presentes em Minha Casa :");
    CHECK(linhas[2] == "Nome do modo: ModoTeste");
    CHECK(linhas[3] == "Estado: Ligado");
    CHECK(linhas[4] == "Bloqueio: Desbloqueado");
    CHECK(linhas[5] == "Objetos relacionados: 0");
    CHECK(linhas[6] == "Comodos relacionados: 0");

    SUBCASE("TESTE 8.1 smarthome sem modos nao imprime nada "){
        Smarthome casaTeste2(&contaTeste, "Minha Casa2");
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        casaTeste2.printModosInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str()== "Smarthome Minha Casa2 de: Usuario A\n"
        "Modos presentes em Minha Casa2 :\n");
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");


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

    auto objetoTeste = std::make_unique<ObjetoInteligente> (
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

    casaTeste.adicionarObjeto(std::move(objetoTeste));

    CHECK(casaTeste.getQuantidadeObjetos() == 1);

    casaTeste.removerObjeto("ObjetoTeste");

    CHECK(casaTeste.getQuantidadeObjetos() == 0);

    SUBCASE("TESTE 9.1 remocao de objeto nao existente na smarthome nao funciona"){
       auto objetoTeste = std::make_unique<ObjetoInteligente> (
        "ObjetoTeste",
        false,
        sensores,
        statusPossiveis,
        "Ligado",
        consumoMedio,
        funcoes,
        funcoesRestritas
    );

        CHECK_THROWS_WITH(casaTeste.removerObjeto("ObjetoTeste2"), "Objeto ObjetoTeste2 nao encontrado na smarthome Minha Casa para remocao");
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");


    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;
    std::string nome;

    Modo modoTeste("ModoTeste", objetos, comodos, true, false);

    casaTeste.adicionarModo(modoTeste);

    CHECK(casaTeste.getQuantidadeModos() == 1);

    casaTeste.removerModo("ModoTeste");

    CHECK(casaTeste.getQuantidadeModos() == 0);

    SUBCASE("TESTE 10.1 remocao de modo nao existente na smarthome nao funciona"){
       Modo modoTeste2("ModoTeste2", objetos, comodos, true, false);

        CHECK_THROWS_WITH(casaTeste.removerModo("ModoTeste2"), "Modo ModoTeste2 nao encontrado na smarthome Minha Casa para remocao");
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

    Smarthome casaTeste(&contaTeste, "Minha Casa");

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

TEST_CASE("Buscar modo pelo nome") {

    Conta usuario("1", "Maria", "maria@gmail.com", "12345678");
    Smarthome casa(&usuario, "Casa");

    Modo modo1("Cinema", {}, {}, false, false);
    Modo modo2("Noturno", {}, {}, false, false);

    casa.adicionarModo(modo1);
    casa.adicionarModo(modo2);

    CHECK(casa.getModo("Cinema") != nullptr);
    CHECK(casa.getModo("Noturno") != nullptr);
    CHECK(casa.getModo("Trabalho") == nullptr);
}