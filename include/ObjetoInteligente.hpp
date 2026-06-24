#ifndef OBJETOINTELIGENTE_H
#define OBJETOINTELIGENTE_H

#include <vector>
#include <string>
#include <functional>

class Sensor;

/**
 * @brief Classe para definir como o objeto está operando.
 */
enum class Protocolo {
    WIFI,
    BLUETOOTH,
    ZIGBEE
};


class ObjetoInteligente {
protected:
    /**
     * @brief Armazena o nome do objeto.
     */
    std::string nome;

    /**
     * @brief Indica se o objeto é restrito apenas para adultos.
     */
    bool restricaoAdulto; 

    /**
     * @brief Vetor que armazena os sensores do objeto.
     */
    std::vector<Sensor*> sensores;

    /**
     * @brief Vetor que armazena os status possíveis do objeto.
     */
    std::vector<std::string> statusPossiveis;

    /**
     * @brief Indica o status atual do objeto.
     */
    std::string statusAtual;

    /**
     * @brief Armazena o consumo médio de energia do objeto.
     */
    float consumoMedioDeEnergia;

    /**
     * @brief Vetor que armazena as funções que podem ser realizadas pelo objeto.
     */
    std::vector<std::function<void()>> funcoes;

    /**
     * @brief Armazena o nome do objeto.
     */
    std::vector<std::function<void()>> funcoesRestritas;

    /**
     * @brief Protocolo definido como WIFI.
     */
    Protocolo protocolo = Protocolo::WIFI;

    /**
     * @brief Inidica se o objeto está apresentando alguma falha.
     */
    bool emFalha = false;

public:
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

   virtual  ~ObjetoInteligente() = default;

    std::string getNome() const;

    std::vector<Sensor*> getSensores() const;
    std::vector<std::string> getStatusPossiveis() const;

    std::string getStatusAtual() const;
    virtual void setStatusAtual(std::string status);

    float getConsumoMedioDeEnergia() const;

    std::vector<std::function<void()>> getFuncoes() const;
    std::vector<std::function<void()>> getFuncoesRestritas() const;

    Protocolo getProtocolo() const;
    void setProtocolo(Protocolo protocolo);
    bool comunicaCom(const ObjetoInteligente& outro) const;
    std::string getProtocoloComoString() const;

    void simularFalha();
    void repararFalha();
    bool estaEmFalha() const;

    bool operator==(const ObjetoInteligente& other) const;
    void printObjetosInfo() const;

    bool CaracteresValidos(const std::string& str);

    void setRestricaoAdulto(bool restricao);
    bool getRestricaoAdulto() const;
};

class Luz : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    Luz(std::string nome);
    void setStatusAtual(int indexStatus);
};

class CaixaDeSom : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    CaixaDeSom(std::string nome);
    void setStatusAtual(int indexStatus);
};

class TV : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    TV(std::string nome);
    void ligar();
    void desligar();
};

class ArCondicionado : public ObjetoInteligente {
private:
    float temperatura;

public:
    using ObjetoInteligente::setStatusAtual;
    ArCondicionado(std::string nome);
    void resfriar();
    void aquecer();
    void desligar();
    void setTemperatura(float temperatura);
    float getTemperatura() const;
};

class Portao : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    Portao(std::string nome);
    void abrir();
    void fechar();
};

class Termostato : public ObjetoInteligente {
private:
    float temperaturaAtual;

public:
    using ObjetoInteligente::setStatusAtual;
    Termostato(std::string nome);
    void setTemperaturaAtual(float temperatura);
    float getTemperaturaAtual() const;
    void normalizar();
    void aquecer();
    void resfriar();
};
#endif
