#ifndef LOGIN_HPP
#define LOGIN_HPP

#include "Conta.hpp"

#include <vector>
#include <string>

/**
 * @class Login
 * @brief Responsável pela criação de contas, bloquear/desbloquear contas e armazenar todas as contas cadastradas no sistema.
 */

 class Login{
    private:
        /**
         * @brief Vetor que armazena as contas cadastradas.
         */
        std::vector<Conta> contas;

    public:
        /**
         * @brief Construtor da classe Login.
         * @param contasCadastradas Vetor inicial das contas já cadastradas.
         */
        Login(std::vector<Conta> contasCadastradas);
        /**
         * @brief Cadastra uma nova conta
         * @param contaNova Conta que sera cadastrada.
         */
        void criarConta(Conta contaNova);
        /**
         * @brief Realiza autenticação de uma conta.
         *  Procura o email e verifica se a senha fornecida está correta.
         * @param email Email digitado.
         * @param senha Senha digitada.
         * @return true= autenticação válida.
         */
        bool autenticarConta(std::string email, std::string senha);
        /**
         * @brief Verifica se a conta está bloqueada
         * true= conta bloqueada
         */
        bool bloquearConta(std::string email);
        /**
         * @brief Retorna as contas cadastradas.
         * @return Vetor de contas.
         */
        std::vector<Conta> getContasCadastradas();

    };
#endif