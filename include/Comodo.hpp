/** @file */
#ifndef COMODO_HPP
#define COMODO_HPP
#pragma once

#include <string>
#include <vector>
#include <memory>

class Smarthome;
class Conta;
class Sensor;
class ObjetoInteligente;
class Modo;

/**
 * @class Comodo
 * @brief Representa um cômodo físico dentro de uma Smarthome.
 *
 * Esta classe é responsável por gerenciar as condições do ambiente e agrupar
 * logicamente objetos inteligentes, sensores, contas presentes e modos de automação.
 */
class Comodo {
public:
    /**
     * @brief Construtor da classe Comodo.
     * @param nome Nome do cômodo (ex: "Sala", "Quarto").
     * @param casa Ponteiro para a Smarthome à qual este cômodo pertence.
     */
    Comodo(const std::string& nome, Smarthome* casa);

    /**
     * @brief Sobrecarga do operador de igualdade para comparar se dois cômodos são o mesmo.
     * @param other Cômodo a ser comparado.
     * @return true se possuírem o mesmo nome e pertencerem à mesma Smarthome, false caso contrário.
     */
    bool operator==(const Comodo& other) const;

    /**
     * @brief Retorna as condições climáticas e físicas do ambiente do cômodo.
     * @return Vetor de strings contendo as condições atuais.
     */
    std::vector<std::string> getCondicoesDoComodo() const;

    /**
     * @brief Muda uma condição do cômodo, desativando automaticamente a sua condição oposta.
     * @param condicao Nova condição a ser estabelecida.
     */
    void mudarCondicao(const std::string& condicao);

    /**
     * @brief Adiciona uma nova condição ao cômodo.
     * @param condicao Nova condição a ser adicionada.
     */
    void adicionarCondicao(const std::string& condicao);

    /**
     * @brief Adiciona um Objeto Inteligente ao cômodo.
     * @param objeto Ponteiro para o Objeto Inteligente a ser inserido.
     */
    void adicionarObjeto(ObjetoInteligente* objeto);

    /**
     * @brief Adiciona um Sensor ao cômodo.
     * @param sensor Smart pointer (unique_ptr) do Sensor a ser inserido.
     */
    void adicionarSensor(std::unique_ptr<Sensor> sensor);

    /**
     * @brief Vincula um Modo ao cômodo.
     * @param modo Ponteiro para o Modo a ser adicionado.
     */
    void adicionarModo(Modo* modo);

    /**
     * @brief Retorna a lista de objetos inteligentes do cômodo.
     * @return Vetor contendo ponteiros para os objetos inteligentes.
     */
    const std::vector<ObjetoInteligente*>& getObjetos() const;

    /**
     * @brief Retorna a lista de sensores instalados no cômodo.
     * @return Vetor contendo smart pointers para os sensores.
     */
    const std::vector<std::unique_ptr<Sensor>>& getSensores() const;

    /**
     * @brief Retorna a lista de modos vinculados ao cômodo.
     * @return Vetor contendo ponteiros para os modos.
     */
    const std::vector<Modo*>& getModos() const;

    /**
     * @brief Remove um modo vinculado ao cômodo buscando pelo seu nome.
     * @param nomeModo Nome exato do modo a ser removido.
     */
    void removerModoPorNome(const std::string& nomeModo);

    /**
     * @brief Remove um objeto inteligente do cômodo buscando pelo seu nome.
     * @param nomeObjeto Nome exato do objeto a ser removido.
     */
    void removerObjetoPorNome(const std::string& nomeObjeto);

    /**
     * @brief Remove um sensor do cômodo buscando pelo seu nome.
     * @param nomeSensor Nome exato do sensor a ser removido.
     */
    void removerSensorPorNome(const std::string& nomeSensor);

    /**
     * @brief Insere uma conta na lista de contas presentes (fisicamente) no cômodo.
     * @param conta Ponteiro para a conta que entrou no ambiente.
     */
    void entrarConta(Conta* conta);

    /**
     * @brief Remove a conta mais antiga da lista de contas presentes no cômodo (Lógica FIFO).
     */
    void sairConta();

    /**
     * @brief Repassa a instrução de ativar ou desativar de um modo para os objetos contidos neste cômodo.
     * @param modo Ponteiro para o modo cujas instruções serão aplicadas.
     */
    void repassarInstrucao(Modo* modo);

    /**
     * @brief Retorna a lista de contas atualmente presentes no cômodo.
     * @return Vetor contendo ponteiros para as contas presentes.
     */
    const std::vector<Conta*>& getContasPresentes() const;

    /**
     * @brief Retorna o nome atribuído ao cômodo.
     * @return String contendo o nome do cômodo.
     */
    std::string getNome() const;

    /**
     * @brief Retorna a instância da Smarthome matriz do cômodo.
     * @return Ponteiro para a Smarthome à qual este cômodo pertence.
     */
    Smarthome* getSmarthome() const;

    /**
     * @brief Imprime no terminal as informações e status de todos os objetos deste cômodo.
     */
    void printObjetosInfo() const;

    /**
     * @brief Imprime no terminal as informações e status de todos os sensores deste cômodo.
     */
    void printSensoresInfo() const;

    /**
     * @brief Imprime no terminal os dados das contas presentes neste cômodo.
     */
    void printContasInfo() const;

    /**
     * @brief Imprime no terminal os dados dos modos vinculados a este cômodo.
     */
    void printModosInfo() const;

    /**
     * @brief Valida se a string fornecida contém apenas letras, números ou espaços.
     * @param str Texto a ser avaliado.
     * @return true se o texto não possuir caracteres especiais, false caso possua.
     */
    bool CaracteresValidos(const std::string& str) const;

    /**
     * @brief Destrutor padrão da classe Comodo.
     */
    ~Comodo();

private:
    /** @brief Nome de identificação do cômodo. */
    std::string nome;
    
    /** @brief Ponteiro para a Smarthome à qual este cômodo pertence. */
    Smarthome* casa;

    /** @brief Vetor que armazena as condições atuais do ambiente físico. */
    std::vector<std::string> condicoesDoComodo = {
        "Iluminado", "Escuro", "Quente", "Frio",
        "Umido", "Seco", "Barulhento", "Silencioso"
    };

    /** @brief Lista de contas que estão fisicamente presentes no cômodo no momento. */
    std::vector<Conta*> contasPresentes;
    
    /** @brief Lista de ponteiros para os objetos inteligentes alocados neste cômodo. */
    std::vector<ObjetoInteligente*> objetos;
    
    /** @brief Lista de smart pointers dos sensores instalados no ambiente. */
    std::vector<std::unique_ptr<Sensor>> sensores;
    
    /** @brief Lista de modos de automação vinculados aos dispositivos deste cômodo. */
    std::vector<Modo*> modos;
};

#endif