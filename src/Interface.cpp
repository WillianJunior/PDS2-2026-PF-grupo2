#include "Interface.hpp"

Interface::Interface() : sistemaLogin(std::vector<Conta>()), usuarioLogado(nullptr) {}

// Métodos declarados no .hpp, mas ainda sem implementação
void Interface::iniciar() {}
void Interface::exibirMenuInicial() {}
void Interface::exibirMenuConta() {}
void Interface::realizarLogin() {}
void Interface::cadastrarConta() {}