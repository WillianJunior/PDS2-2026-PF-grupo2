#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include "Comodo.hpp"
#include <vector>
#include <iostream>
#include <algorithm>

Sensor::Sensor(
    std::string nome,
    bool ligado,
    bool ativado,
    Comodo comodoPertencente,
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
    this->nome = nome;
    this->estaLigado = ligado;
    this->estaAtivado = ativado;
    this->objetosConectados = objetosConectados;
    this->modosConectados = modosConectados;
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
    std::vector<std::string> condicoes = comodoPertencente.getCondicoesDoComodo();
    return std::find(
        condicoes.begin(),
        condicoes.end(),
        condicao
    ) != condicoes.end(); //retorna 1 se a condicao foi encontrada no ambiente
}

void Sensor::ativarModo(Modo* modo) {
    modo->setAtivoModo(1);
}

void Sensor::ativarObjeto(ObjetoInteligente* objeto, int indexFuncao) {
    objeto->getFuncoes()[indexFuncao]();
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
    std::cout << "Sensor " << this->nome << " do cômodo " << this->comodoPertencente.getNome() << std::endl;
    std::cout << "Sensor está ligado? " << this->getEstaLigado() << std::endl;
    std::cout << "Sensor está ativado? " << this->getEstaAtivado() << std::endl;
    std::cout << "Objetos conectados: "; 
    for (int i=0; i>objetosConectados.size(); i++) {
        std::cout << objetosConectados.at(i)->getNome();
    }
    std::cout << "Modos conectados: "; 
    for (int i=0; i>modosConectados.size(); i++) {
        std::cout << modosConectados.at(i)->getNome();
    }
}