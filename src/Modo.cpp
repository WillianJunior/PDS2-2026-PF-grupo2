#include "Modo.hpp"

Modo::Modo(
    std::vector<ObjetoInteligente*> objetos,
    std::vector<Comodo*> comodos,
    bool ligado,
    bool bloqueado
)
    : objetosRelacionados(objetos),
      comodosRelacionados(comodos),
      ligado(ligado),
      bloqueado(bloqueado) {}

void Modo::setAtivoModo(bool ativo) {
    ligado = ativo;
}

bool Modo::getAtivoModo() {
    return ligado;
}

void Modo::setBloqueadoModo(bool estado) {
    bloqueado = estado;
}

bool Modo::getBloqueadoModo() {
    return bloqueado;
}

std::vector<ObjetoInteligente*> Modo::getObjetosRelacionados() {
    return objetosRelacionados;
}

std::vector<Comodo*> Modo::getComodosRelacionados() {
    return comodosRelacionados;
}
bool Modo :: operator == (const Modo& other) const{
    return objetosRelacionados == other.objetosRelacionados && comodosRelacionados == other.comodosRelacionados &&
    ligado == other.ligado && bloqueado == other.bloqueado;
}
void Modo :: printMembrosInfo() const{
    //implemetação
}