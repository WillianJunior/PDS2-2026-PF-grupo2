#include "Comodo.hpp"
#include <algorithm>
#include "Conta.hpp"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <cctype>
using namespace std;
Comodo::Comodo(const std::string& nome, Smarthome* casa) {

    if(nome.empty()){
            throw std::invalid_argument("Nome do Comodo nao pode ser vazio - Tente novamente...");
        } 
    else if (nome.size() > 20) {
            throw std::invalid_argument("Nome do Comodo nao pode ter tamanho maior que 20 - Tente novamente...");
    }
    else if(!CaracteresValidos(nome)) {
            throw std::invalid_argument("Nome do Comodo com usos de caracteres invalidos - Tente novamente...");
    }
    else if (casa == nullptr){
        throw std :: invalid_argument("Ponteiro para smarthome do comodo eh nullptr - Tente novamente...");
    }
    else{
    this->casa = casa;   
    this->nome = nome;
    }
    
}

bool Comodo :: operator== (const Comodo& other) const{
    return nome == other.nome && casa == other.casa;
}

std::vector<std::string> Comodo::getCondicoesDoComodo() const{
    return condicoesDoComodo;
}

void Comodo::mudarCondicao(const std::string& condicao) {
    // remove qualquer condição do mesmo grupo (exemplo : se estiver Iluminado, Escuro é removido)
    if(condicao != "Iluminado" && condicao != "Escuro" && condicao != "Quente" && condicao != "Frio" &&
     condicao != "Barulhento" && condicao != "Silencioso" && condicao != "Umido" && condicao != "Seco" ){

        throw std::invalid_argument("Condicao invalida: " + condicao);
    }
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


void Comodo::adicionarCondicao(const std::string& condicao) {
    mudarCondicao(condicao); // inconsitente com mudar condicao que baseia-se na ideia que tem numero limitado de condicoes
}

void Comodo::adicionarObjeto(ObjetoInteligente* objeto) {
    if( objeto == nullptr){
        throw std::invalid_argument("Tentativa de adicionar objeto nulo ao Comodo " + nome);
    }
    else {
        for (const auto& o : objetos) {
            if (*o == *objeto || o->getNome() == objeto->getNome()) { 
                throw std::invalid_argument("Objeto " + objeto->getNome() + " ja existe no Comodo " + nome);
            }
            
        }
        objetos.push_back(objeto);
    }
}

void Comodo::adicionarSensor(std::unique_ptr<Sensor> sensor) {
    if (!sensor) {
        throw std::invalid_argument(
            "Tentativa de adicionar sensor nulo ao Comodo " + nome
        );
    }

    for (const auto& s : sensores) {
        if (*s == *sensor || s->getNome() == sensor->getNome()) {
            throw std::invalid_argument(
                "Sensor " + sensor->getNome() +
                " ja existe no Comodo " + nome
            );
        }
    }

    sensores.push_back(std::move(sensor));
}

void Comodo::adicionarModo(Modo* modo) {
    if (modo == nullptr){
        throw std::invalid_argument("Tentativa de adicionar modo nulo ao Comodo " + nome);
    }
    else{
        for (const auto& m : modos) {
            if (*m == *modo || m->getNome() == modo->getNome()) { 
                throw std::invalid_argument("Modo " + modo->getNome() + " ja existe no Comodo " + nome);
            }
            
        }
        modos.push_back(modo);
    }
}

const std::vector<ObjetoInteligente*>& Comodo::getObjetos() const {
    return objetos;
}

const std::vector<unique_ptr<Sensor>>& Comodo::getSensores() const {
    return sensores;
}

const std::vector<Modo*>& Comodo::getModos() const {
    return modos;
}

void Comodo::entrarConta(Conta* conta) {
    if(conta == nullptr){
        throw std :: invalid_argument("Tentativa de adicionar conta nula ao Comodo " + nome);
    }
    else {
        for (const auto& c : contasPresentes) {
            if (*c == *conta) { 
                throw std::invalid_argument("Conta " + conta->getNome() + " ja existe no Comodo " + nome);
            }
        }
        contasPresentes.push_back(conta);
    }
}

void Comodo::sairConta() {
    if (!contasPresentes.empty()) {
        contasPresentes.erase(contasPresentes.begin());// comportamento de fila FIFO
    }
    else{
        throw std::runtime_error("Nenhuma conta presente no Comodo " + nome + " para sair");
    }
}

void Comodo::repassarInstrucao( Modo* modo) {
     
    if (contasPresentes.empty()) {
        std::cout << "Aviso: Nenhuma conta presente no Comodo " << nome 
                  << " - instrução do modo não foi repassada." << std::endl;
        return;
    }

    if(modo == nullptr){
        throw std::invalid_argument("Modo invalido (nullptr) ao repassar instrucao no Comodo " + nome);
    } 
    else {
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
    std::cout << "Comodo "<< nome << " :" << endl;
    std::cout<< "Objetos inteligentes presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<objetos.size(); i++){
        objetos[i]->printObjetosInfo();
        std::cout << endl;
    }
}
void Comodo :: printSensoresInfo() const{ 
    std::cout << "Comodo "<< nome << " :" << endl;
    std::cout<< "Sensores presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<sensores.size(); i++){
        sensores[i]->printSensorInfo();
        std::cout << endl;
    }
}

void Comodo :: printModosInfo() const{
    std::cout << "Comodo "<< nome << " :" << endl;
    std::cout<< "Modos presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<modos.size(); i++){
        modos[i]->printMembrosInfo(); 
        std::cout << endl;
    }
}

void Comodo :: printContasInfo() const{
    std::cout << "Comodo "<< nome << " :" << endl;
    std::cout<< "Contas presentes em "<< nome << " :" << endl;
    for(size_t i=0; i<contasPresentes.size(); i++){
        contasPresentes[i]->printMembrosInfo(); 
        std::cout << endl;
    }
}

void Comodo::removerObjetoPorNome(const std::string& nomeObjeto) {
    for (auto it = objetos.begin(); it != objetos.end(); ++it) {
        if ((*it)->getNome() == nomeObjeto) {
            objetos.erase(it);
            std::cout << "Objeto " << nomeObjeto << " removido do Comodo " << nome << std::endl;
            return;
        }
    }
    throw std::runtime_error("Objeto " + nomeObjeto + " nao encontrado no Comodo " + nome);
}

void Comodo::removerSensorPorNome(const std::string& nomeSensor) {
    for (auto it = sensores.begin(); it != sensores.end(); ++it) {
        if ((*it)->getNome() == nomeSensor) {
            sensores.erase(it);
            std::cout << "Sensor " << nomeSensor << " removido do Comodo " << nome << std::endl;
            return;
        }
    }
    throw std::runtime_error("Sensor " + nomeSensor + " nao encontrado no Comodo " + nome);
}

void Comodo::removerModoPorNome(const std::string& nomeModo){
    for (auto it = modos.begin(); it != modos.end(); ++it) {
        if ((*it)->getNome() == nomeModo) {
            modos.erase(it);
            std::cout << "Modo " << nomeModo << " removido do Comodo " << nome << std::endl;
            return;
        }
    }
    throw std::runtime_error("Modo " + nomeModo + " nao encontrado no Comodo " + nome);

}

bool Comodo::CaracteresValidos(const std::string& str) const {
    for (unsigned char ch : str) {
        // só aceita letras, números e espaços
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}

Comodo::~Comodo() = default;