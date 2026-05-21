#include "Sensor.hpp"

Sensor::Sensor(
    bool ligado, 
    bool ativado, 
    std::vector<ObjetoInteligente> objetosConectados, 
    std::vector<Modo> modosConectados
) {
    this->estaLigado = ligado;
    this->estaAtivado = ativado;
    this->objetosConectados = objetosConectados;
    this->modosConectados = modosConectados;
}

void Sensor::setEstaLigado() {
}

bool Sensor::getEstaLigado() {
    return this->estaLigado;
}

void Sensor::setEstaAtivado() {
}

bool Sensor::getEstaAtivado() {
    return this->estaAtivado;
}

ObjetoInteligente Sensor::getObjetosConectados() {
    ObjetoInteligente objVazio; 
    return objVazio;
}

Modo Sensor::getModosConectados() {
    Modo modoVazio;
    return modoVazio;
}

void Sensor::checarAmbiente() {
}

void Sensor::ativarModo(Modo modo) {
}

void Sensor::ativarObjeto(ObjetoInteligente objeto) {
}