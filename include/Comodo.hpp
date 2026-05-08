#include <string>
#include <vector>
#include "Conta.hpp"
#include "SmartHome.hpp"
#include "Sensor.hpp"
#include "ObjetoInteligente.hpp”
#include "Modo.hpp"
#ifndef COMODO_HPP
#define COMODO_HPP

/**
 * @class Comodo
 * @brief Representa um cômodo da SmartHome responsável por armazenar objetos inteligentes, sensores, modos e controlar a presença de uma conta no ambiente.
 */
class Comodo {
public:

    /**
     * @brief Construtor da classe Comodo.
     * @param nome Nome do cômodo.
     * @param casa Ponteiro para a SmartHome à qual o cômodo pertence.
     */ 
    Comodo(std::string nome, SmartHome* casa);

    void adicionarObjeto(ObjetoInteligente* objeto);
    void adicionarSensor(Sensor* sensor); 
    void adicionarModo(Modo* modo);

    /**
     * @brief Define uma conta que esta no cômodo.
     * 
     * @param conta Ponteiro para a conta que entrou no cômodo.
     */
    void entrarConta(Conta* conta);
     /**
     * @brief Remove a conta presente do cômodo.
     */
    void sairConta();

    /**
     * @brief Controla a ativação de um modo.
     * 
     * @param modo Ponteiro para o modo que vai receber a instrução.
     */
    void repassarInstrucao(Modo* modo);

    Conta * getContaPresente();
    /**
     * @brief Retorna o nome do cômodo.
     */
    std :: string getNome();

    ~Comodo();
                
private:
    /**
     * @brief Nome do cômodo.
     */
    std::string nome;
    /**
     * @brief SmartHome que o cômodo pertence.
     */
    SmartHome* casa;                
    Conta* contaPresente;           // conta presente em certos momentos
    std::vector<ObjetoInteligente*> objetos;
    std::vector<Sensor*> sensores;
    std::vector<Modo*> modos;
};
#endif

