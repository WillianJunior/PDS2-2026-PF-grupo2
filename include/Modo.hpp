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

    private:

        std::string nome;

        std::vector<ObjetoInteligente*> objetosRelacionados;
        std::vector<Comodo*> comodosRelacionados;

        bool ligado;
        bool bloqueado;

    public:

        Modo(
            std::string nome,
            std::vector<ObjetoInteligente*> objetos,
            std::vector<Comodo*> comodos,
            bool ligado,
            bool bloqueado
        );

        std::string getNome() const;

        void setAtivoModo(bool ativo);
        bool getAtivoModo();

        void setBloqueadoModo(bool bloqueado);
        bool getBloqueadoModo();

        std::vector<ObjetoInteligente*> getObjetosRelacionados();
        std::vector<Comodo*> getComodosRelacionados();

        bool operator==(const Modo& other) const;

        void printMembrosInfo() const;
};

#endif