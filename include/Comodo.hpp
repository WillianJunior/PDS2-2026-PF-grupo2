#ifndef COMODO_HPP
#define COMODO_HPP
#pragma once
#include <string>
#include <vector>

class Smarthome;
class Conta;
class Sensor;
class ObjetoInteligente;
class Modo;


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
    Comodo(std::string nome, Smarthome* casa);
    /**
     * @brief Define comparação entre comodos.
     * @param other é comodo a ser comparado.
     * @return Retorna true se comodos forem iguais.
     */
    bool operator == (const Comodo& other)const;
    /**
     * @brief Adiciona um objeto a um comodo.
     * @param objeto ObjetoInteligente a ser adicionado ao comodo.
     */
    void adicionarObjeto(ObjetoInteligente* objeto);
    /**
     * @brief Adiciona um sensor a um comodo.
     * @param sensor Sensor a ser adicionado ao comodo.
     */
    void adicionarSensor(Sensor* sensor); 
    /**
     * @brief Adiciona um modo a um comodo.
     * @param modo Modo a ser adicionado ao comodo.
     */
    void adicionarModo(Modo* modo);
    /**
     * @brief Retorna objetos no comodo.
     */
    const std :: vector <ObjetoInteligente*>& getObjetos() const;
    /**
     * @brief Retorna sensores no comodo.
     */
    const std :: vector <Sensor*>& getSensores() const;
    /**
     * @brief Retorna modos no comodo.
     */
    const std :: vector <Modo*>& getModos() const;
    /**
     * @brief Remove objeto do comodo.
     * @param objeto ObjetoInteligente a ser removido do comodo.
     */
    void removerObjeto(const ObjetoInteligente* objeto);

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
    void repassarInstrucao(const Modo* modo);
    /**
     * @brief Retorna Contas dentro do cômodo.
     */
    const std :: vector <Conta*>&  getContasPresentes() const;
    /**
     * @brief Retorna o nome do cômodo.
     */
    std :: string getNome() const;
    /**
     * @brief Retorna Smarthome a qual o cômodo pertence.
     */
    Smarthome* getSmarthome() const;
    /**
     * @brief Imprime informações dos objetos do Comodo.
     */
    void printObjetosInfo()const;
    /**
     * @brief Imprime informações dos sensores do Comodo.
     */
    void printSensoresInfo()const;
    /**
     * @brief Imprime informações dos contas do Comodo.
     */
    void printContasInfo()const;
    /**
     * @brief Imprime informações dos modos do Comodo.
     */
    void printModosInfo()const;

    ~Comodo();
                
private:
    /**
     * @brief Nome do cômodo.
     */
    std::string nome;
    /**
     * @brief Smarthome que o cômodo pertence.
     */
    Smarthome* casa;                
    std::vector<Conta*> contasPresentes;           // contas presentes em certos momentos
    std::vector<ObjetoInteligente*> objetos;
    std::vector<Sensor*> sensores;
    std::vector<Modo*> modos;
};
#endif

