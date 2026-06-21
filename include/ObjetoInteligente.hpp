#ifndef OBJETOINTELIGENTE_H
#define OBJETOINTELIGENTE_H

#include <vector>
#include <string>
#include <functional>

class Sensor;

enum class Protocolo {
    WIFI,
    BLUETOOTH,
    ZIGBEE
};

class ObjetoInteligente {
protected:
    std::string nome;
    bool restricaoAdulto; 
    std::vector<Sensor*> sensores;
    std::vector<std::string> statusPossiveis;
    std::string statusAtual;
    float consumoMedioDeEnergia;
    std::vector<std::function<void()>> funcoes;
    std::vector<std::function<void()>> funcoesRestritas;

    Protocolo protocolo = Protocolo::WIFI;
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

    void setRestricaoAdulto(bool restricao);
    bool getRestricaoAdulto() const;

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
};

class Luz : public ObjetoInteligente {
public:
    Luz(std::string nome);
    void setStatusAtual(int indexStatus);
};

class CaixaDeSom : public ObjetoInteligente {
public:
    CaixaDeSom(std::string nome);
    void setStatusAtual(int indexStatus);
};

class TV : public ObjetoInteligente {
public:
    TV(std::string nome);
    void ligar();
    void desligar();
};

class ArCondicionado : public ObjetoInteligente {
private:
    float temperatura;

public:
    ArCondicionado(std::string nome);
    void resfriar();
    void aquecer();
    void desligar();
    void setTemperatura(float temperatura);
    float getTemperatura() const;
};

class Portao : public ObjetoInteligente {
public:
    Portao(std::string nome);
    void abrir();
    void fechar();
};

class Termostato : public ObjetoInteligente {
private:
    float temperaturaAtual;

public:
    Termostato(std::string nome);
    void setTemperaturaAtual(float temperatura);
    float getTemperaturaAtual() const;
    void normalizar();
    void aquecer();
    void resfriar();
};

#endif