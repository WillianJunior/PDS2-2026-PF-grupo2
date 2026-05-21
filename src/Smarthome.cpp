#include "Smarthome.hpp"

Smarthome::Smarthome(Conta usuario, std::string nome)
    : usuario(usuario), nome(nome) {}

void Smarthome::adicionarModo(const Modo& modo) {
    modos.push_back(modo);
}

void Smarthome::adicionarComodo(const Comodo& comodo) {
    comodos.push_back(comodo);
}

void Smarthome::adicionarObjeto(const ObjetoInteligente& objeto) {
    objetos.push_back(objeto);
}

Conta Smarthome::getNomeUsuario() const {
    return usuario;
}

std::string Smarthome::getNome() const {
    return nome;
}

size_t Smarthome::getQuantidadeModos() const {
    return modos.size();
}

size_t Smarthome::getQuantidadeComodos() const {
    return comodos.size();
}

size_t Smarthome::getQuantidadeObjetos() const {
    return objetos.size();
}

Smarthome::~Smarthome() = default;
