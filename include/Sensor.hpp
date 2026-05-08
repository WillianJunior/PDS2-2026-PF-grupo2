#ifndef SENSOR_H
#define SENSOR_H
#include "ObjetoInteligente.hpp"
#include "Modo.hpp"
#include <vector>

class Sensor {
private:

    bool estaLigado;
    bool estaAtivado;
    std::vector<ObjetoInteligente> objetosConectados;
    std::vector<Modo> modosConectados;

public: 
    /**
     * @brief Função construtora do sensor.
     * @param ligado Variável que determina se o sensor está ligado (se pode ser ativado).
     * @param ativado Variável que indica se o sensor está ativado.
     * @param objetosConectados Vetor com todos objetos ligados ao sensor.
     * @param modosConectados Vetor com todos modos ligados ao sensor.
     */
    Sensor(
        bool ligado,
        bool ativado,
        std::vector<ObjetoInteligente> objetosConectados,
        std::vector<Modo> modosConectados
    );

    /**
     * @brief Liga ou desliga o sensor.
     */
    void setEstaLigado();

    /**
     * @brief Retorna se o sensor está ligado ou não (se está pronto para ser ativado).
     */
    bool getEstaLigado();

    /**
     * @brief Ativa ou desativa o sensor.
     */
    void setEstaAtivado();
    
    /**
     * @brief Ativa ou desativa o sensor.
     */
    bool getEstaAtivado();

    /**
     * @brief Retorna a lista de objetos conectados.
     */
    ObjetoInteligente getObjetosConectados();

    /**
     * @brief Retorna a lista de modos conectados.
     */
    Modo getModosConectados();

    /**
     * @brief Confere elementos do ambiente, podendo assim ativar.
     */
    void checarAmbiente();

    /**
     * @brief Ativa um modo.
     */
    void ativarModo(Modo modo);

    /**
     * @brief Ativa um objeto.
     */
    void ativarObjeto(ObjetoInteligente objeto);

};

#endif