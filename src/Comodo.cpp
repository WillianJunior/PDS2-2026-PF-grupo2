#include "Comodo.hpp"
#include <algorithm>
#include "Conta.hpp"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include <vector>
#include <iostream>
using namespace std;
Comodo::Comodo(std::string nome, Smarthome* casa) {
    //adicionar asserção para nome vazio e casa nullptr
    this->nome = nome;
    this->casa = casa;
}

bool Comodo :: operator== (const Comodo& other) const{
    return nome == other.nome && casa == other.casa;
}

std::vector<std::string> Comodo::getCondicoesDoComodo() {
    return condicoesDoComodo;
}

void Comodo::adicionarCondicao(std::string condicao) {
    condicoesDoComodo.push_back(condicao);
}

void Comodo::adicionarObjeto(ObjetoInteligente* objeto) {
    if (objeto) {
        for (const auto& o : objetos) {
            if (*o == *objeto) { 
                std::cout << "Objeto já existente no Comodo " << nome << std::endl; // por nome do comodo
                return;
            }
        }
        objetos.push_back(objeto);
    }
}

void Comodo::adicionarSensor(Sensor* sensor) {
    if (sensor) {
        for (const auto& s : sensores) {
            if (*s == *sensor) { 
                std::cout << "Sensor já existente no Comodo " << nome << std::endl;
                return;
            }
        }
        sensores.push_back(sensor);
    }
}

void Comodo::adicionarModo(Modo* modo) {
    if (modo) {
        for (const auto& m : modos) {
            if (*m == *modo) { 
                std::cout << "Modo já existente no Comodo " << nome << std::endl;
                return;
            }
        }
        modos.push_back(modo);
    }
}

const std::vector<ObjetoInteligente*>& Comodo::getObjetos() const {
    return objetos;
}

const std::vector<Sensor*>& Comodo::getSensores() const {
    return sensores;
}

const std::vector<Modo*>& Comodo::getModos() const {
    return modos;
}

void Comodo::removerObjeto(const ObjetoInteligente* objeto) {
    auto it = std::find(objetos.begin(), objetos.end(), objeto);
    if (it != objetos.end()) {
        objetos.erase(it);
    }
}

void Comodo::entrarConta(Conta* conta) {
    if (conta) {
        for (const auto& c : contasPresentes) {
            if (*c == *conta) { 
                std::cout << "Conta já existente no Comodo " << nome << std::endl;
                return;
            }
        }
        contasPresentes.push_back(conta);
    }
}

void Comodo::sairConta() {
    if (!contasPresentes.empty()) {
        contasPresentes.erase(contasPresentes.begin());// comportamento de fila FIFO
    }
}

void Comodo::repassarInstrucao(const Modo* modo) {
    
}

const std::vector<Conta*>& Comodo::getContasPresentes() const {
    return contasPresentes;
}

std::string Comodo::getNome() const {
    return nome;
}

Smarthome* Comodo::getSmarthome() const {
    return casa;
}

void Comodo :: printObjetosInfo() const{
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Objetos inteligentes presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<objetos.size(); i++){
        objetos[i]->printMembrosInfo();  // falta add metodos prints certos
        std::cout << endl;
    }
}
void Comodo :: printSensoresInfo() const{ 
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Sensores presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<sensores.size(); i++){
        sensores[i]->printMembrosInfo(); // falta add metodos prints certos 
        std::cout << endl;
    }
}

void Comodo :: printModosInfo() const{
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Modos presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<modos.size(); i++){
        modos[i]->printMembrosInfo();// falta add metodos prints certos  
        std::cout << endl;
    }
}

void Comodo :: printContasInfo() const{
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Contas presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<contasPresentes.size(); i++){
        contasPresentes[i]->printMembrosInfo();// falta add metodos prints certos  
        std::cout << endl;
    }
}
Comodo::~Comodo() = default;