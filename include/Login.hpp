/** @file */
#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "Conta.hpp"

#include <vector>
#include <string>

/**
 * @class Login
 * @brief Responsável pela criação de contas, bloquear/desbloquear contas e armazenar todas as contas cadastradas no sistema.
 */
class Login {
    private:
        /**
         * @brief Vetor que armazena os smart pointers das contas cadastradas.
         */
        std::vector<std::unique_ptr<Conta>> contas;

    public:
        /**
         * @brief Construtor da classe Login.
         * @param contasCadastradas Vetor inicial (movido) das contas já cadastradas.
         */
        Login(std::vector<std::unique_ptr<Conta>>&& contasCadastradas);
        
        /**
         * @brief Cadastra uma nova conta no sistema.
         * @param contaNova Smart pointer único da Conta que será cadastrada.
         */
        void criarConta(std::unique_ptr<Conta> contaNova);
        
        /**
         * @brief Realiza a autenticação de uma conta no sistema.
         * 
         * Procura o e-mail na base de dados e verifica se a senha fornecida está correta.
         * @param email E-mail digitado pelo usuário.
         * @param senha Senha digitada pelo usuário.
         * @return true se a autenticação for válida, false caso as credenciais estejam erradas ou a conta não exista.
         */
        bool autenticarConta(std::string email, std::string senha);
        
        /**
         * @brief Verifica e altera o status de bloqueio de uma conta específica.
         * @param email E-mail da conta a ser bloqueada.
         * @return true se a conta foi encontrada e bloqueada com sucesso, false caso contrário.
         */
        bool bloquearConta(std::string email);
        
        /**
         * @brief Retorna a lista de todas as contas cadastradas no sistema.
         * @return Referência constante para o vetor contendo os smart pointers das contas.
         */
        const std::vector<std::unique_ptr<Conta>>& getContasCadastradas() const;

};
#endif