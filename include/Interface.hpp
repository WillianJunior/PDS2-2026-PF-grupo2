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
    void exibirMenuSmarthome();   // Tela de gestão interna da casa

    void realizarLogin();
    void cadastrarConta();

public:
    Interface();
    void iniciar();
};

#endif