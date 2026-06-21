#include "Conta.hpp"
#include "Smarthome.hpp"
#include "Comodo.hpp"
#include "Modo.hpp"
#include "ObjetoInteligente.hpp"
#include "Sensor.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <cctype>

Conta::Conta(std::string id, std::string nome, std::string email, std::string senha, bool adulto)
    : senha(senha), perfilAdulto(adulto), bloqueada(false) {
    if(nome.empty() || email.empty() || id.empty() ){
        throw std::invalid_argument("Nome, Email, id da Conta nao podem ser vazios - Tente novamente...");
    } 
    else if (nome.size() > 20) {
        throw std::invalid_argument("Nome da Conta nao pode ter tamanho maior que 20  - Tente novamente..." );
    }
    else if(!CaracteresValidos(nome)) {
        throw std::invalid_argument("Nome da Conta com usos de caracteres invalidos  - Tente novamente..." );
    }
    else{
        this->nome = nome;
        this->email =email;
        this->id=id;
    }
}

std::string Conta::getId() const {
    return id;
}

std::string Conta::getNome() const {
    return nome;
}

std::string Conta::getEmail() const {
    return email;
}

bool Conta::isPerfilAdulto() const {
    return perfilAdulto;
}

bool Conta::estaBloqueada() const {
    return bloqueada;
}

void Conta::bloquear() {
    bloqueada = true;
}

void Conta::desbloquear() {
    bloqueada = false;
}

void Conta::criarSmarthome(std::string id, std::string nome) {
    (void)id;

    smarthomes.push_back(std::make_unique<Smarthome>(this, nome));
}

void Conta::apagarSmarthome(const Smarthome& smarthome) {
    for (auto it = smarthomes.begin(); it != smarthomes.end(); ++it) {
        if (**it == smarthome) {
            smarthomes.erase(it);
            break;
        }
    }
}

void Conta::criarComodo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        Comodo novoComodo(nome, smarthome);
        smarthome->adicionarComodo(novoComodo);
    }
}

void Conta::apagarComodo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        Comodo comodoRemover(nome, smarthome);
        smarthome->removerComodo(comodoRemover);
    }
}

void Conta::criarModo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        std::vector<ObjetoInteligente*> objetosVazios;
        std::vector<Comodo*> comodosVazios;
        Modo novoModo(nome, objetosVazios, comodosVazios, false, false);
        smarthome->adicionarModo(novoModo);
    }
}

void Conta::criarModoPorTipo(Smarthome* smarthome, std::string nome, int tipoModo) {
    if (smarthome == nullptr) {
        throw std::invalid_argument("Smarthome invalida ao criar modo");
    }

    switch (tipoModo) {
        case 1: {
            std::vector<ObjetoInteligente*> objetosVazios;
            std::vector<Comodo*> comodosVazios;
            Modo modo(nome, objetosVazios, comodosVazios, false, false);
            smarthome->adicionarModo(modo);
            break;
        }

        case 2: {
            ModoCinema modo(nome);
            smarthome->adicionarModo(modo);
            break;
        }

        case 3: {
            ModoNoturno modo(nome);
            smarthome->adicionarModo(modo);
            break;
        }

        case 4: {
            ModoTrabalho modo(nome);
            smarthome->adicionarModo(modo);
            break;
        }

        case 5: {
            ModoAusente modo(nome);
            smarthome->adicionarModo(modo);
            break;
        }

        case 6: {
            ModoFesta modo(nome);
            smarthome->adicionarModo(modo);
            break;
        }

        default:
            throw std::invalid_argument("Tipo de modo invalido");
    }
}

void Conta::apagarModo(Smarthome* smarthome, std::string nome) {
    if (smarthome != nullptr) {
        smarthome->removerModo(nome); 
    }
}

void Conta::criarObjeto(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        std::vector<Sensor*> sensoresVazios;
        std::vector<std::string> statusPossiveis = {"Desligado", "Ligado"};
        std::vector<std::function<void()>> funcoes;
        std::vector<std::function<void()>> funcoesRestritas;

        ObjetoInteligente* novoObjeto = new ObjetoInteligente(
            nome, false, sensoresVazios, statusPossiveis, "Desligado", 0.0f, funcoes, funcoesRestritas
        );

        smarthome->adicionarObjeto(*novoObjeto);
        comodo->adicionarObjeto(novoObjeto);
    }
}

void Conta::criarObjetoPorTipo(Smarthome* smarthome, Comodo* comodo, std::string nome, int tipoObjeto) {
    if (smarthome == nullptr || comodo == nullptr) {
        throw std::invalid_argument("Smarthome ou Comodo invalido ao criar objeto");
    }

    ObjetoInteligente* novoObjeto = nullptr;

    switch (tipoObjeto) {
        case 1:
            novoObjeto = new Luz(nome);
            break;

        case 2:
            novoObjeto = new TV(nome);
            break;

        case 3:
            novoObjeto = new CaixaDeSom(nome);
            break;

        case 4:
            novoObjeto = new ArCondicionado(nome);
            break;

        case 5:
            novoObjeto = new Portao(nome);
            break;

        case 6:
            novoObjeto = new Termostato(nome);
            break;

        default:
            throw std::invalid_argument("Tipo de objeto invalido");
    }

    smarthome->adicionarObjeto(*novoObjeto);
    comodo->adicionarObjeto(novoObjeto);
}

void Conta::apagarObjeto(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        smarthome->removerObjeto(nome); 
        comodo->removerObjetoPorNome(nome); 
    }
}

void Conta::moverObjeto(Smarthome* smarthome, Comodo* atual, std::string nome, Comodo* destino) {
    if (smarthome != nullptr && atual != nullptr && destino != nullptr) {
        atual->removerObjetoPorNome(nome);
        std::cout << "Objeto " << nome << " removido do comodo atual." << std::endl;
    }
}

void Conta::criarSensor(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {

        auto novoSensor = std::make_unique<Sensor>(
            nome,
            false,
            false,
            comodo,
            std::vector<ObjetoInteligente*>{},
            std::vector<Modo*>{}
        );

        comodo->adicionarSensor(std::move(novoSensor));
    }
}

void Conta::apagarSensor(Smarthome* smarthome, Comodo* comodo, std::string nome) {
    if (smarthome != nullptr && comodo != nullptr) {
        comodo->removerSensorPorNome(nome); 
    }
}

void Conta::moverSensor(Smarthome* smarthome, Comodo* atual, std::string nome, Comodo* destino) {
    if (smarthome != nullptr && atual != nullptr && destino != nullptr) {
        atual->removerSensorPorNome(nome);
        std::cout << "Sensor " << nome << " removido do comodo atual." << std::endl;
    }
}

float Conta::gerarRelatorioDeEnergia(Smarthome* smarthome) {
    float total = 0.0f;
    if (smarthome != nullptr) {
        std::vector<ObjetoInteligente> objetosDaCasa = smarthome->getObjetos();
        for (size_t i = 0; i < objetosDaCasa.size(); ++i) {
            total += objetosDaCasa[i].getConsumoMedioDeEnergia();
        }
    }
    return total;
}

bool Conta::validarFormatoEmail() const {
    return email.find('@') != std::string::npos;
}

bool Conta::validarSenha() const {
    return senha.length() >= 8;
}

bool Conta::autenticar(const std::string& tentativaSenha) const {
    return senha == tentativaSenha;
}

bool Conta :: operator == (const Conta& other) const{
    return id == other.id && nome == other.nome &&
    email == other.email && senha == other.senha && perfilAdulto == other.perfilAdulto;
}

void Conta::printMembrosInfo() const {
    std::cout << "ID: " << id << "\nNome: " << nome << "\nE-mail: " << email 
              << "\nPerfil: " << (perfilAdulto ? "Adulto" : "Infantil") << std::endl;
}

const std::vector<std::unique_ptr<Smarthome>>& Conta::getSmarthomes() const {
    return smarthomes;
}

bool Conta :: CaracteresValidos (const std::string& str) {
    for (unsigned char ch : str) {
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}

std::string Conta::getSenha() const {
    return senha;
}

void Conta::salvarSmarthomesEmArquivo() const {
    // Será implementado ainda
}

void Conta::carregarSmarthomesDeArquivo() {
    // Será implementado ainda
}