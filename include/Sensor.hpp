#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include "Comodo.hpp"

//TODO: adicionar tipos de sensores (de luz, temperatura)

class ObjetoInteligente;
class Modo;

class Sensor {
private:

    std::string nome;

    bool estaLigado;
    bool estaAtivado;

    Comodo* comodoPertencente;

    std::vector<ObjetoInteligente*> objetosConectados;
    std::vector<Modo*> modosConectados;

public:

    /**
     * @brief Função construtora do sensor.
     * @param nome Nome do sensor.
     * @param ligado Variável que determina se o sensor está ligado.
     * @param ativado Variável que indica se o sensor está ativado.
     * @param comodoPertencente A qual cômodo pertence o sensor.
     * @param objetosConectados Vetor com todos objetos ligados ao sensor.
     * @param modosConectados Vetor com todos modos ligados ao sensor.
     */
    Sensor(
        std::string nome,
        bool ligado,
        bool ativado,
        Comodo* comodoPertencente,
        std::vector<ObjetoInteligente*> objetosConectados,
        std::vector<Modo*> modosConectados
    );

    /**
     * @brief Retorna o nome do sensor.
     */
    std::string getNome() const;

    /**
     * @brief Liga ou desliga o sensor.
     * @param ligado Valor que determina se o sensor está ligado (1) ou desligado (0).
     */
    void setEstaLigado(bool ligado);

    /**
     * @brief Retorna se o sensor está ligado.
     */
    bool getEstaLigado() const;

    /**
     * @brief Ativa ou desativa o sensor.
     * @param ativado Valor que determina se o sensor está ativado (1) ou desativado (0).
     */
    void setEstaAtivado(bool ativado);

    /**
     * @brief Retorna se o sensor está ativado.
     */
    bool getEstaAtivado() const;

    /**
     * @brief Retorna a lista de objetos conectados.
     */
    std::vector<ObjetoInteligente*> getObjetosConectados() const;

    /**
     * @brief Retorna a lista de modos conectados.
     */
    std::vector<Modo*> getModosConectados() const;

    /**
     * @brief Confere um elemento do ambiente. Se encontrá-lo, retorna 1. Se não, retorna 0.
     * @param condicao Qual condição do ambiente procurar
     */
    bool checarAmbiente(std::string condicao);

    /**
     * @brief Ativa um modo.
     */
    void ativarModo(Modo* modo);

    /**
     * @brief Ativa um objeto.
     * @param indexFuncao Qual função do objeto ativar.
     */
    void ativarObjeto(ObjetoInteligente* objeto, size_t indexFuncao);

    /**
     * @brief Define comparação entre sensores.
     * @param other é sensor a ser comparado.
     * @return Retorna true se sensores são iguais.
     */
    bool operator== (const Sensor& other)const;

    /**
     * @brief Imprime informações do membro do sensor.
     * */
    void printSensorInfo() const;

    /**
     * @brief Checa se os caracteres de str sao algo alem de numeros, letras e espacos, se forem retorna false
     * */
    bool CaracteresValidos (const std::string& str);
};

#endif