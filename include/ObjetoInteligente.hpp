#ifndef OBJETOINTELIGENTE_H
#define OBJETOINTELIGENTE_H

#include <vector>
#include <string>
#include <functional>

class Sensor;

/**
 * @class ObjetoInteligente
 * @brief Classe para definir como o objeto está operando.
 */
enum class Protocolo {
    WIFI,
    BLUETOOTH,
    ZIGBEE
};


/**
 * @class ObjetoInteligente
 * @brief Representa um objeto inteligente com suas propriedades, funções, sensores, entre outros elementos relacionados.
 */

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
     * @brief Indica se o objeto está apresentando alguma falha.
     */
    bool emFalha = false;

public:

    /**
     * @brief Construtor da classe ObjetoInteligente.
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

    /**
     * @brief Destrutor da classe ObjetoInteligente.
     */
    virtual  ~ObjetoInteligente() = default;

    /**
     * @brief Retorna o nome do objeto.
     */
    std::string getNome() const;

    /**
     * @brief Retorna o vetor com os sensores do objeto.
     */
    std::vector<Sensor*> getSensores() const;

    /**
     * @brief Retorna o vetor com os status possíveis do objeto.
     */
    std::vector<std::string> getStatusPossiveis() const;

    /**
     * @brief Retorna o status atual do objeto.
     */
    std::string getStatusAtual() const;
    
    /**
     * @brief Define o status atual do objeto.
     * @param status Nome do status a ser definido.
     */
    virtual void setStatusAtual(std::string status);

    /**
     * @brief Retorna o consumo médio de energia.
     */
    float getConsumoMedioDeEnergia() const;

    /**
     * @brief Retorna o vetor com as funções do objeto.
     */
    std::vector<std::function<void()>> getFuncoes() const;

    /**
     * @brief Retorna o vetor com as funções restritas do objeto.
     */
    std::vector<std::function<void()>> getFuncoesRestritas() const;

    /**
     * @brief Retorna o protocolo do objeto.
     */
    Protocolo getProtocolo() const;

    /**
     * @brief Define o protocolo do objeto.
     * @param protocolo Qual tipo de protocolo a ser definido.
     */
    void setProtocolo(Protocolo protocolo);

    /**
     * @brief Retorna se o objeto comunica com outro específico.
     */
    bool comunicaCom(const ObjetoInteligente& outro) const;

    /**
     * @brief Retorna o nome do protocolo.
     */
    std::string getProtocoloComoString() const;

    /**
     * @brief Simula uma falha no objeto.
     */
    void simularFalha();

    /**
     * @brief Conserta a falha no objeto.
     */
    void repararFalha();

    /**
     * @brief Retorna se o objeto está com falha.
     */
    bool estaEmFalha() const;

    /**
     * @brief Operador de igualdade da classe.
     */
    bool operator==(const ObjetoInteligente& other) const;

    /**
     * @brief Imprime as informações do objeto.
     */
    void printObjetosInfo() const;

    /**
     * @brief Retorna se os caracteres de uma string estão de acordo com as especificações do sistema.
     * @param str String a ser verificada.
     */
    bool caracteresValidos(const std::string& str);

    /**
     * @brief Define se o objeto tem restrição de adulto.
     */
    void setRestricaoAdulto(bool restricao);

    /**
     * @brief Retorna se o objeto tem restrição de adulto.
     */
    bool getRestricaoAdulto() const;
};

/**
 * @class Luz.
 * @brief Subclasse de objeto, que representa uma luz. 
 */
class Luz : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    Luz(std::string nome);
    void setStatusAtual(int indexStatus);
};

/**
 * @class Caixa.
 * @brief Subclasse de objeto, que representa uma caixa de som. 
 */
class CaixaDeSom : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    CaixaDeSom(std::string nome);
    void setStatusAtual(int indexStatus);
};

/**
 * @class TV.
 * @brief Subclasse de objeto, que representa uma televisão. 
 */
class TV : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;
    TV(std::string nome);
    void ligar();
    void desligar();
};

/**
 * @class ArCondicionado.
 * @brief Subclasse de objeto, que representa um ar condicionado. 
 */
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


/**
 * @class Portao.
 * @brief Subclasse de objeto, que representa um portão. 
 */
class Portao : public ObjetoInteligente {
public:
    using ObjetoInteligente::setStatusAtual;

    /**
     * @brief Construtor da subclasse.
     */
    Portao(std::string nome);

    /**
     * @brief Abre o portão.
     */
    void abrir();

    /**
     * @brief Fecha o paortão.
     */
    void fechar();
};


/**
 * @class Termostato.
 * @brief Subclasse de objeto, que representa um termostato. 
 */
class Termostato : public ObjetoInteligente {
private:

    /**
     * @brief Armazena a temperatura atual.
     */
    float temperaturaAtual;

public:

    using ObjetoInteligente::setStatusAtual;

    /**
     * @brief Construtor da subclasse.
     */
    Termostato(std::string nome);

    /**
     * @brief Define a temperatura atual.
     */
    void setTemperaturaAtual(float temperatura);

    /**
     * @brief Retorna a temperatura atual.
     */
    float getTemperaturaAtual() const;

    /**
     * @brief Define o status como normal.
     */
    void normalizar();

    /**
     * @brief Define o status como aquecendo.
     */
    void aquecer();

    /**
     * @brief Define o status como resfriandp.
     */
    void resfriar();
};
#endif
