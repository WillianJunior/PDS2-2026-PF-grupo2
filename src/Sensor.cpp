#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"

Sensor::Sensor(
    bool ligado,
    bool ativado,
    std::vector<ObjetoInteligente*> objetosConectados,
    std::vector<Modo*> modosConectados
)
{
    this->estaLigado = ligado;
    this->estaAtivado = ativado;
    this->objetosConectados = objetosConectados;
    this->modosConectados = modosConectados;
}

void Sensor::setEstaLigado() {
}

bool Sensor::getEstaLigado() {
    return estaLigado;
}

void Sensor::setEstaAtivado() {
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

void Sensor::checarAmbiente() {
}

void Sensor::ativarModo(Modo* modo) {
    (void)modo;
}

void Sensor::ativarObjeto(ObjetoInteligente* objeto) {
    (void)objeto;
}

bool Sensor :: operator== (const Sensor& other) const{
    return estaLigado == other.estaLigado && estaAtivado == other.estaAtivado && objetosConectados == other.objetosConectados &&
    modosConectados == other.modosConectados;
}

void Sensor :: printMembrosInfo() const{
    //implemetação
}