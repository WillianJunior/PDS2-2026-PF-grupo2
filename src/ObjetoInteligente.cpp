#include "ObjetoInteligente.hpp"
#include <iostream>
#include <algorithm>
#include "Sensor.hpp"
#include <cctype>
#include <stdexcept>

ObjetoInteligente::ObjetoInteligente(
    std::string nome,
    bool restricaoAdulto,
    std::vector<Sensor*> sensores,
    std::vector<std::string> statusPossiveis,
    std::string statusAtual,
    float consumoMedioDeEnergia,
    std::vector<std::function<void()>> funcoes,
    std::vector<std::function<void()>> funcoesRestritas
) :
    restricaoAdulto(restricaoAdulto),
    sensores(std::move(sensores)),
    statusPossiveis(std::move(statusPossiveis)),
    statusAtual(statusAtual),
    consumoMedioDeEnergia(consumoMedioDeEnergia),
    funcoes(std::move(funcoes)),
    funcoesRestritas(std::move(funcoesRestritas))
{
    if(nome.empty()){
            throw std::invalid_argument("Nome do Obejeto nao pode ser vazio - Tente novamente...");
        } 
    else if (nome.size() > 20) {
            throw std::invalid_argument("Nome do Objeto nao pode ter tamanho maior que 20 - Tente novamente...");
    }
    else if(!CaracteresValidos(nome)) {
            throw std::invalid_argument("Nome do Objeto com usos de caracteres invalidos - Tente novamente...");
    }
    else{
    this->nome = nome;
    }
}
std::string ObjetoInteligente::getNome() const {
    return nome;
}

bool ObjetoInteligente :: operator==(const ObjetoInteligente& other) const {
        return nome == other.nome &&
            restricaoAdulto == other.restricaoAdulto &&
            sensores == other.sensores &&
            statusPossiveis == other.statusPossiveis &&
            statusAtual == other.statusAtual &&
            consumoMedioDeEnergia == other.consumoMedioDeEnergia &&
            funcoes.size() == other.funcoes.size() &&
            funcoesRestritas.size() == other.funcoesRestritas.size();
    } // funcoes nao podem ser comparadas diretamente entao usa o .size() 

void ObjetoInteligente::setRestricaoAdulto(bool restricao) {
    restricaoAdulto = restricao;
}


std::vector<Sensor*> ObjetoInteligente::getSensores() const {
    return sensores;
}


std::vector<std::string> ObjetoInteligente::getStatusPossiveis() const{
    if (!statusPossiveis.empty()) {
        return statusPossiveis;
    }
    return {};
}

std::string ObjetoInteligente::getStatusAtual() const {
    return statusAtual;
}

void ObjetoInteligente::setStatusAtual(std::string status) {
    if (std::find(statusPossiveis.begin(), statusPossiveis.end(), status) == statusPossiveis.end()) {
        throw std::invalid_argument("Status invalido para este objeto");
    }
    statusAtual = status; 
}


float ObjetoInteligente::getConsumoMedioDeEnergia() const {
    return consumoMedioDeEnergia;
}


std::vector<std::function<void()>> ObjetoInteligente::getFuncoes() const{
    return funcoes;
}


std::vector<std::function<void()>> ObjetoInteligente::getFuncoesRestritas() const{
    return funcoesRestritas;
}

void ObjetoInteligente :: printObjetosInfo() const{
    std::cout << "Objeto " << this->nome;
    std::cout << "Objeto tem restrição parental?" << this->restricaoAdulto << std::endl;
    std::cout << "Consumo médio de energia: " << this->consumoMedioDeEnergia << std::endl;
    std::cout << "Sensores conectados: "; 
    for (int i=0; i < sensores.size(); i++) {
        std::cout << sensores.at(i)->getNome();
    }
   
    std::cout << "Status possíveis: "; 
for (size_t i = 0; i < statusPossiveis.size(); i++) {
    std::cout << this->getStatusPossiveis().at(i);
}
    std::cout << "Status atual: " << this->statusAtual << std::endl;
}

// LUZ

Luz::Luz(std::string nome)
    : ObjetoInteligente(
        nome,
        false,
        {},
        {"acesa", "apagada"},
        "apagada",
        10.0f,
        {},
        {}
    ) {}

void Luz::setStatusAtual(int indexStatus) {
    if (indexStatus = 0) {
        this->statusAtual = "apagada";
    } else {
        this->statusAtual = "acesa";
    }
}

// CAIXA DE SOM

CaixaDeSom::CaixaDeSom(std::string nome)
    : ObjetoInteligente(
        nome,
        false,
        {},
        {"desligada", "standby", "tocando música"},
        "desligada",
        0.0f,
        {},
        {}
    ) {}

void CaixaDeSom::setStatusAtual(int indexStatus) {
    if (indexStatus == 0) {
        this->statusAtual = "desligado";
    } else if (indexStatus == 1) {
        this->statusAtual = "standby";
    } else {
        this->statusAtual = "tocando música";
    }
}
bool ObjetoInteligente :: CaracteresValidos (const std::string& str) {
    for (unsigned char ch : str) {
        // só aceita letras, números e espaços
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}
