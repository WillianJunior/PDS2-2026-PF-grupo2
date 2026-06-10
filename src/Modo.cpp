#include "Modo.hpp"
#include <stdexcept>
#include <iostream>

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
      bloqueado(bloqueado) {

    if (nome.empty()) {
        throw std::invalid_argument("Nome do modo nao pode ser vazio");
    }

    if (bloqueado) {
        this->ligado = false;
    }
}

std::string Modo::getNome() const {
    return nome;
}

void Modo::setAtivoModo(bool ativo) {
    if (bloqueado && ativo) {
        ligado = false;
        return;
    }

    ligado = ativo;
   // for (auto* comodo : comodosRelacionados) {
   //     comodo->repassarInstrucao(this);
    //}
}

bool Modo::getAtivoModo() const {
    return ligado;
}

void Modo::setBloqueadoModo(bool estado) {
    bloqueado = estado;

    if (bloqueado) {
        ligado = false;
    }
}

bool Modo::getBloqueadoModo()const {
    return bloqueado;
}

std::vector<ObjetoInteligente*> Modo::getObjetosRelacionados() const{
    return objetosRelacionados;
}

std::vector<Comodo*> Modo::getComodosRelacionados() const{
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
    std::cout << "Nome do modo: " << nome << std::endl;
    std::cout << "Estado: " << (ligado ? "Ligado" : "Desligado") << std::endl;
    std::cout << "Bloqueio: " << (bloqueado ? "Bloqueado" : "Desbloqueado") << std::endl;
    std::cout << "Objetos relacionados: " << objetosRelacionados.size() << std::endl;
    std::cout << "Comodos relacionados: " << comodosRelacionados.size() << std::endl;
}

void Modo::executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) {
    
}
void Modo ::  desfazerInstrucao (ObjetoInteligente* objeto, Comodo* comodo){

}