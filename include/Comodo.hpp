#include <string>
#include <vector>
#include "Conta.hpp"
#include "SmartHome.hpp"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp”
#include "Modo.hpp"
#ifndef COMODO_HPP
#define COMODO_HPP

class Comodo {
public:

    Comodo(std::string nome, SmartHome* casa);

    void adicionarObjeto(ObjetoInteligente* objeto);
    void adicionarSensor(Sensor* sensor); 
    void adicionarModo(Modo* modo);

    void entrarConta(Conta* conta);
    void sairConta();

    void repassarInstrucao(Modo* modo);

    Conta * getContaPresente();

    std :: string getNome();

    ~Comodo();
                
private:
    std::string nome;
    SmartHome* casa;                // pertence a uma SmartHome
    Conta* contaPresente;           // conta presente em certos momentos
    std::vector<ObjetoInteligente*> objetos;
    std::vector<Sensor*> sensores;
    std::vector<Modo*> modos;
};
#endif

