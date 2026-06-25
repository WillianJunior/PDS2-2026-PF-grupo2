#ifndef SMARTHOME_HPP
#define SMARTHOME_HPP
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include "Comodo.hpp"
#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Conta.hpp"


class Smarthome{
private:
    /**
     * @brief Armazena o usuário que a smarthome pertence.
     */
    Conta* usuario;

    /**
     * @brief Vetor que armazena os cômodos da smarthome.
     */
    std::vector<std::unique_ptr<Comodo>> comodos;

    /**
     * @brief Indica se o objeto é restrito apenas para adultos.
     */
    std::vector<Modo> modos;

    /**
     * @brief Vetor que armazena os objetos da smarthome.
     */
    std::vector<std::unique_ptr<ObjetoInteligente>> objetos;

    /**
     * @brief Armazena o nome da smarthome.
     */
    std::string nome;

public:

    /**
     * @brief Função construtora da smarthome.
     * @param usuario Conta dona da smarthome.
     * @param nome Nome da smarthome.
     */
    Smarthome(Conta* usuario, std :: string nome);

    /**
     * @brief Operador de igualdade da classe.
     */
    bool operator==(const Smarthome& other) const;

    /**
     * @brief Adiciona um modo a uma smarthome.
     * @param modo Modo a ser adicionado à smarthome.
     */
    void adicionarModo(const Modo& modo);
    /**
     * @brief Adiciona um cômodo a uma smarthome.
     * @param comodo Comodo a ser adicionado à smarthome.
     */
    void adicionarComodo(std::unique_ptr<Comodo> comodo);
    /**
     * @brief Adiciona um objeto a uma smarthome.
     * @param objeto Objeto a ser adicionado à smarthome.
     */
    void adicionarObjeto(std::unique_ptr<ObjetoInteligente> objeto);
    /**
     * @brief Remove um cômodo de uma smarthome.
     * @param comodo Comodo a ser removido da smarthome.
     */
    void removerComodo(const Comodo& comodo);
    /**
     * @brief Remove comodo da smarthome por nome do comodo.
     * @param nomeComodo nome do Comodo a ser removido da smarthome.
     */
    void removerComodoPorNome(const std::string& nomeComodo);
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
    const std::vector<std::unique_ptr<ObjetoInteligente>>& getObjetos() const;

    /**
     * @brief Retorna os comodos da smarthome.
     */
    const std::vector<std::unique_ptr<Comodo>>& getComodos() const;

    /**
     * @brief Retorna os modos da smarthome.
     */
    const std::vector<Modo>& getListaModos() const;

    /**
     * @brief Retorna o usuário dono da smarthome.
     */
    Conta* getUsuario() const;
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
     * @param str String a ser verificada.
     */
    bool CaracteresValidos(const std::string& str);
    /**
     * @brief Busca um comodo especifico pelo nome e retorna o ponteiro para ele.
     * @param nomeComodo Nome a ser procurado.
     */
    Comodo* getComodo(std::string nomeComodo);
    /**
     * @brief Busca um modo especifico pelo nome e retorna o ponteiro para ele.
     * @param nomeModo Nome do modo a ser procurado.
     */
    Modo* getModo(std::string nomeModo);

    /**
     * @brief Destrutor da classe.
     */
    ~Smarthome();
};
#endif