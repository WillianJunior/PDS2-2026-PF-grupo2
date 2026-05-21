#include <vector>
#include <string>
#include "Comodo.hpp"
#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#ifndef SMARTHOME_HPP
#define SMARTHOME_HPP

class SmartHome{
private:

    std::string usuario;
    std::vector<Comodo> comodos;
    std::vector<Modo> modos;
    std::vector<ObjetoInteligente> objetos;

public:
    SmartHome(std :: string usuario);
    void adcionarModo(Modo& modo);
    void adicionarComodo(Comodo& comodo);
    void adicionarObjeto(Objeto& objeto);

    std :: string get_Usuario();


    ~SmartHome();
};
#endif
