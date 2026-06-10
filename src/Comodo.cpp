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

std::vector<std::string> Comodo::getCondicoesDoComodo() const{
    return condicoesDoComodo;
}

void Comodo::mudarCondicao(std::string condicao) {
    // remove qualquer condição do mesmo grupo (exemplo : se estiver Iluminado, Escuro é removido)
    if (condicao == "Iluminado" || condicao == "Escuro") {
        condicoesDoComodo.erase(
            std::remove_if(condicoesDoComodo.begin(), condicoesDoComodo.end(),
                [](const std::string& c){ return c=="Iluminado" || c=="Escuro"; }),
            condicoesDoComodo.end()
        );
    }
    if (condicao == "Quente" || condicao == "Frio") {
        condicoesDoComodo.erase(
            std::remove_if(condicoesDoComodo.begin(), condicoesDoComodo.end(),
                [](const std::string& c){ return c=="Quente" || c=="Frio"; }),
            condicoesDoComodo.end()
        );
    }
    if (condicao == "Barulhento" || condicao == "Silencioso"){
        condicoesDoComodo.erase(
            std::remove_if(condicoesDoComodo.begin(), condicoesDoComodo.end(),
                [](const std::string& c){ return c=="Barulhento" || c=="Silencioso"; }),
            condicoesDoComodo.end()
        );
    }
    if (condicao == "Umido" || condicao == "Seco"){
        condicoesDoComodo.erase(
            std::remove_if(condicoesDoComodo.begin(), condicoesDoComodo.end(),
                [](const std::string& c){ return c=="Umido" || c=="Seco"; }),
            condicoesDoComodo.end()
        );
    }


    condicoesDoComodo.push_back(condicao);
}


void Comodo::adicionarCondicao(std::string condicao) {
    mudarCondicao(condicao);
}

void Comodo::adicionarObjeto(ObjetoInteligente* objeto) {
    if (objeto) {
        for (const auto& o : objetos) {
            if (*o == *objeto || o->getNome() == objeto->getNome()) { 
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
            if (*s == *sensor || s->getNome() == sensor->getNome()) { 
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
            if (*m == *modo || m->getNome() == modo->getNome()) { 
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

void Comodo::repassarInstrucao( Modo* modo) {
     
    if (contasPresentes.empty()) return;

    auto relacionados = modo->getObjetosRelacionados();

    for (auto* objeto : objetos) {
        if (std::find(relacionados.begin(), relacionados.end(), objeto) != relacionados.end()) {
            if (modo->getAtivoModo()) {
                modo->executarInstrucao(objeto, this); // passa o comodo junto
            } else {
                modo->desfazerInstrucao(objeto, this); // lógica de desativação
            }
        }
    }
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
        objetos[i]->printObjetosInfo();
        std::cout << endl;
    }
}
void Comodo :: printSensoresInfo() const{ 
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Sensores presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<sensores.size(); i++){
        sensores[i]->printSensorInfo();
        std::cout << endl;
    }
}

void Comodo :: printModosInfo() const{
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Modos presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<modos.size(); i++){
        modos[i]->printMembrosInfo(); 
        std::cout << endl;
    }
}

void Comodo :: printContasInfo() const{
    std::cout << "Comodo "<< nome << " da smarthome: " << casa << endl;
    std::cout<< "Contas presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<contasPresentes.size(); i++){
        contasPresentes[i]->printMembrosInfo(); 
        std::cout << endl;
    }
}

void Comodo::removerObjetoPorNome(std::string nomeObjeto) {
    for (auto it = objetos.begin(); it != objetos.end(); ++it) {
        if ((*it)->getNome() == nomeObjeto) {
            objetos.erase(it);
            std::cout << "Objeto " << nomeObjeto << " removido do Comodo " << nome << std::endl;
            return;
        }
    }
    std::cout << "Objeto " << nomeObjeto << " nao encontrado no Comodo " << nome << std::endl;
}

void Comodo::removerSensorPorNome(std::string nomeSensor) {
    for (auto it = sensores.begin(); it != sensores.end(); ++it) {
        if ((*it)->getNome() == nomeSensor) {
            sensores.erase(it);
            std::cout << "Sensor " << nomeSensor << " removido do Comodo " << nome << std::endl;
            return;
        }
    }
    std::cout << "Sensor " << nomeSensor << " nao encontrado no Comodo " << nome << std::endl;
}

void Comodo::removerModoPorNome(std::string nomeModo){
    for (auto it = modos.begin(); it != modos.end(); ++it) {
        if ((*it)->getNome() == nomeModo) {
            modos.erase(it);
            std::cout << "Modo " << nomeModo << " removido do Comodo " << nome << std::endl;
            return;
        }
    }
    std::cout << "Modo " << nomeModo << " nao encontrado no Comodo " << nome << std::endl;
}

Comodo::~Comodo() = default;