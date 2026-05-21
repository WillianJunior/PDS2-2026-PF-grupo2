#include <string>
#include <vector>
#include "Comodo.hpp"
#include "ObjetoInteligente.hpp"
#include "Smarthome.hpp"
#include "Sensor.hpp"
#include "Modo.hpp"
#include "doctest.h"

ObjetoInteligente DummyObjeto() {
    std::vector<Sensor> sensores; // vazio ou falso
    std::vector<std::string> status = {"on","off"};
    float consumo = 5.0f;
    std::vector<std::function<void()>> funcoes = {[]{ }};
    std::vector<std::function<void()>> funcoesRestritas = {[]{ }};
    return ObjetoInteligente(false, sensores, status, consumo, funcoes, funcoesRestritas);
}
Sensor DummySensor(){
   std::vector<ObjetoInteligente> objetosConectados;
   std::vector<Modo> modosConectados;
   return Sensor(true, true, objetosConectados, modosConectados);
}
Modo DummyModo () {
    std::vector<ObjetoInteligente> objetos;
    std::vector<Comodo> comodos;
   return Modo(objetos, comodos, true, false);     
}    

   //Comodo(std::string nome, SmartHome* casa);
 TEST_CASE("TESTE 1 construtor - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );

   CHECK(comodoTeste.getNome() == "comodoTeste");
   CHECK(comodoTeste.getSmarthome() == &smarthome);
      SUBCASE("TESTE 1.1 nome do Comodo vazio"){
         Comodo comodoTeste("", &smarthome);
         CHECK(comodoTeste.getNome() == "");
      } 
      SUBCASE("TESTE 1.2 ponteiro smarthome em Comodo nullptr"){
         CHECK_THROWS(Comodo ("comodoTeste", nullptr));
      }
      SUBCASE("TESTE 1.3 nome Comodo longo"){
         std::string longName(1000, 'A');
         Comodo comodoTeste(longName, &smarthome);
         CHECK(comodoTeste.getNome().size() == 1000);
      }
  }
    //void adicionarObjeto(ObjetoInteligente* objeto);
 TEST_CASE("TESTE 2 adiconarObjeto - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );
   auto obj = DummyObjeto();
   comodoTeste.adicionarObjeto(&obj);
   CHECK(comodoTeste.getObjetos().size() == 1);
      SUBCASE("TESTE 2.1 ponteiro de Objetos nullptr"){
         CHECK_THROWS(comodoTeste.adicionarObjeto(nullptr));
      }
      SUBCASE("TESTE 2.2 Objetos iguais adicionados"){
         auto obj = DummyObjeto();
         comodoTeste.adicionarObjeto(&obj);
         CHECK(comodoTeste.getObjetos().size() == 1);
         comodoTeste.adicionarObjeto(&obj);
         CHECK(comodoTeste.getObjetos().size() == 1);
      }
   

}
    //void adicionarSensor(Sensor* sensor);
 TEST_CASE("TESTE 3 adiconarSensor - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );
   auto sensor = DummySensor();
   comodoTeste.adicionarSensor(&sensor);
   CHECK(comodoTeste.getSensores().size() == 1);
      SUBCASE("TESTE 3.1 ponteiro de Sensor nullptr"){
         CHECK_THROWS(comodoTeste.adicionarSensor(nullptr));
      }
      SUBCASE("TESTE 3.2 Sensores iguais adicionados"){
         auto sensor = DummySensor();
         comodoTeste.adicionarSensor(&sensor);
         CHECK(comodoTeste.getSensores().size() == 1);
         comodoTeste.adicionarSensor(&sensor);
         CHECK(comodoTeste.getSensores().size() == 1);
      }

}

    //void adicionarModo(Modo* modo);
 TEST_CASE("TESTE 4 adiconarModo - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );
   auto modo = DummyModo();
   comodoTeste.adicionarModo(&modo);
   CHECK(comodoTeste.getModos().size() == 1);
      SUBCASE("TESTE 4.1 Modos iguais adicionados"){
         auto modo = DummyModo();
         comodoTeste.adicionarModo(&modo);
         CHECK(comodoTeste.getModos().size() == 1);
         comodoTeste.adicionarModo(&modo);
         CHECK(comodoTeste.getModos().size() == 1);
      }
      SUBCASE("TESTE 4.2modo vazio adicionado"){
         CHECK_THROWS(comodoTeste.adicionarModo(nullptr));
      }
}

    //void entrarConta(Conta* conta); Conta * getContaPresente();
 TEST_CASE("TESTE 5 entrarConta - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );
   comodoTeste.entrarConta(&contaTeste);
   CHECK(comodoTeste.getContasPresentes().size() == 1);
   CHECK(comodoTeste.getContasPresentes()[0]->getNome() == "Usuario A");
      SUBCASE("TESTE 5.1 mais de uma conta no mesmo comodo"){
         std :: string id2 = "2";
         Conta contaTeste2(id2, "Usuario B", "usuarioB@email.com", "senha456", true);
         comodoTeste.entrarConta(&contaTeste2);
         CHECK(comodoTeste.getContasPresentes().size() == 2);
         CHECK(comodoTeste.getContasPresentes()[0]->getNome() == "Usuario A");
         CHECK(comodoTeste.getContasPresentes()[1]->getNome() == "Usuario B");
      }
      SUBCASE("TESTE 5.2ponteiro da conta eh nullptr"){
         CHECK_THROWS(comodoTeste.entrarConta(nullptr));
      }
}
    //void sairConta();
 TEST_CASE("TESTE 6 sairConta - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );
   comodoTeste.entrarConta(&contaTeste);

   CHECK(comodoTeste.getContasPresentes().size() == 1);
   CHECK(comodoTeste.getContasPresentes()[0]->getNome() == "Usuario A");
   comodoTeste.sairConta();
   CHECK(comodoTeste.getContasPresentes().size() == 0);


      SUBCASE("TESTE 6.1 comodo com duas contas (quero sair so de uma)"){
         std :: string id2 = "2";
         Conta contaTeste2(id2, "Usuario B", "usuarioB@email.com", "senha456", true);
         comodoTeste.entrarConta(&contaTeste2);
         CHECK(comodoTeste.getContasPresentes().size() == 2);
         comodoTeste.sairConta();
         CHECK(comodoTeste.getContasPresentes().size() == 1);
         
         SUBCASE("TESTE 6.2 sair de todas as contas"){
            Conta contaTeste2(id2, "Usuario B", "usuarioB@email.com", "senha456", true);
            comodoTeste.entrarConta(&contaTeste2);
            CHECK(comodoTeste.getContasPresentes().size() == 2);
            comodoTeste.sairConta();
            CHECK(comodoTeste.getContasPresentes().size() == 1);  
            comodoTeste.sairConta();
            CHECK(comodoTeste.getContasPresentes().size() == 0);
         }
      }

      SUBCASE("TESTE 6.3 sair de conta inexistente"){
         std :: string idf = "x";
         Conta contaFalsa(idf, "Usuario F", "usuarioF@email.com", "senha", true);
         comodoTeste.entrarConta(&contaFalsa);
         CHECK(comodoTeste.getContasPresentes().size() == 0);
         CHECK_THROWS(comodoTeste.sairConta());
      }
}

    //void repassarInstrucao(Modo* modo);
 TEST_CASE("TESTE 7 repassarInstrucao - Comodo"){
   std::string id = "1";
   Conta contaTeste(id, "Usuario A", "usuarioA@email.com", "senha123", true);
   Smarthome smarthome(contaTeste, "Minha Casa");
   Comodo comodoTeste ("comodoTeste", &smarthome );
   auto lampada = DummyObjeto();
   auto tv = DummyObjeto();
   comodoTeste.adicionarObjeto(&lampada);
   comodoTeste.adicionarObjeto(&tv);
   std::vector<ObjetoInteligente> objetos = {lampada, tv};
   std::vector<Comodo> comodos = {comodoTeste};
   Modo modoNoite (objetos, comodos, true, false);
   comodoTeste.adicionarModo(&modoNoite);
   comodoTeste.repassarInstrucao(&modoNoite);
   CHECK(comodoTeste.getObjetos()[0]->getStatus() == "off" );
   CHECK(comodoTeste.getObjetos()[1]->getStatus() == "off" );
   
   SUBCASE("modo nullptr"){
      CHECK_THROWS(comodoTeste.repassarInstrucao(nullptr));
   }
   SUBCASE("TESTE 7.1 comodo sem objetos afetados pelo modo"){
      std::vector<ObjetoInteligente> objetos = {};
      Modo modoNaoRelacionado (objetos, comodos, true, false);
      comodoTeste.adicionarModo(&modoNaoRelacionado);
      comodoTeste.repassarInstrucao(&modoNaoRelacionado);
      CHECK_THROWS(comodoTeste.getObjetos()[0]->getStatus());
   }
   SUBCASE("TESTE 7.2 modo desligado"){
      comodoTeste.adicionarModo(&modoNoite);
      modoNoite.setAtivoModo(false);
      comodoTeste.repassarInstrucao(&modoNoite);
      CHECK(comodoTeste.getObjetos()[0]->getStatus() == "on" );
      CHECK(comodoTeste.getObjetos()[1]->getStatus() == "on" );
   }
   SUBCASE("TESTE 7.3 modo bloqueado"){
      comodoTeste.adicionarModo(&modoNoite);
      modoNoite.setBloqueadoModo(true);
      CHECK_THROWS(comodoTeste.repassarInstrucao(&modoNoite));
   }
  }

                