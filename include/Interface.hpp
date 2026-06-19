#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Login.hpp"
#include "Conta.hpp"
#include "Smarthome.hpp"
#include "Comodo.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Interface {
private:
    Login sistemaLogin;
    std::unique_ptr<Conta> usuarioLogado;

    void exibirMenuInicial();
    void exibirMenuConta();
    void exibirMenuSmarthome();
    void gerenciarSmarthome(Smarthome* casa);
    void exibirMenuComodos(Smarthome* casa);
    void gerenciarComodoEspecifico(Smarthome* casa, Comodo* comodo);
    void exibirMenuModos(Smarthome* casa);
    void gerenciarModoEspecifico(Smarthome* casa, std::string nomeModo);
    void criarCasaPadrao(Smarthome* casa);
    void realizarLogin();
    void cadastrarConta();

public:
    Interface();
    void iniciar();
};

#endif