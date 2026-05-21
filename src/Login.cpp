#include "Login.hpp"

Login::Login(std::vector<Conta> contasCadastradas)
    : contas(contasCadastradas) {}

void Login::criarConta(Conta contaNova) {
    contas.push_back(contaNova);
}

bool Login::autenticarConta(std::string email, std::string senha) {

    for (int i = 0; i < contas.size(); i++) {

        if (contas[i].getEmail() == email &&
            contas[i].autenticar(senha)) {

            return true;
        }
    }

    return false;
}

bool Login::bloquearConta(std::string email) {

    for (int i = 0; i < contas.size(); i++) {

        if (contas[i].getEmail() == email) {
            return true;
        }
    }

    return false;
}

std::vector<Conta> Login::getContasCadastradas() {
    return contas;
}