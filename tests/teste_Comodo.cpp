#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <string>
#include <vector>
#include <functional>

#include "Comodo.hpp"
#include "ObjetoInteligente.hpp"
#include "Smarthome.hpp"
#include "Sensor.hpp"
#include "Modo.hpp"
#include "Conta.hpp"

static ObjetoInteligente DummyObjetoComodo() {
    std::vector<Sensor*> sensores;
    std::vector<std::string> status = {"on", "off"};
    float consumo = 5.0f;
    std::vector<std::function<void()>> funcoes = {[]{}};
    std::vector<std::function<void()>> funcoesRestritas = {[]{}};

    return ObjetoInteligente
        ("ObjetoTeste", false, sensores, status, "on", consumo, funcoes, funcoesRestritas);
}

static Modo DummyModoComodo() {

    std::vector<ObjetoInteligente*> objetos;
    std::vector<Comodo*> comodos;

    return Modo("ModoTeste", objetos, comodos, true, false);
}

TEST_CASE("TESTE 1 construtor - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    CHECK(comodoTeste.getNome() == "comodoTeste");
    CHECK(comodoTeste.getSmarthome() == &smarthome);

    SUBCASE("TESTE 1.1 nome nao pode ser vazio") {
        CHECK_THROWS(Comodo("", &smarthome)); 
    }

    SUBCASE("TESTE 1.2 ponteiro smarthome nao pode ser nullptr") {
        CHECK_THROWS (Comodo("comodoTeste", nullptr));
    }

    SUBCASE("TESTE 1.3 nome nao pode ter tamanho maior que 20") {
        std::string longName(22, 'A');
        
        CHECK_THROWS(Comodo (longName, &smarthome));
    }

    SUBCASE("TESE 1.4 caracteres invalidos"){
        CHECK_THROWS(Comodo("Comodo@", &smarthome));
    }
}

TEST_CASE("TESTE 2 adicionarObjeto - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto obj = DummyObjetoComodo();

    comodoTeste.adicionarObjeto(&obj);

    CHECK(comodoTeste.getObjetos().size() == 1);

    SUBCASE("TESTE 2.1 ponteiro nullptr nao adiciona") {
        CHECK_THROWS_WITH(comodoTeste.adicionarObjeto(nullptr),
        "Tentativa de adicionar objeto nulo ao Comodo comodoTeste");
        CHECK(comodoTeste.getObjetos().size() == 1);
    }

    SUBCASE("TESTE 2.2 objeto repetido nao duplica") {

    CHECK_THROWS_WITH(comodoTeste.adicionarObjeto(&obj),
        "Objeto ObjetoTeste ja existe no Comodo comodoTeste");

    std::vector<Sensor*> sensores;
    std::vector<std::string> status = {"on", "off"};
    float consumoAlt = 10.0f;
    std::vector<std::function<void()>> funcoes = {[]{}};
    std::vector<std::function<void()>> funcoesRestritas = {[]{}};

    ObjetoInteligente objClone2("ObjetoTeste", false, sensores, status, "on", consumoAlt, funcoes, funcoesRestritas);
    
    CHECK_THROWS_WITH(comodoTeste.adicionarObjeto(&objClone2),
        "Objeto ObjetoTeste ja existe no Comodo comodoTeste");

    CHECK(comodoTeste.getObjetos().size() == 1);
    }
}

TEST_CASE("TESTE 3 adicionarSensor - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto sensor = std::make_unique<Sensor>(
        "SensorTeste", true, true, &comodoTeste, std::vector<ObjetoInteligente*>(), std::vector<Modo*>());

    comodoTeste.adicionarSensor(std::move(sensor));

    CHECK(comodoTeste.getSensores().size() == 1);

    SUBCASE("TESTE 3.1 ponteiro nullptr nao adiciona") {
        CHECK_THROWS_WITH(comodoTeste.adicionarSensor(nullptr),
        "Tentativa de adicionar sensor nulo ao Comodo comodoTeste");
        CHECK(comodoTeste.getSensores().size() == 1);
    }

    SUBCASE("TESTE 3.2 sensor repetido nao duplica") {
        auto sensorClone1 = std::make_unique<Sensor>(
        "SensorTeste", true, true, &comodoTeste, std::vector<ObjetoInteligente*>(), std::vector<Modo*>());
        CHECK_THROWS_WITH(comodoTeste.adicionarSensor(std::move(sensorClone1)),
        "Sensor SensorTeste ja existe no Comodo comodoTeste");// mesmo tudo

         auto sensorClone2 = std::make_unique<Sensor>(
        "SensorTeste", false, true, &comodoTeste, std::vector<ObjetoInteligente*>(), std::vector<Modo*>());

        CHECK_THROWS_WITH(comodoTeste.adicionarSensor(std::move(sensorClone2)),
        "Sensor SensorTeste ja existe no Comodo comodoTeste");// mesmo nome outro conteudo

        CHECK(comodoTeste.getSensores().size() == 1);
    }
}

TEST_CASE("TESTE 4 adicionarModo - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto modo = DummyModoComodo();

    comodoTeste.adicionarModo(&modo);

    CHECK(comodoTeste.getModos().size() == 1);

    SUBCASE("TESTE 4.1 modo repetido nao duplica") {
        CHECK_THROWS_WITH(comodoTeste.adicionarModo(&modo),
        "Modo ModoTeste ja existe no Comodo comodoTeste");

        std::vector<Comodo*> comodos;
        std::vector<ObjetoInteligente*> objetosAlt;

        auto modo3 =
        Modo("ModoTeste", objetosAlt, comodos, true, false);

        CHECK_THROWS_WITH(comodoTeste.adicionarModo(&modo3),
        "Modo ModoTeste ja existe no Comodo comodoTeste");

        CHECK(comodoTeste.getModos().size() == 1);

    }

    SUBCASE("TESTE 4.2 modo nullptr nao adiciona") {
        CHECK_THROWS_WITH(comodoTeste.adicionarModo(nullptr),
        "Tentativa de adicionar modo nulo ao Comodo comodoTeste");


        CHECK(comodoTeste.getModos().size() == 1);
    }
}

TEST_CASE("TESTE 5 entrarConta - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    comodoTeste.entrarConta(&contaTeste);

    CHECK(comodoTeste.getContasPresentes().size() == 1);

    SUBCASE("TESTE 5.1 mais de uma conta") {
        Conta contaTeste2("2", "Usuario B", "usuarioB@email.com", "senha456", true);
        comodoTeste.entrarConta(&contaTeste2);
        CHECK(comodoTeste.getContasPresentes().size() == 2);
    }

    SUBCASE("TESTE 5.2 conta nullptr nao adiciona") {
        CHECK_THROWS_WITH(comodoTeste.entrarConta(nullptr),
        "Tentativa de adicionar conta nula ao Comodo comodoTeste");
        CHECK(comodoTeste.getContasPresentes().size() == 1);
    }

    SUBCASE("TESTE 5.3 conta nao pode entrar duas vezes"){
        Conta contaTeste2("1", "Usuario A", "usuarioA@email.com", "senha123", true);

        CHECK_THROWS_WITH(comodoTeste.entrarConta(&contaTeste2),
        "Conta Usuario A ja existe no Comodo comodoTeste");

        CHECK(comodoTeste.getContasPresentes().size() == 1);
    }
}

TEST_CASE("TESTE 6 sairConta - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Conta contaTeste2("2", "Usuario B", "usuariob@email.com", "senha1234", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);
    comodoTeste.entrarConta(&contaTeste);
    comodoTeste.entrarConta(&contaTeste2);

    CHECK(comodoTeste.getContasPresentes().size() == 2);
    CHECK(comodoTeste.getContasPresentes().front() == &contaTeste);

    comodoTeste.sairConta();
    CHECK(comodoTeste.getContasPresentes().size() == 1);
    CHECK(comodoTeste.getContasPresentes().front() == &contaTeste2);
    comodoTeste.sairConta();
    CHECK(comodoTeste.getContasPresentes().empty());

    SUBCASE("TESTE 6.1 sair sem conta nao quebra") {
        CHECK_THROWS_WITH(comodoTeste.sairConta(),
        "Nenhuma conta presente no Comodo comodoTeste para sair");
        CHECK(comodoTeste.getContasPresentes().empty());
    }
}

TEST_CASE("TESTE 7 removerObjetoPorNome - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto obj = DummyObjetoComodo();

    comodoTeste.adicionarObjeto(&obj);
    CHECK(comodoTeste.getObjetos().size() == 1);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.removerObjetoPorNome("ObjetoTeste");

    std::cout.rdbuf(oldCout);
    CHECK(comodoTeste.getObjetos().size() == 0);
    CHECK(oss.str()== "Objeto ObjetoTeste removido do Comodo comodoTeste\n");
    
    SUBCASE("TESTE 7.1 tenta remover objeto nao adicionado"){
        CHECK_THROWS_WITH(comodoTeste.removerObjetoPorNome("ObjetoTeste2"),
        "Objeto ObjetoTeste2 nao encontrado no Comodo comodoTeste");
    }
}


TEST_CASE("TESTE 8 printObjetosInfo - Comodo"){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto obj = DummyObjetoComodo();

    comodoTeste.adicionarObjeto(&obj);

   
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    
    comodoTeste.printObjetosInfo();
    

    std::cout.rdbuf(oldCout);

    std::istringstream iss(oss.str());
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(iss, linha)) {
        linhas.push_back(linha);
    }

    CHECK(linhas[0] == "Comodo comodoTeste :");
    CHECK(linhas[1] == "Objetos inteligentes presentes em comodoTeste :");
    CHECK(linhas[2] == "Objeto ObjetoTeste");
    CHECK(linhas[3] == "Objeto tem restrição parental? Nao");
    CHECK(linhas[4] == "Consumo médio de energia: 5.0");
    CHECK(linhas[5] == "Protocolo: WiFi");
    CHECK(linhas[6] == "Em falha? Nao");
    CHECK(linhas[7] == "Sensores conectados: ");
    CHECK(linhas[8] == "Status possíveis: on off ");
    CHECK(linhas[9] == "Status atual: on");


    SUBCASE("TESTE 8.1 comodo sem objetos nao imprime nada "){
        Comodo comodoTeste2("comodoTeste2", &smarthome);
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        comodoTeste2.printObjetosInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str()== 
        "Comodo comodoTeste2 :\n"
        "Objetos inteligentes presentes em comodoTeste2 :\n");
    }

}
TEST_CASE("TESTE 9 printModosInfo - Comodo" ){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto modo = DummyModoComodo();

    comodoTeste.adicionarModo(&modo);

    // Captura a saída do cout
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.printModosInfo();

    // Restaura cout
    std::cout.rdbuf(oldCout);

    std::cout.rdbuf(oldCout);

    std::istringstream iss(oss.str());
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(iss, linha)) {
        linhas.push_back(linha);
    }
    
    CHECK(linhas[0] == "Comodo comodoTeste :");
    CHECK(linhas[1] == "Modos presentes em comodoTeste :");
    CHECK(linhas[2] == "Nome do modo: ModoTeste");
    CHECK(linhas[3] == "Estado: Ligado");
    CHECK(linhas[4] == "Bloqueio: Desbloqueado");
    CHECK(linhas[5] == "Objetos relacionados: 0");
    CHECK(linhas[6] == "Comodos relacionados: 0");
    
    SUBCASE("TESTE 9.1 comodo sem modos nao imprime nada "){
        Comodo comodoTeste2("comodoTeste2", &smarthome);
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        comodoTeste2.printModosInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str()==
        "Comodo comodoTeste2 :\n"
        "Modos presentes em comodoTeste2 :\n");
    }

}

TEST_CASE("TESTE 10 printContasInfo - Comodo"){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    comodoTeste.entrarConta(&contaTeste);
    // Captura a saída do cout
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.printContasInfo();

    // Restaura cout
    std::cout.rdbuf(oldCout);

    CHECK(oss.str() == 
        "Comodo comodoTeste :\n"
        "Contas presentes em comodoTeste :\n"
        "ID: 1\nNome: Usuario A\nE-mail: usuarioA@email.com\nPerfil: Adulto\n\n"
    );
    SUBCASE("TESTE 10.1 comodo sem contas nao imprime nada "){
        Comodo comodoTeste2("comodoTeste2", &smarthome);
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        comodoTeste2.printContasInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str()==
        "Comodo comodoTeste2 :\n"
        "Contas presentes em comodoTeste2 :\n");
    }
}

TEST_CASE("TESTE 11 printSensoresInfo - Comodo"){
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);
    

    auto sensor = std::make_unique<Sensor>(
        "SensorTeste", true, true, &comodoTeste, std::vector<ObjetoInteligente*>(), std::vector<Modo*>());

    comodoTeste.adicionarSensor(std::move(sensor));

     // Captura a saída do cout
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.printSensoresInfo();
   
    // Restaura cout
    std::cout.rdbuf(oldCout);

    std::istringstream iss(oss.str());
    std::vector<std::string> linhas;
    std::string linha;
    while (std::getline(iss, linha)) {
        linhas.push_back(linha);
    }
    
    CHECK(linhas[0] == "Comodo comodoTeste :");
    CHECK(linhas[1] == "Sensores presentes em comodoTeste :");
    CHECK(linhas[2] == "Sensor SensorTeste do cômodo comodoTeste");
    CHECK(linhas[3] == "Sensor está ligado? Sim");
    CHECK(linhas[4] == "Sensor está ativado? Sim");
    CHECK(linhas[5] == "Objetos conectados: ");
    CHECK(linhas[6] == "Modos conectados: "); 

    SUBCASE("TESTE 11.1 comodo sem sensores nao imprime nada "){
        Comodo comodoTeste2("comodoTeste2", &smarthome);
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        comodoTeste2.printSensoresInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str() == 
        "Comodo comodoTeste2 :\n"
        "Sensores presentes em comodoTeste2 :\n");
    }

}

// ---- implementação deve ser checada -----

TEST_CASE("TESTE 12 repassarInstrucao - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo quarto("Quarto", &smarthome);

    auto luz = std::make_shared<ObjetoInteligente>(
    "Luz",
    false,
    std::vector<Sensor*>(),                          
    std::vector<std::string>{"Ligado","Desligado"},  
    "Ligado",                                        
    10.0f,                                           
    std::vector<std::function<void()>>(),            
    std::vector<std::function<void()>>()             
    );

    auto abajur = std::make_shared<ObjetoInteligente>(
    "Abajur",
    false,
    std::vector<Sensor*>(),
    std::vector<std::string>{"Ligado","Desligado"},
    "Desligado",
    5.0f,
    std::vector<std::function<void()>>(),
    std::vector<std::function<void()>>()
    );

    auto tv = std::make_shared<ObjetoInteligente>(
    "TV",
    false,
    std::vector<Sensor*>(),
    std::vector<std::string>{"Ligado","Desligado"},
    "Desligado",
    50.0f,
    std::vector<std::function<void()>>(),
    std::vector<std::function<void()>>()
    );

    quarto.adicionarObjeto(luz.get());
    quarto.adicionarObjeto(abajur.get());
    quarto.adicionarObjeto(tv.get());

    ModoNoturno dormir("Dormir");
    dormir = ModoNoturno("Dormir");

    quarto.entrarConta(&contaTeste);

    quarto.repassarInstrucao(&dormir);

    CHECK(luz->getStatusAtual() == "Desligado");
    CHECK(abajur->getStatusAtual() == "Desligado");
    CHECK(tv->getStatusAtual() == "Desligado");

    SUBCASE("TESTE 12.1 comodo com modo inativo nao passa instrucao"){
        Modo dormirInativo("Dormir", {luz.get()}, {&quarto}, false, false);
        quarto.repassarInstrucao(&dormirInativo);
        quarto.repassarInstrucao(&dormir);

        CHECK(luz->getStatusAtual() == "Ligado"); 
    }
    
    SUBCASE("TESTE 12.2 comodo sem conta presente nao passa instrucao"){
        Conta contaTeste2("2", "Usuario B", "usuarioB@email.com", "senha456", true);
        Smarthome smarthome2(&contaTeste2, "Minha Casa");
        Comodo quarto2("Quarto", &smarthome2);

        auto lampada = std::make_shared<ObjetoInteligente>(
            "Lampada", false,
            std::vector<Sensor*>(),
            std::vector<std::string>{"Ligado","Desligado"},
            "Ligado",
            15.0f,
            std::vector<std::function<void()>>(),
            std::vector<std::function<void()>>()
        );

        quarto2.adicionarObjeto(lampada.get());

        Modo dormir2("Dormir", {lampada.get()}, {&quarto2}, true, false);

        // Não chama entrarConta → cômodo vazio
        quarto2.repassarInstrucao(&dormir2);

        CHECK(lampada->getStatusAtual() == "Ligado"); // não mudou
        
    }
    SUBCASE("TESTE 12.3 modo nullptr lança excecao") {

    CHECK_THROWS_WITH(quarto.repassarInstrucao(nullptr),
        "Modo invalido (nullptr) ao repassar instrucao no Comodo Quarto");
    }

}

TEST_CASE("TESTE 13 removerModoPorNome - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);

    auto modo = DummyModoComodo();

    comodoTeste.adicionarModo(&modo);
    CHECK(comodoTeste.getModos().size() == 1);
    
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.removerModoPorNome("ModoTeste");
    CHECK(comodoTeste.getModos().size() == 0);
    
    std::cout.rdbuf(oldCout);
    
    CHECK (oss.str() == "Modo ModoTeste removido do Comodo comodoTeste\n");
    SUBCASE("TESTE 13.1 tenta remover modo nao adicionado"){

        CHECK_THROWS_WITH(comodoTeste.removerModoPorNome("ModoTeste2"),
          "Modo ModoTeste2 nao encontrado no Comodo comodoTeste");

        
    }
}
TEST_CASE("TESTE 14 removerSensorPorNome - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo comodoTeste("comodoTeste", &smarthome);


    auto sensor = std::make_unique<Sensor>(
        "SensorTeste", true, true, &comodoTeste, std::vector<ObjetoInteligente*>(), std::vector<Modo*>());

    comodoTeste.adicionarSensor(std::move(sensor));
    CHECK(comodoTeste.getSensores().size() == 1);

    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.removerSensorPorNome("SensorTeste");
    CHECK(comodoTeste.getSensores().size() == 0);

    std::cout.rdbuf(oldCout);

    CHECK (oss.str() == "Sensor SensorTeste removido do Comodo comodoTeste\n");
    
    SUBCASE("TESTE 14.1 tenta remover sensor nao adicionado"){

        CHECK_THROWS_WITH(comodoTeste.removerSensorPorNome("SensorTeste2"),
        "Sensor SensorTeste2 nao encontrado no Comodo comodoTeste");
       
    }
}

// ---- implementação deve ser checada-----

TEST_CASE("TESTE 15 mudarCondicao - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo quarto("Quarto", &smarthome);

    SUBCASE("TESTE 15.1 Adicionar primeira condição") {
        quarto.mudarCondicao("Iluminado");
        auto condicoes = quarto.getCondicoesDoComodo();
        CHECK(condicoes.size() == 1);
        CHECK(condicoes[0] == "Iluminado");
    }

    SUBCASE("TESTE 15.2 Trocar condição exclusiva (Iluminado -> Escuro)") {
        quarto.mudarCondicao("Iluminado");
        quarto.mudarCondicao("Escuro");
        auto condicoes = quarto.getCondicoesDoComodo();
        CHECK(condicoes.size() == 1);
        CHECK(condicoes[0] == "Escuro");
    }

    SUBCASE("TESTE 15.3 Adicionar múltiplas condições não exclusivas") {
        quarto.mudarCondicao("Quente");
        quarto.mudarCondicao("Barulhento");
        auto condicoes = quarto.getCondicoesDoComodo();
        CHECK(condicoes.size() == 2);
        CHECK(std::find(condicoes.begin(), condicoes.end(), "Quente") != condicoes.end());
        CHECK(std::find(condicoes.begin(), condicoes.end(), "Barulhento") != condicoes.end());
    }

    SUBCASE("TESTE 15.4 Trocar condição exclusiva (Quente -> Frio)") {
        quarto.mudarCondicao("Quente");
        quarto.mudarCondicao("Frio");
        auto condicoes = quarto.getCondicoesDoComodo();
        CHECK(condicoes.size() == 1);
        CHECK(condicoes[0] == "Frio");
    }

    SUBCASE("TESTE 15.5 Condição inválida") {
        CHECK_THROWS_WITH(quarto.mudarCondicao("Claro"),
        "Condicao invalida: Claro");
    }

    SUBCASE("TESTE 15.6 Repetição da mesma condição") {
        quarto.mudarCondicao("Iluminado");
        quarto.mudarCondicao("Iluminado");
        auto condicoes = quarto.getCondicoesDoComodo();
        CHECK(condicoes.size() == 1); // não deve duplicar
        CHECK(condicoes[0] == "Iluminado");
    }
}

