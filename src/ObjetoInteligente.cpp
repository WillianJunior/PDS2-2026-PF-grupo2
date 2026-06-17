#include "ObjetoInteligente.hpp"
#include <iostream>
#include <algorithm>
#include "Sensor.hpp"


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
    nome(nome),
    restricaoAdulto(restricaoAdulto),
    sensores(std::move(sensores)),
    statusPossiveis(std::move(statusPossiveis)),
    statusAtual(statusAtual),
    consumoMedioDeEnergia(consumoMedioDeEnergia),
    funcoes(std::move(funcoes)),
    funcoesRestritas(std::move(funcoesRestritas))
{
    
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
    )
{
}