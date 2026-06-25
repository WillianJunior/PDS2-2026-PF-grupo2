/** @file */
#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "Login.hpp"
#include "Conta.hpp"
#include "Smarthome.hpp"
#include "Comodo.hpp"
#include <iostream>
#include <vector>
#include <memory>

/**
 * @class Interface
 * @brief Classe responsável por gerenciar a interação do usuário com o sistema via terminal.
 * 
 * Centraliza os menus de navegação, fluxos de login, cadastro e a visualização 
 * dos dados da Smarthome, servindo como o "front-end" em modo texto da aplicação.
 */
class Interface {
private:
    /** @brief Instância do sistema de login que gerencia as contas cadastradas. */
    Login sistemaLogin;
    
    /** @brief Ponteiro para a conta do usuário que está atualmente autenticado e utilizando o sistema. */
    Conta* usuarioLogado = nullptr;

    /** @brief Indica se estou fazendo um teste ou nao (usado para evitar exit(0)) */
    bool modoTeste = false;

    /**
     * @brief Exibe o menu inicial do sistema (Login, Cadastro ou Sair).
     */
    void exibirMenuInicial();
    
    /**
     * @brief Exibe o painel principal da conta logada, permitindo gerenciar ou acessar Smarthomes.
     */
    void exibirMenuConta();
    
    /**
     * @brief Exibe a lista de Smarthomes vinculadas ao usuário para seleção.
     */
    void exibirMenuSmarthome();
    
    /**
     * @brief Inicia o fluxo de gerenciamento de uma Smarthome específica.
     * @param casa Ponteiro para a Smarthome que será gerenciada.
     */
    void gerenciarSmarthome(Smarthome* casa);
    
    /**
     * @brief Exibe o menu de listagem e criação de cômodos da casa.
     * @param casa Ponteiro para a Smarthome atual.
     */
    void exibirMenuComodos(Smarthome* casa);
    
    /**
     * @brief Acessa o painel de controle de um cômodo específico para gerenciar objetos e sensores.
     * @param casa Ponteiro para a Smarthome à qual o cômodo pertence.
     * @param comodo Ponteiro para o Cômodo a ser gerenciado.
     */
    void gerenciarComodoEspecifico(Smarthome* casa, Comodo* comodo);
    
    /**
     * @brief Exibe o menu para criação, listagem e remoção de modos da Smarthome.
     * @param casa Ponteiro para a Smarthome atual.
     */
    void exibirMenuModos(Smarthome* casa);
    
    /**
     * @brief Inicia o fluxo de configuração e acionamento de um modo específico.
     * @param casa Ponteiro para a Smarthome atual.
     * @param nomeModo Nome do modo que será configurado ou ativado.
     */
    void gerenciarModoEspecifico(Smarthome* casa, std::string nomeModo);
    
    /**
     * @brief Auxilia a criação rápida de uma casa com cômodos pré-definidos.
     * @param casa Ponteiro para a Smarthome que receberá a configuração padrão.
     */
    void criarCasaPadrao(Smarthome* casa);
    
    /**
     * @brief Imprime no terminal um esquema visual simplificado listando os cômodos e seus modos associados.
     * @param casa Ponteiro para a Smarthome atual.
     */
    void mostrarPlantaCasa(Smarthome* casa);
    
    /**
     * @brief Captura os dados de e-mail e senha no terminal e repassa para o sistema de autenticação.
     */
    void realizarLogin();
    
    /**
     * @brief Coleta as informações do usuário no terminal para instanciar uma nova Conta no sistema.
     */
    void cadastrarConta();

public:
    /**
     * @brief Construtor padrão da Interface. 
     * 
     * Inicializa o sistema criando uma conta administrador padrão para testes.
     */
    Interface();
    
    /**
     * @brief Inicia o loop principal do programa, prendendo a execução na navegação dos menus.
     */
    void iniciar();

    /**
     * @brief Inicia o loop principal do programa, prendendo a execução na navegação dos menus para testes.
     */
    void iniciarTeste();
};

#endif