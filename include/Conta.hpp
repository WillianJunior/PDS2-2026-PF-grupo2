#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>
// #include "Smarthome.hpp"
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
    // std::vector<Smarthome> smarthomes; // vetor que armazena as smarthomes da conta

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
    // void apagarSmarthome(Smarthome smarthome);

};
#endif