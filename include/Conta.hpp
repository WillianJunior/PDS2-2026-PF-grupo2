/** @file */
#ifndef CONTA_HPP
#define CONTA_HPP

#include <string>
#include <memory>
#include "ObjetoInteligente.hpp"
#include "Smarthome.hpp"
#include <vector>
#include <fstream>
class Smarthome;
class Comodo;
class Sensor;
class Modo;

/**
 * @brief Classe responsável por gerenciar o perfil do usuário no sistema.
 * 
 * Esta classe atende a User Story Criação de Perfil e User Story Controle Parental,
 * diferenciando usuários adultos de infantis.
 */
class Conta {
private:
    /** @brief Identificador único da conta. */
    std::string id;
    
    /** @brief Nome completo do usuário. */
    std::string nome;
    
    /** @brief E-mail utilizado para o login. */
    std::string email;
    
    /** @brief Senha de acesso ao sistema. */
    std::string senha;
    
    /** @brief Indicador de perfil: true para Adulto, false para Infantil. */
    bool perfilAdulto; 
    
    /** @brief Indicador de acesso: true para conta bloqueada, false para ativa. */
    bool bloqueada; 
    
    /** @brief Vetor que armazena os smart pointers das smarthomes pertencentes à conta. */
    std::vector<std::unique_ptr<Smarthome>> smarthomes; 

public:
    /**
     * @brief Construtor da classe Conta.
     * @param id Identificador único da conta.
     * @param nome Nome do usuário.
     * @param email E-mail para login.
     * @param senha Senha de acesso.
     * @param adulto Define se o perfil é de administrador/adulto (true).
     */
    Conta(const std::string& id,
      const std::string& nome,
      const std::string& email,
      const std::string& senha,
      bool adulto = true);
      
    ~Conta() = default;

    // Métodos Getters
    /**
     * @brief Retorna o id da conta.
     * @return String constante contendo o ID.
     */
    const std::string& getId() const;
    
    /**
     * @brief Retorna o nome da conta.
     * @return String constante contendo o nome.
     */
    const std::string& getNome() const;
    
    /**
     * @brief Retorna o email da conta.
     * @return String constante contendo o e-mail.
     */
    const std::string& getEmail() const;
    
    /**
     * @brief Verifica se o perfil da conta é de adulto.
     * @return true se for adulto, false se for infantil.
     */
    bool isPerfilAdulto() const; 
    
    /**
     * @brief Verifica se a conta está bloqueada.
     * @return true se a conta estiver bloqueada, false caso contrário.
     */
    bool estaBloqueada() const;

    /**
     * @brief Retorna a lista de smarthomes da conta.
     * @return Referência constante para o vetor de unique_ptrs de Smarthomes.
     */
    const std::vector<std::unique_ptr<Smarthome>>& getSmarthomes() const;

    /**
     * @brief Bloqueia a conta, impedindo o acesso.
     */
    void bloquear();

    /**
     * @brief Desbloqueia a conta, permitindo o acesso novamente.
     */
    void desbloquear();

    /**
     * @brief Comando para criar uma smarthome e vinculá-la à conta.
     * @param id Identificador único da smarthome.
     * @param nome Nome da smarthome.
     */
    void criarSmarthome(const std::string& id, const std::string& nome);
    
    /**
     * @brief Comando para remover uma smarthome da conta.
     * @param smarthome Referência da Smarthome a ser apagada.
     */
    void apagarSmarthome(const Smarthome& smarthome);

    /**
     * @brief Comando para criar um cômodo dentro de uma smarthome específica.
     * @param smarthome Ponteiro para a Smarthome em que o cômodo será adicionado.
     * @param nome Nome do cômodo.
     */
    void criarComodo(Smarthome* smarthome, const std::string& nome);

    /**
     * @brief Comando para apagar um cômodo de uma smarthome.
     * @param smarthome Ponteiro para a Smarthome de onde o cômodo será apagado.
     * @param nome Nome do cômodo a ser removido.
     */
    void apagarComodo(Smarthome* smarthome, const std::string& nome);

    /**
     * @brief Comando para criar um modo customizado vazio.
     * @param smarthome Ponteiro para a Smarthome em que o modo será adicionado.
     * @param nome Nome do modo que será adicionado.
     */
    void criarModo(Smarthome* smarthome, const std::string& nome);

    /**
     * @brief Comando para criar um modo de um tipo específico (pré-configurado).
     * @param smarthome Ponteiro para a Smarthome em que o modo será adicionado.
     * @param nome Nome do modo que será criado.
     * @param tipoModo Tipo do modo a ser criado:
     * 1 = Modo comum
     * 2 = Modo Cinema
     * 3 = Modo Noturno
     * 4 = Modo Trabalho
     * 5 = Modo Ausente
     * 6 = Modo Festa
     */
    void criarModoPorTipo(Smarthome* smarthome, const std::string& nome, int tipoModo);
    
    /**
     * @brief Comando para remover um modo do sistema.
     * @param smarthome Ponteiro para a Smarthome de onde o modo será removido.
     * @param nome Nome exato do modo que será removido.
     */
    void apagarModo(Smarthome* smarthome, const std::string& nome);

    /**
     * @brief Comando genérico para criar um objeto inteligente.
     * @param smarthome Ponteiro para a Smarthome em que o objeto será adicionado.
     * @param comodo Ponteiro para o Cômodo em que o objeto será posicionado.
     * @param nome Nome do objeto inteligente a ser criado.
     */
    void criarObjeto(Smarthome* smarthome, Comodo* comodo, const std::string& nome);
    
    /**
     * @brief Comando para apagar um objeto inteligente existente.
     * @param smarthome Ponteiro para a Smarthome de onde o objeto será apagado.
     * @param comodo Ponteiro para o Cômodo de onde o objeto será retirado.
     * @param nome Nome exato do objeto a ser apagado.
     */
    void apagarObjeto(Smarthome* smarthome, Comodo* comodo, const std::string& nome);
    
    /**
     * @brief Comando para mover um objeto inteligente entre cômodos físicos.
     * @param smarthome Ponteiro para a Smarthome base.
     * @param atual Ponteiro para o Cômodo de origem do objeto.
     * @param nome Nome do objeto que será movido.
     * @param destino Ponteiro para o Cômodo de destino do objeto.
     */
    void moverObjeto(Smarthome* smarthome, Comodo* atual, const std::string& nome, Comodo* destino);

    /**
     * @brief Comando para criar um novo sensor no ambiente.
     * @param smarthome Ponteiro para a Smarthome em que o sensor será adicionado.
     * @param comodo Ponteiro para o Cômodo em que o sensor será instalado.
     * @param nome Nome do sensor a ser criado.
     */
    void criarSensor(Smarthome* smarthome, Comodo* comodo, const std::string& nome);
    
    /**
     * @brief Comando para apagar um sensor existente.
     * @param smarthome Ponteiro para a Smarthome de onde o sensor será apagado.
     * @param comodo Ponteiro para o Cômodo de onde o sensor será retirado.
     * @param nome Nome exato do sensor a ser apagado.
     */
    void apagarSensor(Smarthome* smarthome, Comodo* comodo, const std::string& nome);
    
    /**
     * @brief Comando para mover um sensor de um cômodo para outro.
     * @param smarthome Ponteiro para a Smarthome.
     * @param atual Ponteiro para o Cômodo de origem do sensor.
     * @param nome Nome exato do sensor a ser movido.
     * @param destino Ponteiro para o Cômodo de destino do sensor.
     */
    void moverSensor(Smarthome* smarthome, Comodo* atual, const std::string& nome, Comodo* destino);

    /**
     * @brief Comando para gerar relatório consolidado de gasto de energia da casa.
     * @param smarthome Ponteiro para a Smarthome que terá seu gasto calculado.
     * @return float O valor total do consumo médio de energia em kWh.
     */
    float gerarRelatorioDeEnergia(Smarthome* smarthome);

    /**
     * @brief Valida se o formato do e-mail da conta é estruturalmente válido.
     * @return true se possuir formato válido (ex: contém '@'), false caso contrário.
     */
    bool validarFormatoEmail() const;
    
    /**
     * @brief Verifica se a senha atende aos requisitos mínimos de segurança.
     * @return true se a senha for considerada segura, false caso contrário.
     */
    bool validarSenha() const;
    
    /**
     * @brief Autentica a conta comparando a senha armazenada com a fornecida.
     * @param tentativaSenha Senha digitada no momento do login.
     * @return true se as senhas coincidirem, false caso contrário.
     */
    bool autenticar(const std::string& tentativaSenha) const;
    
    /**
     * @brief Sobrecarga do operador de igualdade para comparar contas.
     * @param other Conta a ser comparada.
     * @return true se os dados das contas forem idênticos, false caso contrário.
     */
    bool operator == (const Conta& other) const;
    
    /**
     * @brief Imprime no terminal as informações básicas (membros/atributos) da conta.
     */
    void printMembrosInfo() const;
    
    /**
     * @brief Checa se a string contém caracteres válidos (apenas letras, espaços ou números).
     * @param str Texto a ser analisado.
     * @return true se for válido, false se contiver caracteres especiais.
     */
    bool CaracteresValidos (const std::string& str) const;
    
    /**
     * @brief Retorna a senha atual da conta.
     * @return String constante contendo a senha.
     */
    const std::string& getSenha() const;
    
    /**
     * @brief Salva todas as smarthomes da conta em um arquivo de texto (.txt).
     */
    void salvarSmarthomesEmArquivo() const;
    
    /**
     * @brief Carrega as smarthomes a partir de um arquivo de texto (.txt) salvo previamente.
     */
    void carregarSmarthomesDeArquivo();
    
    /**
     * @brief Comando para criar um objeto inteligente de um tipo derivado específico.
     * @param smarthome Ponteiro para a Smarthome em que o objeto será adicionado.
     * @param comodo Ponteiro para o Cômodo em que o objeto será adicionado.
     * @param nome Nome do objeto inteligente.
     * @param tipoObjeto Inteiro que define o tipo do objeto a ser instanciado:
     * 1 = Luz
     * 2 = TV
     * 3 = Caixa de Som
     * 4 = Ar Condicionado
     * 5 = Portão
     * 6 = Termostato
     */
    void criarObjetoPorTipo(Smarthome* smarthome, Comodo* comodo, std::string nome, int tipoObjeto);
};

#endif