#ifndef OBJETOINTELIGENTE_H
#define OBJETOINTELIGENTE_H
#include <vector>
#include <string>
#include <functional>

//TODO: adicionar tipos de objetos (lampada, ar condicionado, tv, etc.)

class Sensor;

/**
 * @class ObjetoInteligente
 * @brief Representa um objeto inteligente da smarthome
 * 
 * A classe armazena sensores, funções disponíveis, restrições de acesso e informações de consumo de energia.
 */

class ObjetoInteligente {
private:
    std::string nome;
    bool restricaoAdulto; 
    std::vector<Sensor*> sensores;
    std::vector<std::string> statusPossiveis;
    std::string statusAtual;
    float consumoMedioDeEnergia;
    std::vector<std::function<void()>> funcoes;
    std::vector<std::function<void()>> funcoesRestritas;

public:

    /**
     * @brief Construtor da classe ObjetoInteligente.
     * @param nome Nome do objeto.
     * @param restricaoAdulto Define se o objeto possui restrição para adultos.
     * @param sensores Vetor dos sensores associados ao objeto.
     * @param statusPossiveis Vetor com os estados possíveis do objeto.
     * @param statusAtual Status atual do objeto.
     * @param consumoMedioDeEnergia Consumo médio de energia do objeto.
     * @param funcoes Vetor das funções disponíveis.
     * @param funcoesRestritas Vetor das funções restritas.
     */

    ObjetoInteligente(
        std::string nome,
        bool restricaoAdulto,
        std::vector<Sensor*> sensores,
        std::vector<std::string> statusPossiveis,
        std::string statusAtual,
        float consumoMedioDeEnergia,
        std::vector<std::function<void()>> funcoes,
        std::vector<std::function<void()>> funcoesRestritas
    );

    ~ObjetoInteligente() = default;

    /// Métodos setters e getters
    /**
     * @brief Define se o objeto é restrito para adultos apenas.
     * @param restricao define se a restrição está ligada (1) ou não (0).
     */
    void setRestricaoAdulto(bool restricao);
    /**
     * @brief Retorna os sensores associados ao objeto.
     */
    std::vector<Sensor*> getSensores();
    /**
     * @brief Retorna os status possíveis do objeto.
     */
    std::vector<std::string> getStatusPossiveis();
    /**
     * @brief Retorna o status atual do objeto.
     */
    std::string getStatusAtual();
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
    /**
     * @brief Define comparação entre objetos.
     * */
    bool operator==(const ObjetoInteligente& other) const;
    /**
     * @brief Imprime informações do membro do objeto.
     * */
    void printMembrosInfo() const;
};

#endif