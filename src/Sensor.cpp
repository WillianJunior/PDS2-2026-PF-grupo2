#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include "Comodo.hpp"
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

bool Sensor::getEstaLigado() {
    return estaLigado;
}

void Sensor::setEstaAtivado(bool ativado) {
    estaAtivado = ativado;
}

bool Sensor::getEstaAtivado() {
    return estaAtivado;
}

std::vector<ObjetoInteligente*> Sensor::getObjetosConectados() {
    return objetosConectados;
}

std::vector<Modo*> Sensor::getModosConectados() {
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
    objeto->getFuncoes()[indexFuncao];
}

bool Sensor :: operator== (const Sensor& other) const{
    return nome == other.nome &&
           estaLigado == other.estaLigado && 
           estaAtivado == other.estaAtivado && 
           objetosConectados == other.objetosConectados &&
           modosConectados == other.modosConectados;
}

void Sensor :: printMembrosInfo() const{
    //implemetação
}