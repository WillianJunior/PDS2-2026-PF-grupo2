#ifndef SMARTHOME_HPP
#define SMARTHOME_HPP
#include <vector>
#include <string>
#include <algorithm>
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
     * @brief Remove um cômodo de uma smarthome.
     * @param comodo Comodo a ser removido da smarthome.
     */
    void removerComodo(const Comodo& comodo);

    /**
     * @brief Remove um modo da smarthome pelo nome.
     * @param nomeModo Nome do modo a ser removido.
     */
    void removerModo(std::string nomeModo);
    /**
     * @brief Remove um objeto da smarthome pelo nome.
     * @param nomeObjeto Nome do objeto a ser removido.
     */
    void removerObjeto(std::string nomeObjeto);
    /**
     * @brief Retorna os objetos da smarthome.
     */
    const std::vector<ObjetoInteligente>& getObjetos() const;

    /**
     * @brief Retorna o usuário dono da smarthome.
     */
    Conta getUsuario()const;
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
    /**
     * @brief Imprime informações dos comodos de Smarthome.
     */
    void printComodosInfo()const;
    /**
     * @brief Imprime informações dos objetos de Smarthome.
     */
    void printObjetosInfo()const;
    /**
     * @brief Imprime informações dos modos de Smarthome.
     */
    void printModosInfo()const;
    /**
     * @brief Checa se o str contem caracteres que nao sao espaços, letras ou numeros, se houver retorna false.
     */
    bool CaracteresValidos(const std::string& str);
    /**
     * @brief Busca um comodo especifico pelo nome e retorna o ponteiro para ele.
     */
    Comodo* getComodo(std::string nomeComodo);
    
    ~Smarthome();
};
#endif