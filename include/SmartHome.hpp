#include <vector>
#include <string>
#include "Comodo.hpp"
#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Conta.hpp"
#ifndef SMARTHOME_HPP
#define SMARTHOME_HPP

class SmartHome{
private:

    Conta usuario;
    std::vector<Comodo> comodos;
    std::vector<Modo> modos;
    std::vector<ObjetoInteligente> objetos;
    std::string nome;

public:

    /**
     * @brief Função construtora da smarthome.
     * @param usuario Conta dona da smarthome.
     * @param nome Nome da smarthome.
     */
    SmartHome(Conta usuario, string nome);

    /**
     * @brief Adiciona um modo a uma smarthome.
     * @param modo Modo a ser adicionado à smarthome.
     */
    void adicionarModo(Modo& modo);
    /**
     * @brief Adiciona um cômodo a uma smarthome.
     * @param comodo Comodo a ser adicionado à smarthome.
     */
    void adicionarComodo(Comodo& comodo);
    /**
     * @brief Adiciona um objeto a uma smarthome.
     * @param objeto Objeto a ser adicionado à smarthome.
     */
    void adicionarObjeto(Objeto& objeto);

    /**
     * @brief Retorna o usuário dono da smarthome.
     */
    Conta getUsuario();


    ~SmartHome();
};
#endif
