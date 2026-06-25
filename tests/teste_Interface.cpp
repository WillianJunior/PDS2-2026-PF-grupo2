#include "doctest.h"
#include "Interface.hpp"
#include <sstream>
#include <iostream>

TEST_CASE("Interface - Login e Logout simulados") {
    
    std::istringstream fakeInput("1\nadmin@smarthome.com\n12345678\n3\n");
    std::cin.rdbuf(fakeInput.rdbuf());

  
    std::ostringstream fakeOutput;
    auto oldCout = std::cout.rdbuf(fakeOutput.rdbuf());

    Interface interface;
    interface.iniciarTeste();

    
    std::cout.rdbuf(oldCout);

    
    CHECK(fakeOutput.str().find("Login realizado com sucesso") != std::string::npos);
    CHECK(fakeOutput.str().find("Logout efetuado com sucesso") != std::string::npos);
}
TEST_CASE("Interface - Cadastro de conta inválida") {
    std::istringstream fakeInput("2\nid1\nNome Teste\nemail_invalido\n123\nA\n");
    std::cin.rdbuf(fakeInput.rdbuf());

    std::ostringstream fakeOutput;
    auto oldCout = std::cout.rdbuf(fakeOutput.rdbuf());

    Interface interface;
    interface.iniciarTeste(); // roda só o menu inicial

    std::cout.rdbuf(oldCout);

    CHECK(fakeOutput.str().find("Formato de e-mail invalido") != std::string::npos);
}
TEST_CASE("Interface - Fluxo até Menu de Modos") {
    
    std::istringstream fakeInput(
        "1\n"                       // Login
        "admin@smarthome.com\n"     // Email
        "12345678\n"                // Senha
        "1\n"                       // Criar Smarthome
        "MinhaCasa\n"               // Nome da casa
        "2\n"                       // Acessar minhas Smarthomes
        "1\n"                       // Escolher a primeira casa
        "2\n"                       // Gerenciar Modos
        "2\n"                       // Criar novo Modo
        "ModoNoturno\n"             // Nome do modo
        "3\n"                       // Tipo do modo: Noturno
        "4\n"                       // Acessar Modo específico
        "ModoNoturno\n"             // Nome do modo
        "2\n"                       // Adicionar cômodo ao modo
        "Quarto\n"                  // Nome do cômodo
        "5\n"                       // Voltar
    );
    std::cin.rdbuf(fakeInput.rdbuf());

    std::ostringstream fakeOutput;
    auto oldCout = std::cout.rdbuf(fakeOutput.rdbuf());

    Interface interface;
    interface.iniciarTeste(); 

    std::cout.rdbuf(oldCout);

    CHECK(fakeOutput.str().find("Smarthome 'MinhaCasa' criada com sucesso") != std::string::npos);
    CHECK(fakeOutput.str().find("Modo 'ModoNoturno' criado com sucesso") != std::string::npos);
   // CHECK(fakeOutput.str().find("Comodo 'Quarto' adicionado ao modo") != std::string::npos);
}
TEST_CASE("Interface - Fluxo até Criar casa padrao"){
     std::istringstream fakeInput(
        "1\n"                       // Login
        "admin@smarthome.com\n"     // Email
        "12345678\n"                // Senha
        "1\n"                       // Criar Smarthome
        "MinhaCasaPadrao\n"         // Nome da casa
        "2\n"                       // Acessar minhas Smarthomes
        "1\n"                       // Escolher a primeira casa
        "3\n"                       // Criar Casa Padrão
        "3\n"                       // 3 quartos
        "2\n"                       // 2 banheiros
        "S\n"                       // possui sala
        "S\n"                       // possui cozinha
        "S\n"                       // possui escritório
        "4\n"                       // Mostrar planta da casa
        "6\n"                       // Voltar
    );
    std::cin.rdbuf(fakeInput.rdbuf());

    std::ostringstream fakeOutput;
    auto oldCout = std::cout.rdbuf(fakeOutput.rdbuf());

    Interface interface;
    interface.iniciarTeste();

    std::cout.rdbuf(oldCout);

    CHECK(fakeOutput.str().find("Smarthome 'MinhaCasaPadrao' criada com sucesso") != std::string::npos);
    CHECK(fakeOutput.str().find("Casa padrao personalizada criada com sucesso") != std::string::npos);
    //CHECK(fakeOutput.str().find("Planta da casa") != std::string::npos);
}