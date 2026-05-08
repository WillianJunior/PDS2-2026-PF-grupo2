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
    /**
     * @brief Retorna o status atual do objeto.
     */
    std::string getStatus();
    /**
     * @brief Define o status atual do objeto.
     * @param status é o nome dos status a ser definido.
     */
    void setStatusAtual(std::string status);
    /**
     * @brief Retorna o valor de consumo médio de energia do objeto.
     */
    float getConsumoMedioDeEnergia();
    /**
     * @brief Retorna a lista de funções do objeto.
     * */
    std::vector<std::function<void()>> getFuncoes();
    /**
     * @brief Retorna a lista de funções restritas a crianças do objeto.
     * */
    std::vector<std::function<void()>> getFuncoesRestritas();

};

#endif