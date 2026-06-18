#include "Modo.hpp"
#include <stdexcept>
#include <iostream>
#include "ObjetoInteligente.hpp"
#include <cctype>
#include <stdexcept>

Modo::Modo(
    std::string nome,
    std::vector<ObjetoInteligente*> objetos,
    std::vector<Comodo*> comodos,
    bool ligado,
    bool bloqueado
)
    :
      objetosRelacionados(objetos),
      comodosRelacionados(comodos),
      ligado(ligado),
      bloqueado(bloqueado) {

    if (nome.empty()) {
        throw std::invalid_argument("Nome do Modo nao pode ser vazio - Tente novamente...");
    }
    else if (nome.size() > 20) {
        throw std::invalid_argument("Nome do Modo nao pode ter tamanho maior que 20  - Tente novamente..." );
    }
    else if(!CaracteresValidos(nome)) {
        throw std::invalid_argument("Nome do Modo com usos de caracteres invalidos  - Tente novamente..." );
    }
    else{
            this->nome=nome;
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
      (void)comodo;

    if (objeto == nullptr){
        throw std::invalid_argument("Modo nao pode executar instrucao em Objeto nullptr");
    } if (bloqueado) {
        std::cout<< "Modo" << nome << "bloqueado" << std::endl;
        return;
    }

    objeto->setStatusAtual("Ligado");
}
void Modo :: desfazerInstrucao (ObjetoInteligente* objeto, Comodo* comodo){
     (void)comodo;

    if (objeto == nullptr){
        throw std::invalid_argument("Modo nao pode desfazer instrucao em Objeto nullptr");
    } if (bloqueado) {
        std::cout<< "Modo" << nome << "bloqueado" << std::endl;
        return;
    }

    objeto->setStatusAtual("Desligado");
}
    bool Modo :: CaracteresValidos (const std::string& str) {
    for (unsigned char ch : str) {
        // só aceita letras, números e espaços
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}



ModoNoturno::ModoNoturno(std::string nome)
    : Modo(
        nome,
        {},
        {},
        false,
        false
    ) {}

void ModoNoturno::executarInstrucao() {
    for (ObjetoInteligente* item : this->getObjetosRelacionados()) {
        item->setStatusAtual(0);
    }
}