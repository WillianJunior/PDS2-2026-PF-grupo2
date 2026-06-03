#include "Smarthome.hpp"
#include <iostream>
using namespace std;
Smarthome::Smarthome(Conta usuario, std::string nome)
    : usuario(usuario), nome(nome) {} // adicionar asserções para instanciamentos invalidos ex: nome vazio

void Smarthome::adicionarModo(const Modo& modo) {
    for (const auto& m : modos) {
        if (m == modo) {
            std :: cout << "Modo ja existente na SmartHome" << endl;
            return;
        }
    }
    modos.push_back(modo);
}

void Smarthome::adicionarComodo(const Comodo& comodo) {
    for (const auto& c: comodos) {
        if (c == comodo) {
            std :: cout << "Comodo ja existente na SmartHome" << endl;
            return;
        }
    }
    comodos.push_back(comodo);
}

void Smarthome::adicionarObjeto(const ObjetoInteligente& objeto) {
    for (const auto& obj: objetos) {
        if (obj == objeto) {
            std :: cout << "Objeto ja existente na SmartHome" << endl;
            return;
        }
    }
    objetos.push_back(objeto);
}
void Smarthome :: removerComodo(const Comodo& comodo){
    auto it = std::find(comodos.begin(), comodos.end(), comodo);
    if (it != comodos.end()) {
        comodos.erase(it);
    }
}

Conta Smarthome::getUsuario() const {
    return usuario;
}

std::string Smarthome::getNome() const {
    return nome;
}

size_t Smarthome::getQuantidadeModos() const {
    return modos.size();
}

size_t Smarthome::getQuantidadeComodos() const {
    return comodos.size();
}

size_t Smarthome::getQuantidadeObjetos() const {
    return objetos.size();
}

void Smarthome:: printComodosInfo()const{
    std::cout << "Smarthome " << nome << " de: " << usuario.getNome() << endl;
    std::cout<< "Comodos presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<comodos.size(); i++){
        comodos[i].printObjetosInfo(); 
        comodos[i].printModosInfo();
        comodos[i].printSensoresInfo();
        comodos[i].printContasInfo();
        std::cout << endl;
    }
}

void Smarthome:: printObjetosInfo() const{
    std::cout << "Smarthome " << nome << " de: " << usuario.getNome() << endl;
    std::cout << "Objetos Inteligentes presentes em " << nome << " :" << endl;
    for(size_t i=0; i<objetos.size(); i++){
        objetos[i].printMembrosInfo(); // falta add metodos prints certos
        std::cout<< endl;
    } 
}

void Smarthome:: printModosInfo() const{
    std::cout << "Smarthome " << nome << " de: " << usuario.getNome() << endl;
    std::cout << "Modos presentes em " << nome << " :" << endl;
    for(size_t i=0; i<modos.size(); i++){
         modos[i].printMembrosInfo(); // falta add metodos prints certos
        std::cout<< endl;
    }
}
Smarthome::~Smarthome() = default;
