#include "Comodo.hpp"
#include <algorithm>

Comodo::Comodo(std::string nome, Smarthome* casa) : nome(nome), casa(casa) {
    // Não lança exceção se casa == nullptr, apenas aceita
}

void Comodo::adicionarObjeto(const ObjetoInteligente* objeto) {
    if (objeto) {
        if (std::find(objetos.begin(), objetos.end(), objeto) == objetos.end())
            objetos.push_back(const_cast<ObjetoInteligente*>(objeto));
    }
}

void Comodo::adicionarSensor(const Sensor* sensor) {
    if (sensor) {
        if (std::find(sensores.begin(), sensores.end(), sensor) == sensores.end())
            sensores.push_back(const_cast<Sensor*>(sensor));
    }
}

void Comodo::adicionarModo(const Modo* modo) {
    if (modo) {
        if (std::find(modos.begin(), modos.end(), modo) == modos.end())
            modos.push_back(const_cast<Modo*>(modo));
    }
}

const std::vector<ObjetoInteligente*>& Comodo::getObjetos() const {
    return objetos;
}

const std::vector<Sensor*>& Comodo::getSensores() const {
    return sensores;
}

const std::vector<Modo*>& Comodo::getModos() const {
    return modos;
}

void Comodo::removerObjeto(const ObjetoInteligente* objeto) {
    auto it = std::find(objetos.begin(), objetos.end(), objeto);
    if (it != objetos.end()) {
        objetos.erase(it);
    }
}

void Comodo::entrarConta(const Conta* conta) {
    if (conta) {
        contasPresentes.push_back(const_cast<Conta*>(conta));
    }
}

void Comodo::sairConta() {
    if (!contasPresentes.empty()) {
        contasPresentes.pop_back();
    }
}

void Comodo::repassarInstrucao(const Modo* modo) {
    
}

const std::vector<Conta*>& Comodo::getContasPresentes() const {
    return contasPresentes;
}

std::string Comodo::getNome() const {
    return nome;
}

Smarthome* Comodo::getSmarthome() const {
    return casa;
}

Comodo::~Comodo() = default;