#ifndef OBJETOINTELIGENTE_H
#define OBJETOINTELIGENTE_H
#include <vector>
#include <string>
#include <functional>
#include "Sensor.hpp"


class ObjetoInteligente {
private:
    bool restricaoAdulto;
    std::vector<Sensor> sensores;
    std::vector<std::string> statusPossiveis;
    float consumoMedioDeEnergia;
    std::vector<std::function<void()>> funcoes;
    std::vector<std::function<void()>> funcoesRestritas;

public:
    ObjetoInteligente(
        bool restricaoAdulto,
        std::vector<Sensor> sensores,
        std::vector<std::string> statusPossiveis,
        float consumoMedioDeEnergia,
        std::vector<std::function<void()>> funcoes,
        std::vector<std::function<void()>> funcoesRestritas
    );

    virtual ~ObjetoInteligente() = default;

    void setRestricaoAdulto();
    // void mover(Comodo& destino); responsabilidade da conta?
    std::vector<Sensor> getSensores();
    std::string getStatus();
    void setStatusAtual(std::string status);
    float getConsumoMedioDeEnergia();
    std::vector<std::function<void()>> getFuncoes();
    std::vector<std::function<void()>> getFuncoesRestritas();

};

#endif