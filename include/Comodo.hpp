#ifndef COMODO_HPP
#define COMODO_HPP
#pragma once

#include <string>
#include <vector>
#include <memory>

class Smarthome;
class Conta;
class Sensor;
class ObjetoInteligente;
class Modo;

class Comodo {
public:
    Comodo(std::string nome, Smarthome* casa);

    bool operator==(const Comodo& other) const;

    std::vector<std::string> getCondicoesDoComodo() const;

    void mudarCondicao(std::string condicao);
    void adicionarCondicao(std::string condicao);

    void adicionarObjeto(ObjetoInteligente* objeto);
    void adicionarSensor(std::unique_ptr<Sensor> sensor);
    void adicionarModo(Modo* modo);

    const std::vector<ObjetoInteligente*>& getObjetos() const;
    const std::vector<std::unique_ptr<Sensor>>& getSensores() const;
    const std::vector<Modo*>& getModos() const;

    void removerModoPorNome(std::string nomeModo);
    void removerObjetoPorNome(std::string nomeObjeto);
    void removerSensorPorNome(std::string nomeSensor);

    void entrarConta(Conta* conta);
    void sairConta();

    void repassarInstrucao(Modo* modo);

    const std::vector<Conta*>& getContasPresentes() const;

    std::string getNome() const;
    Smarthome* getSmarthome() const;

    void printObjetosInfo() const;
    void printSensoresInfo() const;
    void printContasInfo() const;
    void printModosInfo() const;

    bool CaracteresValidos (const std::string& str);

    ~Comodo();

private:
    std::string nome;
    Smarthome* casa;

    std::vector<std::string> condicoesDoComodo = {
        "Iluminado", "Escuro", "Quente", "Frio",
        "Umido", "Seco", "Barulhento", "Silencioso"
    };

    std::vector<Conta*> contasPresentes;
    std::vector<ObjetoInteligente*> objetos;
    std::vector<std::unique_ptr<Sensor>> sensores;
    std::vector<Modo*> modos;
};


#endif 