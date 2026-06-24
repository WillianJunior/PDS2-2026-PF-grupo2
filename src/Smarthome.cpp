#include "Smarthome.hpp"
#include <iostream>
#include <stdexcept>
#include <cctype>
using namespace std;
Smarthome::Smarthome(Conta* usuario, std::string nome)
    : usuario(usuario) {
        if(nome.empty()){
            throw std::invalid_argument("Nome da SmartHome nao pode ser vazio");
        } 
        else if (nome.size() > 20) {
            throw std::invalid_argument("Nome da SmartHome nao pode ter tamanho maior que 20");
        }
        else if(!CaracteresValidos(nome)) {
            throw std::invalid_argument("Nome da SmartHome com usos de caracteres invalidos");
        }
        else{
            this -> nome = nome;
        }
    } // adicionar validação de entrada para instanciamentos invalidos ex: nome vazio

bool Smarthome::operator==(const Smarthome& other) const {
    return usuario == other.usuario
        && comodos == other.comodos
        && modos == other.modos
        && objetos == other.objetos
        && nome == other.nome;
}
    
void Smarthome::adicionarModo(const Modo& modo) {
    for (const auto& m : modos) {
        if (m == modo) {
            std :: cout << "Modo ja existente na SmartHome" << endl;
            return;
        }
    }
    modos.push_back(modo);
}

void Smarthome::adicionarComodo(std::unique_ptr<Comodo> comodo) {
    for (const auto& c: comodos) {
        if (*c == *comodo) {
            std :: cout << "Comodo ja existente na SmartHome" << endl;
            return;
        }
    }
    comodos.push_back(move(comodo));
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
     auto it = std::find_if(comodos.begin(), comodos.end(),
        [&](const std::unique_ptr<Comodo>& c) {
            return *c == comodo; // compara objeto apontado com referência
        });
    if (it != comodos.end()) {
        comodos.erase(it);
    }
    else{
        throw std::invalid_argument("Comodo " + comodo.getNome() + " nao encontrado na smarthome " + nome + " para remocao");
    }
}
void Smarthome :: removerComodoPorNome(const std::string& nomeComodo){
     for (auto it = comodos.begin(); it != comodos.end(); ++it) {
        if ((*it)->getNome() == nomeComodo) {
            comodos.erase(it);
            return;
        }
    }
    throw std::runtime_error(
        "Comodo " + nomeComodo +
        " nao encontrado na smarthome " + nome + " para remocao"
    );
}

void Smarthome::removerModo(std::string nomeModo) {
    for (auto it = modos.begin(); it != modos.end(); ++it) {
        if (it->getNome() == nomeModo) {
            modos.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Modo " + nomeModo + " nao encontrado na smarthome " + nome + " para remocao");

}

void Smarthome::removerObjeto(std::string nomeObjeto) {
    for (auto it = objetos.begin(); it != objetos.end(); ++it) {
        if (it->getNome() == nomeObjeto) {
            objetos.erase(it);
            return;
        }
    }
    throw std::invalid_argument("Objeto " + nomeObjeto + " nao encontrado na smarthome " + nome + " para remocao");
}

const std::vector<ObjetoInteligente>& Smarthome::getObjetos() const {
    return objetos;
}

Conta* Smarthome::getUsuario() const {
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
    std::cout << "Smarthome " << nome << " de: " << (*usuario).getNome() << endl;
    std::cout<< "Comodos presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<comodos.size(); i++){
        std::cout << comodos[i]->getNome();
        std::cout << endl;
        auto condicoes = comodos[i]->getCondicoesDoComodo();
        for (const auto& c : condicoes) {
            std::cout << c << " ";
        }
        std::cout << std::endl;
        comodos[i]->printObjetosInfo();
        comodos[i]->printModosInfo();
        comodos[i]->printSensoresInfo();
        comodos[i]->printContasInfo();
        std::cout << endl;
    }
}

void Smarthome:: printObjetosInfo() const{
    std::cout << "Smarthome " << nome << " de: " << (*usuario).getNome() << endl;
    std::cout << "Objetos Inteligentes presentes em " << nome << " :" << endl;
    for(size_t i=0; i<objetos.size(); i++){
        objetos[i].printObjetosInfo(); 
               std::cout<< endl;
    } 
}

void Smarthome:: printModosInfo() const{
    std::cout << "Smarthome " << nome << " de: " << (*usuario).getNome() << endl;
    std::cout << "Modos presentes em " << nome << " :" << endl;
    for(size_t i=0; i<modos.size(); i++){
         modos[i].printMembrosInfo();
        std::cout<< endl;
    }
}

bool Smarthome :: CaracteresValidos (const std::string& str) {
    for (unsigned char ch : str) {
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}
Comodo* Smarthome::getComodo(std::string nomeComodo) {
    for (auto& c : comodos) {
        if (c->getNome() == nomeComodo) {
            return c.get();
        }
    }
    return nullptr;
}
Modo* Smarthome::getModo(std::string nomeModo) {
    for (auto& m : modos) {
        if (m.getNome() == nomeModo) {
            return &m;
        }
    }
    return nullptr;
}

const std::vector<std::unique_ptr<Comodo>>& Smarthome::getComodos() const {
    return comodos;
}

const std::vector<Modo>& Smarthome::getListaModos() const {
    return modos;
}

Smarthome::~Smarthome() = default;
