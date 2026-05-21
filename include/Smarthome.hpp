#ifndef SMARTHOME_HPP
#define SMARTHOME_HPP
#include <vector>
#include <string>
#include "Comodo.hpp"
#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Conta.hpp"


class Smarthome{
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
    Smarthome(Conta usuario, std :: string nome);

    /**
     * @brief Adiciona um modo a uma smarthome.
     * @param modo Modo a ser adicionado à smarthome.
     */
    void adicionarModo(const Modo& modo);
    /**
     * @brief Adiciona um cômodo a uma smarthome.
     * @param comodo Comodo a ser adicionado à smarthome.
     */
    void adicionarComodo(const Comodo& comodo);
    /**
     * @brief Adiciona um objeto a uma smarthome.
     * @param objeto Objeto a ser adicionado à smarthome.
     */
    void adicionarObjeto(const ObjetoInteligente& objeto);

    /**
     * @brief Retorna o usuário dono da smarthome.
     */
    Conta getNomeUsuario()const;
    /**
     * @brief Retorna nome da smarthome.
     */
    std :: string getNome()const;
    /**
     * @brief Retorna a quantidade de Modos da smarthome.
     */
    size_t getQuantidadeModos()const;
    /**
     * @brief Retorna a quantidade de Comodos da smarthome.
     */
    size_t getQuantidadeComodos()const;
    /**
     * @brief Retorna a quantidade de Objetos da smarthome.
     */
    size_t getQuantidadeObjetos()const;


    ~Smarthome();
};
#endif
