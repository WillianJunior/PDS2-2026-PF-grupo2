#include "Conta.hpp"
#include "Smarthome.hpp"
#include "Comodo.hpp"
#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Sensor.hpp"
#include <iostream>
#include <vector>

Conta::Conta(std::string id, std::string nome, std::string email, std::string senha, bool adulto)
    : id(id), nome(nome), email(email), senha(senha), perfilAdulto(adulto), bloqueada(false) {}

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

bool Conta::estaBloqueada() const {
    return bloqueada;
}

void Conta::bloquear() {
    bloqueada = true;
}

void Conta::desbloquear() {
    bloqueada = false;
}

void Conta::criarSmarthome(std::string id, std::string nome) {
    (void)id;
    Smarthome* nova_smarthome = new Smarthome(*this, nome);
    smarthomes.push_back(nova_smarthome);
}

void Conta::apagarSmarthome(Smarthome* smarthome) {
    for (auto it = smarthomes.begin(); it != smarthomes.end(); ++it) {
        if (*it == smarthome) {
            delete *it;
            smarthomes.erase(it);
            break;
        }
    }
}

void Conta::criarComodo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        Comodo novoComodo(nome, smarthome);
        smarthome->adicionarComodo(novoComodo);
    }
}

void Conta::apagarComodo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        Comodo comodoRemover(nome, smarthome);
        smarthome->removerComodo(comodoRemover);
    }
}


void Conta::criarModo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        std::vector<ObjetoInteligente*> objetosVazios;
        std::vector<Comodo*> comodosVazios;
        Modo novoModo(nome, objetosVazios, comodosVazios, false, false);
        smarthome->adicionarModo(novoModo);
    }
}

void Conta::apagarModo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        smarthome->removerModo(nome); 
    }
}

void Conta::editarModo(Smarthome* smarthome, std::string nome) {
    (void)smarthome;
    (void)nome;
    // ver como e se será implementado em Smarthome
}

void Conta::criarObjeto(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        std::vector<Sensor*> sensoresVazios;
        std::vector<std::string> statusPossiveis = {"Desligado", "Ligado"};
        std::vector<std::function<void()>> funcoes;
        std::vector<std::function<void()>> funcoesRestritas;

        ObjetoInteligente* novoObjeto = new ObjetoInteligente(
            nome, false, sensoresVazios, statusPossiveis, "Desligado", 0.0f, funcoes, funcoesRestritas
        );

        smarthome->adicionarObjeto(*novoObjeto);
        comodo->adicionarObjeto(novoObjeto);
    }
}

void Conta::apagarObjeto(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        smarthome->removerObjeto(nome); 
        comodo->removerObjetoPorNome(nome); 
    }
}

void Conta::moverObjeto(Smarthome* smarthome, Comodo* atual, std::string nome, Comodo* destino) {
    if (smarthome != nullptr && atual != nullptr && destino != nullptr) {
        atual->removerObjetoPorNome(nome);
        std::cout << "Objeto " << nome << " removido do comodo atual." << std::endl;
    }
}

void Conta::criarSensor(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        std::vector<ObjetoInteligente*> objetosVazios;
        std::vector<Modo*> modosVazios;

        Sensor* novoSensor = new Sensor(nome, false, false, *comodo, objetosVazios, modosVazios);
        comodo->adicionarSensor(novoSensor);
    }
}

void Conta::apagarSensor(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        comodo->removerSensorPorNome(nome); 
    }
}

void Conta::moverSensor(Smarthome* smarthome, Comodo* atual, std::string nome, Comodo* destino) {
    if (smarthome != nullptr && atual != nullptr && destino != nullptr) {
        atual->removerSensorPorNome(nome);
        std::cout << "Sensor " << nome << " removido do comodo atual." << std::endl;
    }
}

float Conta::gerarRelatorioDeEnergia(Smarthome* smarthome) {
    float total = 0.0f;
    if (smarthome != nullptr) {
        std::vector<ObjetoInteligente> objetosDaCasa = smarthome->getObjetos();
        for (size_t i = 0; i < objetosDaCasa.size(); ++i) {
            total += objetosDaCasa[i].getConsumoMedioDeEnergia();
        }
    }
    return total;
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

bool Conta :: operator == (const Conta& other) const{
    return id == other.id && nome == other.nome &&
    email == other.email && senha == other.senha && perfilAdulto == other.perfilAdulto;
}

void Conta::printMembrosInfo() const {
    std::cout << "ID: " << id << "\nNome: " << nome << "\nE-mail: " << email 
              << "\nPerfil: " << (perfilAdulto ? "Adulto" : "Infantil") << std::endl;
}

std::vector<Smarthome*> Conta::getSmarthomes() const {
    return smarthomes;
}