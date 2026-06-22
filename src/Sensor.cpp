#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include "Comodo.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

Sensor::Sensor(
    std::string nome,
    bool ligado,
    bool ativado,
    Comodo* comodoPertencente,
    std::vector<ObjetoInteligente*> objetosConectados,
    std::vector<Modo*> modosConectados
)
:
    nome(nome),
    estaLigado(ligado),
    estaAtivado(ativado),
    comodoPertencente(comodoPertencente),
    objetosConectados(objetosConectados),
    modosConectados(modosConectados)

{
    if(nome.empty()){
            throw std::invalid_argument("Nome do Sensor nao pode ser vazio - Tente novamente...");
        } 
    else if (nome.size() > 20) {
            throw std::invalid_argument("Nome do Sensor nao pode ter tamanho maior que 20 - Tente novamente...");
    }
    else if(!CaracteresValidos(nome)) {
            throw std::invalid_argument("Nome do Sensor com usos de caracteres invalidos - Tente novamente...");
    }
    else{
        this->nome = nome;
        this->objetosConectados = objetosConectados;
        this->modosConectados = modosConectados;
    }
}

void Sensor::setEstaLigado(bool ligado) {
    estaLigado = ligado;
}

std::string Sensor::getNome() const {
    return nome;
}

bool Sensor::getEstaLigado() const{
    return estaLigado;
}

void Sensor::setEstaAtivado(bool ativado) {
    estaAtivado = ativado;
}

bool Sensor::getEstaAtivado() const {
    return estaAtivado;
}

std::vector<ObjetoInteligente*> Sensor::getObjetosConectados() const {
    return objetosConectados;
}

std::vector<Modo*> Sensor::getModosConectados() const {
    return modosConectados;
}

bool Sensor::checarAmbiente(std::string condicao) {
    if (condicao.empty()) {
        throw std::invalid_argument("Condicao vazia passada para checarAmbiente no Sensor " + nome);
    }
    std::vector<std::string> condicoes = (*comodoPertencente).getCondicoesDoComodo();
    return std::find(
        condicoes.begin(),
        condicoes.end(),
        condicao
    ) != condicoes.end(); //retorna 1 se a condicao foi encontrada no ambiente
}

void Sensor::ativarModo(Modo* modo) {
    if (modo == nullptr) {
        throw std::invalid_argument("Tentativa de ativar modo nulo pelo Sensor " + nome);
    }
    modo->setAtivoModo(1);
}

void Sensor::ativarObjeto(ObjetoInteligente* objeto, size_t indexFuncao) {
    if (objeto == nullptr) {
        throw std::invalid_argument("Tentativa de ativar objeto nulo pelo Sensor " + nome);
    }
    auto funcoes = objeto->getFuncoes();
    if (indexFuncao >= funcoes.size()) {
        throw std::out_of_range("Index de funcao invalido para objeto " + objeto->getNome());
    }
    funcoes[indexFuncao](); // igual a objeto->getFuncoes()[indexFuncao]();
}

bool Sensor :: operator== (const Sensor& other) const{
    return nome == other.nome &&
        estaLigado == other.estaLigado &&
        estaAtivado == other.estaAtivado &&
        comodoPertencente == other.comodoPertencente &&
        objetosConectados == other.objetosConectados &&
        modosConectados == other.modosConectados;
}

void Sensor :: printSensorInfo() const{
    std::cout << "Sensor " << this->nome << " do cômodo " << (*comodoPertencente).getNome() << std::endl;
    std::cout << "Sensor está ligado? " << this->getEstaLigado() << std::endl;
    std::cout << "Sensor está ativado? " << this->getEstaAtivado() << std::endl;
    std::cout << "Objetos conectados: "; 
    for (auto* obj : objetosConectados) {
        std::cout << obj->getNome();
    }
    std::cout<<std::endl;
    std::cout << "Modos conectados: "; 
    for (auto* modo : modosConectados) {
        std::cout << modo->getNome();
    }
    std::cout<<std::endl;
}

bool Sensor :: CaracteresValidos (const std::string& str) {
    for (unsigned char ch : str) {
        // só aceita letras, números e espaços
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}