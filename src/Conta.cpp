#include "Conta.hpp"

Conta::Conta(std::string id, std::string nome, std::string email, std::string senha, bool adulto) {
    (void)id;
    (void)nome;
    (void)email;
    (void)senha;
    (void)adulto;
}

std::string Conta::getId() const {
    return "";
}

std::string Conta::getNome() const {
    return "";
}

std::string Conta::getEmail() const {
    return "";
}

bool Conta::isPerfilAdulto() const {
    return false;
}

void Conta::criarSmarthome(std::string id, std::string nome) {
    (void)id;
    (void)nome;
}

void Conta::apagarSmarthome(Smarthome smarthome) {
    (void)smarthome;
}

void Conta::criarCômodo(Smarthome smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::apagarCômodo(Smarthome smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::criarModo(Smarthome smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::apagarModo(Smarthome smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::editarModo(Smarthome smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::criarObjeto(Smarthome smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::apagarObjeto(Smarthome smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::moverObjeto(Smarthome smarthome, Comodo atual, std::string nome, Comodo destino) {
    (void)smarthome;
    (void)atual;
    (void)nome;
    (void)destino;
}

void Conta::criarSensor(Smarthome smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::apagarSensor(Smarthome smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::moverSensor(Smarthome smarthome, Comodo atual, std::string nome, Comodo destino) {
    (void)smarthome;
    (void)atual;
    (void)nome;
    (void)destino;
}

float Conta::gerarRelatórioDeEnergia(Smarthome smarthome) {
    (void)smarthome;
    return 0.0f;
}

bool Conta::validarFormatoEmail() const {
    return false;
}

bool Conta::validarSenha() const {
    return false;
}

bool Conta::autenticar(const std::string& tentativaSenha) const {
    (void)tentativaSenha;
    return false;
}