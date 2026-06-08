#include "Modo.hpp"

Modo::Modo(
    std::string nome,
    std::vector<ObjetoInteligente*> objetos,
    std::vector<Comodo*> comodos,
    bool ligado,
    bool bloqueado
)
    : nome(nome),
      objetosRelacionados(objetos),
      comodosRelacionados(comodos),
      ligado(ligado),
      bloqueado(bloqueado) {}

std::string Modo::getNome() const {
    return nome;
}

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

bool Modo::operator==(const Modo& other) const {
    return nome == other.nome &&
           objetosRelacionados == other.objetosRelacionados &&
           comodosRelacionados == other.comodosRelacionados &&
           ligado == other.ligado &&
           bloqueado == other.bloqueado;
}

void Modo::printMembrosInfo() const {
    // ainda vou implementar

}