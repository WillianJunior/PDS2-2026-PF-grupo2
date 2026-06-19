#include "Login.hpp"
#include <cstddef>

Login::Login(std::vector<Conta> contasCadastradas)
    : contas(contasCadastradas) {}

void Login::criarConta(Conta contaNova) {

    for (size_t i = 0; i < contas.size(); i++) {

        if (contas[i].getEmail() == contaNova.getEmail()) {
            return;
        }
    }

    contas.push_back(contaNova);
}

bool Login::autenticarConta(std::string email, std::string senha) {

    for (size_t i = 0; i < contas.size(); i++) {

        if (contas[i].getEmail() == email) {

            if (contas[i].estaBloqueada()) {
                return false;
            }

            return contas[i].autenticar(senha);
        }
    }

    return false;
}

bool Login::bloquearConta(std::string email) {

    for (size_t i = 0; i < contas.size(); i++) {

        if (contas[i].getEmail() == email) {
            contas[i].bloquear();
            return true;
        }
    }

    return false;
}

const std::vector<Conta>& Login::getContasCadastradas() const {
    return contas;
}