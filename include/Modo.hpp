#ifndef MODO_HPP
#define MODO_HPP

class ObjetoInteligente;
class Comodo;

#include <vector>
#include <string>

/**
 * @class Modo
 * @brief Representa um modo de funcionamento da smarthome.
 * Armazena informações sobre os objetos inteligentes e cômodos relacionados,
 * além de controlar se o modo está ativo/desativado ou bloqueado/permitido.
 */

class Modo {

    protected:

        /**
         * @brief Armazena o nome do modo.
         */
        std::string nome;

        /**
         * @brief Vetor que armazena os objetos relacionados ao modo.
         */
        std::vector<ObjetoInteligente*> objetosRelacionados;

        /**
         * @brief Vetor que armazena os cômodos relacionados ao modo.
         */
        std::vector<Comodo*> comodosRelacionados;

        /**
         * @brief Indica se o modo está ligado (está sendo executado).
         */
        bool ligado;

        /**
         * @brief Indica se o modo está bloqueado (impedido de ser ativado).
         */
        bool bloqueado;

    public:

        /**
         * @brief Construtor da classe modo.
         */
        Modo(
            std::string nome,
            std::vector<ObjetoInteligente*> objetos,
            std::vector<Comodo*> comodos,
            bool ligado,
            bool bloqueado
        );

        /**
         * @brief Retorna o nome do modo.
         */
        std::string getNome() const;

        /**
         * @brief Define se o modo está ativo ou não.
         */
        void setAtivoModo(bool ativo);

        /**
         * @brief Retorna se o modo está ativo ou não.
         */
        bool getAtivoModo()const;

        /**
         * @brief Define se o modo está bloqueado ou não.
         */
        void setBloqueadoModo(bool bloqueado);

        /**
         * @brief Retorna se o modo está bloqueado ou não.
         */
        bool getBloqueadoModo()const;

        /**
         * @brief Retorna o vetor com os objetos afetados pelo modo.
         */
        std::vector<ObjetoInteligente*> getObjetosRelacionados()const;
        
        /**
         * @brief Retorna o vetor com os cômodos relacionados ao modo.
         */
        std::vector<Comodo*> getComodosRelacionados()const;

        /**
         * @brief Adiciona um cômodo ao vetor de cômodos relacionados.
         * @param comodo Qual cômodo adicionar.
         */
        void adicionarComodoRelacionado(Comodo* comodo);

        /**
         * @brief Tira a conexão com um cômodo relacionado.
         * @param nomeComodo O nome do cômodo a ser removido.
         */
        void removerComodoRelacionado(std::string nomeComodo);

        /**
         * @brief Operador de igualdade da classe.
         */
        bool operator==(const Modo& other) const;

        /**
         * @brief Retorna o nome do modo.
         */
        void printMembrosInfo() const;

        /**
         * @brief Executa a instrução nos cômodos atrelados.
         */
        void executarNosComodosRelacionados();

        /**
         * @brief Executa uma instrução em um objeto específico de um certo comodo.
         * @param objeto Qual objeto a ser afetado.
         * @param comodo Em qual cômodo deve-se aplicar a instrução.
         */
        virtual void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo);
        
        /**
         * @brief Desfaz uma instrução em um objeto específico de um certo comodo.
         * @param objeto Qual objeto a ser afetado.
         * @param comodo Em qual cômodo deve-se desfazer a instrução.
         */
        void desfazerInstrucao(ObjetoInteligente* objeto, Comodo* comodo);

        /**
         * @brief Confere se os caractéres seguem os requisitos do sistema.
         * @param str String a ser conferida.
         */
        bool caracteresValidos (const std::string& str);
        virtual ~Modo() = default;
};

/**
 * @class ModoNoturno
 * @brief Representa o modo noturno da smarthohome.
 * Desliga todos objetos relacionados.
 */

class ModoNoturno : public Modo {
    
    public:
        /**
         * @brief Construtor da subclasse.
         */
        ModoNoturno(std::string nome);

        /**
         * @brief Executa o modo.
         */
        void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) override;
};

/**
 * @class ModoCinema
 * @brief Representa o modo cinema da smarthome.
 * Desliga a luz, liga a TV e a caixa de som.
 */
class ModoCinema : public Modo {
public:
    /**
     * @brief Construtor da classe.
     * @param nome Nome do modo.
     */
    ModoCinema(std::string nome);

    /**
     * @brief Executa o modo.
     * @param objeto Qual objeto a ser afetado.
     * @param comodo Em qual cômodo deve-se aplicar a instrução.
     */
    void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) override;
};


/**
 * @class ModoTrabalho
 * @brief Representa o modo de trabalho da smarthome.
 * Liga a luz, o ar condicionado e desliga a TV.
 */
class ModoTrabalho : public Modo {
public:

    /**
     * @brief Construtor da subclasse.
     */
    ModoTrabalho(std::string nome);

    /**
     * @brief Construtor da subclasse.
     * @param objeto Qual objeto a ser afetado.
     * @param comodo Em qual cômodo deve-se aplicar a instrução.
     */
    void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) override;
};

/**
 * @class ModoAusente
 * @brief Representa o modo ausente da smarthome.
 * Fecha o portão, apaga a luz, desliga a tv, caixa de som e ar condicionado.
 */
class ModoAusente : public Modo {
public:

    /**
     * @brief Construtor da subclasse.
     */
    ModoAusente(std::string nome);

    /**
     * @brief Executa o modo.
     * @param objeto Qual objeto a ser afetado.
     * @param comodo Em qual cômodo deve-se aplicar a instrução.
     */
    void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) override;
};

/**
 * @class ModoFesta
 * @brief Representa o modo festa da smarthome.
 * Liga a caixa de som, a luz e a tv.
 */
class ModoFesta : public Modo {
public:

    /**
     * @brief Construtor da subclasse.
     */
    ModoFesta(std::string nome);

    /**
     * @brief Executa o modo.
     * @param objeto Qual objeto a ser afetado.
     * @param comodo Em qual cômodo deve-se aplicar a instrução.
     */
    void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) override;
};

/**
 * @class ModoEconomia
 * @brief Representa o modo de economia de energia da smarthome.
 * Desliga a luz, ar condicionado, caixa de som e tv.
 */
class ModoEconomia : public Modo {
public:

    /**
     * @brief Construtor da subclasse.
     * @param nome Nome do Modo
     */
    ModoEconomia(std::string nome);

    /**
     * @brief Executa o modo.
     * @param objeto Qual objeto a ser afetado.
     * @param comodo Em qual cômodo deve-se aplicar a instrução.
     */
    void executarInstrucao(ObjetoInteligente* objeto, Comodo* comodo) override;
};

#endif