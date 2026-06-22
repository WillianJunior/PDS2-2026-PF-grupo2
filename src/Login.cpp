#include "Login.hpp"
#include <cstddef>

Login::Login(std::vector<std::unique_ptr<Conta>>&& contasCadastradas)
    : contas(std::move(contasCadastradas)) {}

void Login::criarConta(std::unique_ptr<Conta> contaNova) {

    for (size_t i = 0; i < contas.size(); i++) {

        if (contas[i]->getEmail() == contaNova->getEmail()) {
            return;
        }
    }

    contas.push_back(move(contaNova));
}

bool Login::autenticarConta(std::string email, std::string senha) {

    for (size_t i = 0; i < contas.size(); i++) {

        if (contas[i]->getEmail() == email) {

            if (contas[i]->estaBloqueada()) {
                return false;
            }

            return contas[i]->autenticar(senha);
        }
    }

    return false;
}

bool Login::bloquearConta(std::string email) {

    for (size_t i = 0; i < contas.size(); i++) {

        if (contas[i]->getEmail() == email) {
            contas[i]->bloquear();
            return true;
        }
    }

    return false;
}

const std::vector<std::unique_ptr<Conta>>& Login::getContasCadastradas() const {
    return contas;
}