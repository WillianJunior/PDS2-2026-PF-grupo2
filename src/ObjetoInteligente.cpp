#include "ObjetoInteligente.hpp"
#include <iostream>
#include <algorithm>
#include "Sensor.hpp"
#include <cctype>
#include <stdexcept>
#include <Comodo.hpp>

ObjetoInteligente::ObjetoInteligente(
    std::string nome,
    bool restricaoAdulto,
    std::vector<Sensor*> sensores,
    std::vector<std::string> statusPossiveis,
    std::string statusAtual,
    float consumoMedioDeEnergia,
    std::vector<std::function<void()>> funcoes,
    std::vector<std::function<void()>> funcoesRestritas
) :
    restricaoAdulto(restricaoAdulto),
    sensores(std::move(sensores)),
    statusPossiveis(std::move(statusPossiveis)),
    statusAtual(statusAtual),
    consumoMedioDeEnergia(consumoMedioDeEnergia),
    funcoes(std::move(funcoes)),
    funcoesRestritas(std::move(funcoesRestritas))
{
    if(nome.empty()){
        throw std::invalid_argument("Nome do Obejeto nao pode ser vazio - Tente novamente...");
    } 
    else if (nome.size() > 20) {
        throw std::invalid_argument("Nome do Objeto nao pode ter tamanho maior que 20 - Tente novamente...");
    }
    else if(!CaracteresValidos(nome)) {
        throw std::invalid_argument("Nome do Objeto com usos de caracteres invalidos - Tente novamente...");
    }
    else{
        this->nome = nome;
    }
}

std::string ObjetoInteligente::getNome() const {
    return nome;
}

bool ObjetoInteligente :: operator==(const ObjetoInteligente& other) const {
    return nome == other.nome &&
        restricaoAdulto == other.restricaoAdulto &&
        sensores == other.sensores &&
        statusPossiveis == other.statusPossiveis &&
        statusAtual == other.statusAtual &&
        consumoMedioDeEnergia == other.consumoMedioDeEnergia &&
        funcoes.size() == other.funcoes.size() &&
        funcoesRestritas.size() == other.funcoesRestritas.size();
}

void ObjetoInteligente::setRestricaoAdulto(bool restricao) {
    restricaoAdulto = restricao;
}

bool ObjetoInteligente::getRestricaoAdulto() const {
    return restricaoAdulto;
}

std::vector<Sensor*> ObjetoInteligente::getSensores() const {
    return sensores;
}

std::vector<std::string> ObjetoInteligente::getStatusPossiveis() const{
    if (!statusPossiveis.empty()) {
        return statusPossiveis;
    }
    return {};
}

std::string ObjetoInteligente::getStatusAtual() const {
    return statusAtual;
}

void ObjetoInteligente::setStatusAtual(std::string status) {
    if (emFalha) {
        throw std::runtime_error("Objeto " + nome + " esta em falha");
    }

    if (std::find(statusPossiveis.begin(), statusPossiveis.end(), status) == statusPossiveis.end()) {
        throw std::invalid_argument("Status invalido para este objeto");
    }

    statusAtual = status; 
}

float ObjetoInteligente::getConsumoMedioDeEnergia() const {
    return consumoMedioDeEnergia;
}

std::vector<std::function<void()>> ObjetoInteligente::getFuncoes() const{
    return funcoes;
}

std::vector<std::function<void()>> ObjetoInteligente::getFuncoesRestritas() const{
    return funcoesRestritas;
}

Protocolo ObjetoInteligente::getProtocolo() const {
    return protocolo;
}

void ObjetoInteligente::setProtocolo(Protocolo protocolo) {
    this->protocolo = protocolo;
}

bool ObjetoInteligente::comunicaCom(const ObjetoInteligente& outro) const {
    return protocolo == outro.protocolo;
}

std::string ObjetoInteligente::getProtocoloComoString() const {
    if (protocolo == Protocolo::WIFI) {
        return "WiFi";
    }

    if (protocolo == Protocolo::BLUETOOTH) {
        return "Bluetooth";
    }

    return "ZigBee";
}

void ObjetoInteligente::simularFalha() {
    emFalha = true;
}

void ObjetoInteligente::repararFalha() {
    emFalha = false;
}

bool ObjetoInteligente::estaEmFalha() const {
    return emFalha;
}

void ObjetoInteligente :: printObjetosInfo() const{
    std::cout << "Objeto " << this->nome << std::endl;
    std::cout << "Objeto tem restrição parental? " << this->restricaoAdulto << std::endl;
    std::cout << "Consumo médio de energia: " << this->consumoMedioDeEnergia << std::endl;
    std::cout << "Protocolo: " << getProtocoloComoString() << std::endl;
    std::cout << "Em falha? " << (emFalha ? "Sim" : "Nao") << std::endl;

    std::cout << "Sensores conectados: "; 
    for (size_t i = 0; i < sensores.size(); i++) {
        if (sensores.at(i) != nullptr) {
            std::cout << sensores.at(i)->getNome() << " ";
        }
    }
   
    std::cout << "\nStatus possíveis: "; 
    for (size_t i = 0; i < statusPossiveis.size(); i++) {
        std::cout << this->getStatusPossiveis().at(i) << " ";
    }

    std::cout << "\nStatus atual: " << this->statusAtual << std::endl;
}

// LUZ

Luz::Luz(std::string nome)
    : ObjetoInteligente(
        nome,
        false,
        {},
        {"acesa", "apagada"},
        "apagada",
        10.0f,
        {},
        {}
    ) {}

void Luz::setStatusAtual(int indexStatus) {
    if (indexStatus == 0) {
        ObjetoInteligente::setStatusAtual("apagada");
    } else {
        ObjetoInteligente::setStatusAtual("acesa");
    }
}

// CAIXA DE SOM

CaixaDeSom::CaixaDeSom(std::string nome)
    : ObjetoInteligente(
        nome,
        true,
        {},
        {"desligada", "standby", "tocando música"},
        "desligada",
        35.0f,
        {},
        {}
    ) {
        protocolo = Protocolo::BLUETOOTH;
    }

void CaixaDeSom::setStatusAtual(int indexStatus) {
    if (indexStatus == 0) {
        ObjetoInteligente::setStatusAtual("desligada");
    } else if (indexStatus == 1) {
        ObjetoInteligente::setStatusAtual("standby");
    } else {
        ObjetoInteligente::setStatusAtual("tocando música");
    }
}

// TV

TV::TV(std::string nome)
    : ObjetoInteligente(
        nome,
        true,
        {},
        {"ligada", "desligada"},
        "desligada",
        80.0f,
        {},
        {}
    ) {
        protocolo = Protocolo::WIFI;
    }

void TV::ligar() {
    setStatusAtual("ligada");
}

void TV::desligar() {
    setStatusAtual("desligada");
}

// AR CONDICIONADO

ArCondicionado::ArCondicionado(std::string nome)
    : ObjetoInteligente(
        nome,
        true,
        {},
        {"desligado", "resfriando", "aquecendo"},
        "desligado",
        1500.0f,
        {},
        {}
    ),
    temperatura(24.0f) {
        protocolo = Protocolo::WIFI;
    }

void ArCondicionado::resfriar() {
    setStatusAtual("resfriando");
}

void ArCondicionado::aquecer() {
    setStatusAtual("aquecendo");
}

void ArCondicionado::desligar() {
    setStatusAtual("desligado");
}

void ArCondicionado::setTemperatura(float temperatura) {
    if (temperatura < 16.0f || temperatura > 30.0f) {
        throw std::invalid_argument("Temperatura do ar condicionado deve estar entre 16 e 30 graus");
    }

    this->temperatura = temperatura;
}

float ArCondicionado::getTemperatura() const {
    return temperatura;
}

// PORTAO

Portao::Portao(std::string nome)
    : ObjetoInteligente(
        nome,
        true,
        {},
        {"aberto", "fechado"},
        "fechado",
        50.0f,
        {},
        {}
    ) {
        protocolo = Protocolo::ZIGBEE;
    }

void Portao::abrir() {
    setStatusAtual("aberto");
}

void Portao::fechar() {
    setStatusAtual("fechado");
}

// TERMOSTATO

Termostato::Termostato(std::string nome)
    : ObjetoInteligente(
        nome,
        false,
        {},
        {"normal", "aquecendo", "resfriando"},
        "normal",
        5.0f,
        {},
        {}
    ),
    temperaturaAtual(25.0f) {
        protocolo = Protocolo::ZIGBEE;
    }

void Termostato::setTemperaturaAtual(float temperatura) {
    if (temperatura < -10.0f || temperatura > 60.0f) {
        throw std::invalid_argument("Temperatura medida pelo termostato fora do intervalo permitido");
    }

    temperaturaAtual = temperatura;
}

float Termostato::getTemperaturaAtual() const {
    return temperaturaAtual;
}

void Termostato::normalizar() {
    setStatusAtual("normal");
}

void Termostato::aquecer() {
    setStatusAtual("aquecendo");
}

void Termostato::resfriar() {
    setStatusAtual("resfriando");
}

bool ObjetoInteligente :: CaracteresValidos (const std::string& str) {
    for (unsigned char ch : str) {
        if (!(std::isalnum(ch) || std::isspace(ch))) {
            return false;
        }
    }
    return true;
}


bool ObjetoInteligente::getRestricaoAdulto() const {
    return restricaoAdulto;
}

