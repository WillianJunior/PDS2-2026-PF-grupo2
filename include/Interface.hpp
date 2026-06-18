#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Login.hpp"
#include "Conta.hpp"
#include <iostream>
#include <vector>
#include <memory>

class Interface {
private:
    Login sistemaLogin;
    std::unique_ptr<Conta> usuarioLogado;

    void exibirMenuInicial();     // Tela de Login / Cadastro
    void exibirMenuConta();       // Tela após logar - Gerenciar Smarthomes
    void exibirMenuSmarthome();   // Tela de listagem e seleção de Smarthomes
    void gerenciarSmarthome(Smarthome* casa); // Tela de controle da Smarthome escolhida
    void exibirMenuComodos(Smarthome* casa);  // Tela de gestao de comodos da casa
    void gerenciarComodoEspecifico(Smarthome* casa, Comodo* comodo); // Tela de controle de um comodo especifico
    void exibirMenuModos(Smarthome* casa); // Tela de gestao de modos da casa

    void realizarLogin();
    void cadastrarConta();

public:
    Interface();
    void iniciar();
};

#endif