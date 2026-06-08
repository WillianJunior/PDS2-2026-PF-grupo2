#include "ObjetoInteligente.hpp"
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


std::vector<Sensor*> ObjetoInteligente::getSensores() {
    return sensores;
}


std::vector<std::string> ObjetoInteligente::getStatusPossiveis() {
    if (!statusPossiveis.empty()) {
        return statusPossiveis;
    }
    return {};
}

std::string ObjetoInteligente::getStatusAtual() {
    return statusAtual;
}

void ObjetoInteligente::setStatusAtual(std::string status) {

    statusAtual = status; 
}


float ObjetoInteligente::getConsumoMedioDeEnergia() {
    return consumoMedioDeEnergia;
}


std::vector<std::function<void()>> ObjetoInteligente::getFuncoes() {
    return funcoes;
}


std::vector<std::function<void()>> ObjetoInteligente::getFuncoesRestritas() {
    return funcoesRestritas;
}

void ObjetoInteligente :: printMembrosInfo() const{
    //implemetação
}