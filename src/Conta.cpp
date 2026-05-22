#include "Conta.hpp"
#include "Smarthome.hpp"
#include "Comodo.hpp"

Conta::Conta(std::string id, std::string nome, std::string email, std::string senha, bool adulto)
    : id(id), nome(nome), email(email), senha(senha), perfilAdulto(adulto) {}

std::string Conta::getId() const {
    return id;
}

std::string Conta::getNome() const {
    return nome;
}

std::string Conta::getEmail() const {
    return email;
}

bool Conta::isPerfilAdulto() const {
    return perfilAdulto;
}

void Conta::criarSmarthome(std::string id, std::string nome) {
    (void)id;
    (void)nome;
}

void Conta::apagarSmarthome(Smarthome* smarthome) {
    (void)smarthome;
}

void Conta::criarComodo(Smarthome* smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::apagarComodo(Smarthome* smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::criarModo(Smarthome* smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::apagarModo(Smarthome* smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::editarModo(Smarthome* smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
}

void Conta::criarObjeto(Smarthome* smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::apagarObjeto(Smarthome* smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::moverObjeto(Smarthome* smarthome, Comodo atual, std::string nome, Comodo destino) {
    (void)smarthome;
    (void)atual;
    (void)nome;
    (void)destino;
}

void Conta::criarSensor(Smarthome* smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::apagarSensor(Smarthome* smarthome, Comodo comodo, std::string nome) {
    (void)smarthome;
    (void)comodo;
    (void)nome;
}

void Conta::moverSensor(Smarthome* smarthome, Comodo atual, std::string nome, Comodo destino) {
    (void)smarthome;
    (void)atual;
    (void)nome;
    (void)destino;
}

float Conta::gerarRelatorioDeEnergia(Smarthome* smarthome) {
    (void)smarthome;
    return 0.0f;
}

bool Conta::validarFormatoEmail() const {
    return email.find('@') != std::string::npos;
}

bool Conta::validarSenha() const {
    return senha.length() >= 8;
}

bool Conta::autenticar(const std::string& tentativaSenha) const {
    return senha == tentativaSenha;
}