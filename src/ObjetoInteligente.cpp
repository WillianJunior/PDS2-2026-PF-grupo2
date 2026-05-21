#include "ObjetoInteligente.hpp"
#include <algorithm>

ObjetoInteligente::ObjetoInteligente(
    bool restricaoAdulto,
    std::vector<Sensor> sensores,
    std::vector<std::string> statusPossiveis,
    float consumoMedioDeEnergia,
    std::vector<std::function<void()>> funcoes,
    std::vector<std::function<void()>> funcoesRestritas
) :
    restricaoAdulto(restricaoAdulto),
    sensores(std::move(sensores)),
    statusPossiveis(std::move(statusPossiveis)),
    consumoMedioDeEnergia(consumoMedioDeEnergia),
    funcoes(std::move(funcoes)),
    funcoesRestritas(std::move(funcoesRestritas))
{
    
}


void ObjetoInteligente::setRestricaoAdulto() {
    restricaoAdulto = true;
}


std::vector<Sensor> ObjetoInteligente::getSensores() {
    return sensores;
}


std::string ObjetoInteligente::getStatus() {
    if (!statusPossiveis.empty()) {
        return statusPossiveis.back();
    }
    return "";
}


void ObjetoInteligente::setStatusAtual(std::string status) {
    statusPossiveis.push_back(status);
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
