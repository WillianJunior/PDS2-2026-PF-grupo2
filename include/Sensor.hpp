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
    Sensor(
        bool ligado,
        bool ativado,
        std::vector<ObjetoInteligente> objetosConectados,
        std::vector<Modo> modosConectados
    );
    void setEstaLigado();
    bool getEstaLigado();
    void setEstaAtivado();
    bool getEstaAtivado();

    ObjetoInteligente getObjetosConectados();
    Modo getModosConectados();
    void checarAmbiente();
    void ativarModo(Modo modo);
    void ativarObjeto(ObjetoInteligente objeto);

};

#endif