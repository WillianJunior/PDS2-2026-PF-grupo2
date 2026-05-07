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
    std::string getId() const;
    std::string getNome() const;
    std::string getEmail() const;
    bool isPerfilAdulto() const; 

    /**
     * @brief Comando para criar uma smarthome.
     * @param id Identificador único da smarthome.
     * @param nome Nome da smarthome.
     */
    void criarSmarthome(std::string id, std::string nome);
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
     * @param nome Nome da smarthome em que o cômodo será adicionado.
     */
    void criarModo(Smarthome smarthome, std::string nome);
    void apagarModo(Smarthome smarthome, std::string nome);
    void editarModo(Smarthome smarthome, std::string nome);

    /**
     * @brief Comando para criar um objeto inteligente.
     * @param smarthome Smarthome em que o objeto será adicionado.
     * @param comodo Comodo em que o objeto será adicionado.
     * @param nome Nome da smarthome em que o cômodo será adicionado.
     */
    void criarObjeto(Smarthome smarthome, Comodo comodo, std::string nome);
    void apagarObjeto(Smarthome smarthome, Comodo comodo, std::string nome);
    void moverObjeto(Smarthome smarthome, Comodo comodo, std::string nome);

    /**
     * @brief Comando para criar um sensor.
     * @param smarthome Smarthome em que o objeto será adicionado.
     * @param comodo Comodo em que o objeto será adicionado.
     * @param nome Nome da smarthome em que o cômodo será adicionado.
     */
    void criarSensor(Smarthome smarthome, Comodo comodo, std::string nome);
    void apagarSensor(Smarthome smarthome, Comodo comodo, std::string nome);
    void moverSensor(Smarthome smarthome, Comodo comodo, std::string nome);

     /**
     * @brief Valida se o formato do e-mail é válido.
     * @return true=válido.
     */
    bool validarFormatoEmail() const;
    /**
     * @brief Verifica se a senha atende de segurança.
     * @return true = segura.
     */
    bool validarSenha() const;
    /**
     * @brief Autentica a conta comparando a senha fornecida.
     * @param tentativaSenha Senha digitada no login.
     * @return true = correta.
     */
    bool autenticar(const std::string& tentativaSenha) const;
};
#endif