# PDS2-2026-PF-grupo2 - Smart Home

Este projeto consiste na modelagem e desenvolvimento de um sistema de automação residencial inteligente (Smart Home). O software permite o gerenciamento centralizado de dispositivos, perfis de usuários com controle parental e monitoramento de eficiência energética. 

---

## Membros do Grupo 2
* **Aline Sayuri Hamawaki Kawamura** - 2025430854
* **Hamlah Alves de Vasconcelos Dip** - 2025019267
* **Maria Paula Barbosa Vartuli** - 2025019356
* **Tiago Ladeira Alkmim Bizzotto** - 2025019445

---

## Descrição do Problema e Contextualização

O projeto aborda a dificuldade de gerenciar múltiplos dispositivos inteligentes, focando em resolver a falta de controle centralizado sobre a segurança infantil, o monitoramento de gastos energéticos e a organização física dos aparelhos por cômodos. Em suma, o objetivo é unificar o controle da Smart Home para tornar a interação tecnológica mais segura e organizada.

### Motivação

O projeto nasce do desejo de simplificar a relação entre as pessoas e a tecnologia, transformando a automação em uma ferramenta de proteção e clareza para o dia a dia. A casa inteligente deve ser um ambiente onde o morador detém o controle total sobre a segurança e os gastos. 

O desenvolvimento deste sistema é impulsionado pelo desafio de resolver problemas cotidianos mapeados em nossas *User Stories*, de modo que o sistema permite o gerenciamento centralizado de dispositivos, perfis de usuários com controle parental e monitoramento de eficiência energética. 

## Funcionalidades/Objetivos Principais

1.  **Gestão de Perfis e Segurança**: Criação de contas com validação e sistema de login.
2.  **Controle Parental**: Restrição de funcionalidades de dispositivos baseada na classificação do perfil (Adulto vs. Infantil).
3.  **Organização Espacial**: Gerenciamento de dispositivos por cômodos para facilitar a interação do usuário.
4.  **Automação Inteligente**: Uso de sensores e modos pré-definidos para otimizar o funcionamento da residência.
5.  **Monitoramento Energético**: Visualização em forma de relatórios do consumo elétrico da casa.

---

## Estrutura Técnica e Contratos (C++)

### Arquivos de Cabeçalho - Contratos (.hpp)
* Conta.hpp;
* Login.hpp;
* ObjetoInteligente.hpp;
* Smarthome.hpp;
* Comodo.hpp;
* Sensor.hpp;
* Modo.hpp;

---

## Organização do Repositório
```text
├── include/           # Arquivos de cabeçalho (.hpp)
├── src/               # Implementações (.cpp)
├── docs/              # PDFs com Cartões CRC e documentação de design
└── README.md          # Documentação principal