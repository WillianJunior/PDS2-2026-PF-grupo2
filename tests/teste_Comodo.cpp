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

    return ObjetoInteligente("ObjetoTeste", false, sensores, status, "on", consumo, funcoes, funcoesRestritas);
}

static std:: unique_ptr <Sensor> DummySensorComodo() {
    std::vector<ObjetoInteligente*> objetosConectados;
    std::vector<Modo*> modosConectados;
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthomeDummy(&contaTeste, "MinhaCasa");
    Comodo comodoDummy("SalaTeste", &smarthomeDummy);
    return std:: make_unique <Sensor>("SensorTeste", true, true, &comodoDummy, objetosConectados, modosConectados);
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

    comodoTeste.adicionarSensor(DummySensorComodo()); 

    CHECK(comodoTeste.getSensores().size() == 1);

    SUBCASE("TESTE 3.1 ponteiro nullptr nao adiciona") {
        CHECK_THROWS_WITH(comodoTeste.adicionarSensor(nullptr),
        "Tentativa de adicionar sensor nulo ao Comodo comodoTeste");
        CHECK(comodoTeste.getSensores().size() == 1);
    }

    SUBCASE("TESTE 3.2 sensor repetido nao duplica") {
        CHECK_THROWS_WITH(comodoTeste.adicionarSensor(DummySensorComodo()),
        "Sensor SensorTeste ja existe no Comodo comodoTeste");// mesmo tudo
        
        std::vector<ObjetoInteligente*> objetosConectados;
        std::vector<Modo*> modosConectadosAlt;
        Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
        Smarthome smarthomeDummy(&contaTeste, "MinhaCasa");
        Comodo comodoDummy("SalaTeste", &smarthomeDummy);

        CHECK_THROWS_WITH(comodoTeste.adicionarSensor(std:: make_unique <Sensor>
            ("SensorTeste", true, true, &comodoDummy, objetosConectados, modosConectadosAlt)),
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

    // Captura a saída do cout
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    
    comodoTeste.printObjetosInfo();
    
     // Restaura cout
    std::cout.rdbuf(oldCout);

    CHECK(oss.str() == 
        "Comodo comodoTeste :\n"
        "Objetos inteligentes presentes em comodoTeste :\n"
        "Objeto ObjetoTeste\n"
        "Objeto tem restrição parental? Nao\n"
        "Consumo médio de energia: 5.0\n"
        "Protocolo: WiFi\n"
        "Em falha? Nao\n"
        "Sensores conectados:"
        "\nStatus possíveis: on off "
        "\nStatus atual: on\n");

        SUBCASE("DEBUG"){
            auto normalize = [](std::string s) {
    // remove carriage returns
    s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
    // remove espaços no fim das linhas
    std::string result;
    std::istringstream iss(s);
    std::string line;
    while (std::getline(iss, line)) {
        while (!line.empty() && line.back() == ' ')
            line.pop_back();
        result += line + "\n";
    }
    return result;
};

CHECK(normalize(oss.str()) == normalize(
    "Comodo comodoTeste :\n"
        "Objetos inteligentes presentes em comodoTeste :\n"
        "Objeto ObjetoTeste\n"
        "Objeto tem restrição parental? Nao\n"
        "Consumo médio de energia: 5.0\n"
        "Protocolo: WiFi\n"
        "Em falha? Nao\n"
        "Sensores conectados:"
        "\nStatus possíveis: on off "
        "\nStatus atual: on\n"));

        }

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

    CHECK(oss.str() == 
        "Comodo comodoTeste :\n"
        "Modos presentes em comodoTeste :\n"
        "Nome do modo: ModoTeste\n"
        "Estado: Ligado\n"
        "Bloqueio: Desbloqueado\n"
        "Objetos relacionados: 0\n"
        "Comodos relacionados: 0\n"
    );
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
    

    comodoTeste.adicionarSensor(DummySensorComodo());

     // Captura a saída do cout
    std::ostringstream oss;
    std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

    comodoTeste.printSensoresInfo();
   
    // Restaura cout
    std::cout.rdbuf(oldCout);

    CHECK(oss.str() == 
        "Comodo comodoTeste :\n"
        "Sensores presentes em comodoTeste :\n"
        "Sensor SensorTeste do cômodo SalaTeste\n"
        "Sensor está ligado? true\n"
        "Sensor está ativado? true\n"
        "Objetos conectados: \n"
        "Modos conectados: \n"
        ); 
    SUBCASE("TESTE 11.1 comodo sem sensores nao imprime nada "){
        Comodo comodoTeste2("comodoTeste2", &smarthome);
         // Captura a saída do cout
        std::ostringstream oss;
        std::streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());

        comodoTeste2.printModosInfo();

        // Restaura cout
        std::cout.rdbuf(oldCout);

        CHECK(oss.str().empty());
    }

}

// ---- implementação deve ser checada -----

TEST_CASE("TESTE 12 repassarInstrucao - Comodo") {
    Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
    Smarthome smarthome(&contaTeste, "Minha Casa");
    Comodo quarto("Quarto", &smarthome);
//troca para smart pointers
    ObjetoInteligente* luz = new ObjetoInteligente
        ("Luz", false, {}, {"Ligado","Desligado"}, "Ligado", 10.0, {}, {});
    ObjetoInteligente* abajur = new ObjetoInteligente
        ("Abajur", false, {}, {"Ligado","Desligado"}, "Desligado", 5.0, {}, {});
    ObjetoInteligente* tv = new ObjetoInteligente
        ("TV", false, {}, {"Ligado","Desligado"}, "Desligado", 50.0, {}, {});

    quarto.adicionarObjeto(luz);
    quarto.adicionarObjeto(abajur);
    quarto.adicionarObjeto(tv);

    Modo dormir("Dormir", {luz, abajur, tv}, {&quarto}, true, false);

    quarto.entrarConta(&contaTeste);

    quarto.repassarInstrucao(&dormir);

    CHECK(luz->getStatusAtual() == "Desligado");
    CHECK(abajur->getStatusAtual() == "Ligado");
    CHECK(tv->getStatusAtual() == "Ligado");

    delete luz;
    delete abajur;
    delete tv;

    SUBCASE("TESTE 12.1 comodo com modo inativo nao passa instrucao"){
        Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
        Smarthome smarthome(&contaTeste, "Minha Casa");
        Comodo quarto("Quarto", &smarthome);
    //troca para smart pointers
        ObjetoInteligente* luz = new ObjetoInteligente
            ("Luz", false, {}, {"Ligado","Desligado"}, "Ligado", 10.0, {}, {});

        quarto.adicionarObjeto(luz);

        Modo dormir("Dormir", {luz}, {&quarto}, false, false); // modo inativo

        quarto.entrarConta(&contaTeste);
        quarto.repassarInstrucao(&dormir);

        CHECK(luz->getStatusAtual() == "Ligado"); 
        CHECK_THROWS_WITH(quarto.repassarInstrucao(&dormir),
         "Modo invalido (nullptr) ao repassar instrucao no Comodo comodoTeste");

        delete luz;
    }
    
    SUBCASE("TESTE 12.2 comodo sem conta presente nao passa instrucao"){
        Conta contaTeste("1", "Usuario A", "usuarioA@email.com", "senha123", true);
        Smarthome smarthome(&contaTeste, "Minha Casa");
        Comodo quarto("Quarto", &smarthome);
        //troca para smart pointers
        ObjetoInteligente* luz = new ObjetoInteligente
            ("Luz", false, {}, {"Ligado","Desligado"}, "Ligado", 10.0, {}, {});

        quarto.adicionarObjeto(luz);

        Modo dormir("Dormir", {luz}, {&quarto}, true, false);

        // Não chama entrarConta → cômodo vazio
        quarto.repassarInstrucao(&dormir);

        CHECK(luz->getStatusAtual() == "Ligado"); // não mudou

        delete luz;
        
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


    comodoTeste.adicionarSensor(DummySensorComodo());
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
    Comodo quarto("Quarto", nullptr);

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
        //quarto.mudarCondicao("Claro"); // não está na lista de pares
        //auto condicoes = quarto.getCondicoesDoComodo();
        //CHECK(condicoes.size() == 1); // adiciona mesmo assim
        //CHECK(condicoes[0] == "Claro"); // mas não remove nada
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

