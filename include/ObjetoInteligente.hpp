#ifndef OBJETOINTELIGENTE_H
#define OBJETOINTELIGENTE_H
#include <vector>
#include <string>
#include <functional>
#include "Sensor.hpp"

/**
 * @class ObjetoInteligente
 * @brief Representa um objeto inteligente da smarthome
 * 
 * A classe armazena sensores, funções disponíveis, restrições de acesso e informações de consumo de energia.
 */

class ObjetoInteligente {
private:
    bool restricaoAdulto; 
    std::vector<Sensor> sensores;
    std::vector<std::string> statusPossiveis;
    float consumoMedioDeEnergia;
    std::vector<std::function<void()>> funcoes;
    std::vector<std::function<void()>> funcoesRestritas;

public:

    /**
     * @brief Construtor da classe ObjetoInteligente.
     * 
     * @param restricaoAdulto Define se o objeto possui restrição para adultos.
     * @param sensores Vetor dos sensores associados ao objeto.
     * @param statusPossiveis Vetor com os estados possíveis do objeto.
     * @param consumoMedioDeEnergia Consumo médio de energia do objeto.
     * @param funcoes Vetor das funções disponíveis.
     * @param funcoesRestritas Vetor das funções restritas.
     */

    ObjetoInteligente(
        bool restricaoAdulto,
        std::vector<Sensor> sensores,
        std::vector<std::string> statusPossiveis,
        float consumoMedioDeEnergia,
        std::vector<std::function<void()>> funcoes,
        std::vector<std::function<void()>> funcoesRestritas
    );

    ~ObjetoInteligente() = default;

    /// Métodos setters e getters
    void setRestricaoAdulto();
    /**
     * @brief Retorna os sensores associados ao objeto.
     */
    std::vector<Sensor> getSensores();
    std::string getStatus();
    void setStatusAtual(std::string status);
    float getConsumoMedioDeEnergia();
    std::vector<std::function<void()>> getFuncoes();
    std::vector<std::function<void()>> getFuncoesRestritas();

};

#endif