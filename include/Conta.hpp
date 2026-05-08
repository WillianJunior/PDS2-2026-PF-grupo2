/** @file */
#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>
#include "Smarthome.hpp"
#include "ObjetoInteligente.hpp"
#include "Sensor.hpp"
#include "Comodo.hpp"
#include "Modo.hpp"


#include <vector>


/**
 * @brief Classe responsável por gerenciar o perfil do usuário no sistema.
 * 
 * Esta classe atende a User Story Criação de Perfil e User Story Controle Parental,
 * diferenciando usuários adultos de infantis.
 */
class Conta {
private:
    std::string id;
    std::string nome;
    std::string email;
    std::string senha;
    bool perfilAdulto; // true para Adulto, false para Infantil.
    std::vector<Smarthome> smarthomes; // vetor que armazena as smarthomes da conta

public:
    /**
     * @brief Construtor da classe Conta.
     * @param id Identificador único da conta.
     * @param nome Nome do usuário.
     * @param email E-mail para login.
     * @param senha Senha de acesso.
     * @param adulto Define se o perfil é de administrador/adulto (true).
     */
    Conta(std::string id, std::string nome, std::string email, std::string senha, bool adulto = true);

    ~Conta() = default;

    // Métodos Getters
    /**
     * @brief Retorna o id da conta.
     */
    std::string getId() const;
    /**
     * @brief Retorna o nome da conta.
     */
    std::string getNome() const;
    /**
     * @brief Retorna o email da conta.
     */
    std::string getEmail() const;
    /**
     * @brief Retorna o nome da conta.
     */
    bool isPerfilAdulto() const; 

    /**
     * @brief Comando para criar uma smarthome.
     * @param id Identificador único da smarthome.
     * @param nome Nome da smarthome.
     */
    void criarSmarthome(std::string id, std::string nome);
    /**
     * @brief Comando para criar uma smarthome.
     * @param smarthome Smarthome a ser apagada.
     */
    void apagarSmarthome(Smarthome smarthome);

    /**
     * @brief Comando para criar um cômodo.
     * @param smarthome Smarthome em que o cômodo será adicionado.
     * @param nome Nome do cômodo.
     */
    void criarCômodo(Smarthome smarthome, std::string nome);
    void apagarCômodo(Smarthome smarthome, std::string nome);

    /**
     * @brief Comando para criar um modo.
     * @param smarthome Smarthome em que o modo será adicionado.
     * @param nome Nome do modo que será adicionado.
     */
    void criarModo(Smarthome smarthome, std::string nome);

    /**
     * @brief Comando para remover um modo.
     * @param smarthome Smarthome em que o modo será removido.
     * @param nome Nome do modo que será removido.
     */
    void apagarModo(Smarthome smarthome, std::string nome);

    /**
     * @brief Comando para editar um modo.
     * @param smarthome Smarthome em que o modo será editado.
     * @param nome Nome do modo a ser editado.
     */
    void editarModo(Smarthome smarthome, std::string nome);

    /**
     * @brief Comando para criar um objeto inteligente.
     * @param smarthome Smarthome em que o objeto será adicionado.
     * @param comodo Comodo em que o objeto será adicionado.
     * @param nome Nome da smarthome em que o cômodo será adicionado.
     */
    void criarObjeto(Smarthome smarthome, Comodo comodo, std::string nome);
    
     /**
     * @brief Comando para apagar um objeto inteligente.
     * @param smarthome Smarthome em que o objeto será apagado.
     * @param comodo Comodo em que o objeto será apagado.
     * @param nome Nome da smarthome em que o cômodo será apagado.
     */
    void apagarObjeto(Smarthome smarthome, Comodo comodo, std::string nome);
    
     /**
     * @brief Comando para mover um objeto inteligente.
     * @param smarthome Smarthome em que o objeto será adicionado.
     * @param atual Comodo de origem do objeto.
     * @param nome Nome do objeto que será movido.
     * @param destino Comodo de destiono do objeto.
     * 
     */
    void moverObjeto(Smarthome smarthome, Comodo atual, std::string nome, Comodo destino);

    /**
     * @brief Comando para criar um sensor.
     * @param smarthome Smarthome em que o objeto será adicionado.
     * @param comodo Comodo em que o objeto será adicionado.
     * @param nome Nome da smarthome em que o cômodo será adicionado.
     */
    void criarSensor(Smarthome smarthome, Comodo comodo, std::string nome);
    
    /**
     * @brief Comando para apagar um sensor.
     * @param smarthome Smarthome em que o objeto será apagado.
     * @param comodo Comodo em que o objeto será apagado.
     * @param nome Nome da smarthome em que o cômodo será apagado.
     */
    void apagarSensor(Smarthome smarthome, Comodo comodo, std::string nome);
    
    /**
     * @brief Comando para mover um sensor.
     * @param smarthome Smarthome em que o objeto será movido.
     * @param atual Comodo de origem do sensor.
     * @param nome Nome da smarthome a ser movido.
     * @param destino Comodo de destino do sensor.
     */
    void moverSensor(Smarthome smarthome, Comodo atual, std::string nome, Comodo destino);


    /**
     * @brief Comando para gerar relatório de gasto de energia.
     * @param smarthome Smarthome a ter seu gasto de energia calculado.
     */
    float gerarRelatórioDeEnergia(Smarthome smarthome);

};
#endif