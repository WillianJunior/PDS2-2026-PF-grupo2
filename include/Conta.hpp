#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>

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

    virtual ~Conta() = default;

    // Métodos Getters
    std::string getId() const;
    std::string getNome() const;
    std::string getEmail() const;
    bool isPerfilAdulto() const; 

    // Métodos de Regra de Negócio (User Story 1 e 2)
    
    /**
     * @brief Valida se a formatação do e-mail é válida (ex: contém '@' e '.').
     * @return true se for válido, false caso contrário.
     */
    bool validarEmailFormato() const;

    /**
     * @brief Verifica se a senha fornecida atende aos requisitos mínimos de segurança.
     * @return true se a senha for segura.
     */
    bool validarSenhaSegura() const;

    /**
     * @brief Autentica o usuário comparando a senha digitada com a senha armazenada.
     * @param senhaTentativa Senha digitada no login.
     * @return true se as senhas baterem.
     */
    bool autenticar(const std::string& senhaTentativa) const;
};
#endif