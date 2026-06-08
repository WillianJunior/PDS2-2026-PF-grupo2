#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>

class ObjetoInteligente;
class Modo;

class Sensor {
private:

    std::string nome;
    bool estaLigado;
    bool estaAtivado;

    std::vector<ObjetoInteligente*> objetosConectados;
    std::vector<Modo*> modosConectados;

public:

    /**
     * @brief Função construtora do sensor.
     * @param nome Nome do sensor.
     * @param ligado Variável que determina se o sensor está ligado.
     * @param ativado Variável que indica se o sensor está ativado.
     * @param objetosConectados Vetor com todos objetos ligados ao sensor.
     * @param modosConectados Vetor com todos modos ligados ao sensor.
     */
    Sensor(
        std::string nome,
        bool ligado,
        bool ativado,
        std::vector<ObjetoInteligente*> objetosConectados,
        std::vector<Modo*> modosConectados
    );

    /**
     * @brief Retorna o nome do sensor.
     */
    std::string getNome() const;

    /**
     * @brief Liga ou desliga o sensor.
     */
    void setEstaLigado();

    /**
     * @brief Retorna se o sensor está ligado.
     */
    bool getEstaLigado();

    /**
     * @brief Ativa ou desativa o sensor.
     */
    void setEstaAtivado();

    /**
     * @brief Retorna se o sensor está ativado.
     */
    bool getEstaAtivado();

    /**
     * @brief Retorna a lista de objetos conectados.
     */
    std::vector<ObjetoInteligente*> getObjetosConectados();

    /**
     * @brief Retorna a lista de modos conectados.
     */
    std::vector<Modo*> getModosConectados();

    /**
     * @brief Confere elementos do ambiente.
     */
    void checarAmbiente();

    /**
     * @brief Ativa um modo.
     */
    void ativarModo(Modo* modo);

    /**
     * @brief Ativa um objeto.
     */
    void ativarObjeto(ObjetoInteligente* objeto);

    /**
     * @brief Define comparação entre sensores.
     * @param other é sensor a ser comparado.
     * @return Retorna true se sensores são iguais.
     */
    bool operator== (const Sensor& other)const;

    /**
     * @brief Imprime informações do membro do sensor.
     * */
    void printMembrosInfo() const;
};

#endif