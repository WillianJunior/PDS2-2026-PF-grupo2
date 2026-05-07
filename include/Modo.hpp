#ifndef MODO_HPP
#define MODO_HPP

#include "ObjetoInteligente.hpp"
#include "Comodo.hpp"

#include <vector>

/**
 * @class Modo
 * @brief Representa um modo de funcionamento da smarthome.
 * Armazena informações sobre os objetos inteligentese cômodos relacionados, além de controlar se o modo está ativo/desativado ou bloqueado/permitido.
 */ 

class Modo{


    private:

        std::vector<ObjetoInteligente> objetosRelacionados;
        std::vector<Comodo> comodosRelacionados;


         /**
         * @brief Indica se o modo está ativo  (true = ligado/false = desligado)
         */
        bool ligado; 
         /**
         * @brief Indica se o modo está bloqueado: se estiver bloqueado, o modo não funcionará mesmo estando ligado.
         */
        bool bloqueado;

    public:
        /**
         * @brief Construtor da classe.
        * @param objetos Objetos relacionados ao modo.
        * @param comodos Cômodos relacionados ao modo.
        * @param ligado Estado inicial do modo.
        * @param bloqueado Estado de bloqueio do modo.
         */
         Modo(
            std::vector<ObjetoInteligente> objetos,
            std::vector<Comodo> comodos,
            bool ligado,
            bool bloqueado
        );

         /**
         * @brief Ativa ou desativa o modo.
         * @param ativo Estado do modo.
         */
        void setAtivoModo(bool ativo);
        bool getAtivoModo();

        /**
         * @brief Retorna se o modo está ativo.
         * @return Estado do modo.
         */
        void setBloqueadoModo(bool bloqueado);
        bool getBloqueadoModo();

        std::vector<ObjetoInteligente> getObjetosRelacionados();
        std::vector<Comodo> getComodosRelacionados();



};

#endif