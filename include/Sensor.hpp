#ifndef SENSOR_H
#define SENSOR_H
#include "ObjetoInteligente.hpp"
#include "Modos"
#include <vector>

class Sensor {
private:
    bool estaLigado;
    bool estaAtivado;
    std::vector<ObjetoInteligente> objetosConectados;
    std::vector<Modos> modosConectados;

public:
    Sensor();
    void setEstaLigado();
    bool getEstaLigado();
    void setEstaAtivado();
    bool getEstaAtivado();

    ObjetoInteligente getObjetosConectados();


};

#endif