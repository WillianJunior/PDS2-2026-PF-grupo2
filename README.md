# PDS2-2026-PF-grupo2
# Smart Home - PDS II

![C++](https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![UFMG](https://img.shields.io/badge/UFMG-Engenharia_de_Sistemas-red?style=for-the-badge)

Este projeto consiste na modelagem e desenvolvimento de um sistema de automação residencial inteligente (Smart Home). O software permite o gerenciamento centralizado de dispositivos, perfis de usuários com controle parental e monitoramento de eficiência energética. Desenvolvido como projeto prático para a disciplina de **Programação e Desenvolvimento de Software II (PDS II)** da UFMG.

---

## 👥 Membros do Grupo 2
* **Aline Sayuri Hamawaki Kawamura** - 2025430854
* **Hamlah Alves de Vasconcelos Dip** - 2025019267
* **Maria Paula Barbosa Vartuli** - 2025019356
* **Tiago Ladeira Alkmim Bizzotto** - 2025019445

---

## 🎯 User Stories

### 1. Criação de Perfil (Conta)
* **História:** Como usuário, quero criar uma conta no sistema para que eu possa ter um ambiente seguro e personalizado para gerenciar minha residência.
* **Critérios de Aceitação:**
    * O sistema deve validar se o e-mail inserido possui formato válido.
    * A senha deve atender a requisitos mínimos de segurança (tamanho/caracteres).
    * O sistema deve confirmar a criação bem-sucedida do perfil no banco de dados.

### 2. Acesso ao Sistema (Login)
* **História:** Como usuário cadastrado, quero realizar o login no aplicativo para acessar as configurações e dispositivos da minha Smart Home de forma autenticada.
* **Critérios de Aceitação:**
    * O sistema deve autenticar o usuário comparando as credenciais com os dados cadastrados.
    * O sistema deve exibir as SmartHomes conectadas àquela conta logo após o acesso.
    * O sistema deve oferecer um fluxo de recuperação de acesso para senhas esquecidas.

### 3. Controle de Dispositivos (Interação)
* **História:** Como morador, quero acionar remotamente um dispositivo através da interface para poder ligá-lo ou desligá-lo à distância sem a necessidade de interação física manual.
* **Critérios de Aceitação:**
    * O sistema deve listar apenas os dispositivos disponíveis no cômodo onde o usuário está "presente".
    * A interface deve exibir status em tempo real (ex: ligado/desligado, temperatura atual).
    * O sistema deve validar se o perfil do usuário possui permissão para aquele comando.

### 4. Organização por Cômodos
* **História:** Como administrador da casa, quero vincular objetos inteligentes a cômodos específicos para facilitar a navegação e o controle organizado dos dispositivos.
* **Critérios de Aceitação:**
    * O sistema deve permitir a criação, edição e exclusão de cômodos.
    * Deve ser possível associar ou desassociar objetos de um cômodo via composição.
    * A interface deve permitir a filtragem de dispositivos por ambiente.

### 5. Automação por Modos Customizáveis
* **História:** Como usuário, quero criar modos customizados (ex: Modo Cinema) para que um conjunto de objetos execute funções simultâneas com um único comando.
* **Critérios de Aceitação:**
    * O sistema deve permitir salvar uma lista de estados (status) para múltiplos objetos sob um único "Modo".
    * Ao ativar um modo, o sistema deve iterar sobre os objetos e disparar os comandos automaticamente.
    * Deve ser possível disparar modos através de gatilhos de sensores.

### 6. Controle Parental e Permissões
* **História:** Como responsável legal, quero diferenciar as permissões entre perfis adultos e infantis para restringir o acesso de crianças a funções potencialmente perigosas.
* **Critérios de Aceitação:**
    * O sistema deve permitir a marcação de objetos como "Restritos".
    * Perfis do tipo "Infantil" devem ter o comando bloqueado ao tentar interagir com objetos restritos.
    * Apenas perfis do tipo "Adulto" podem alterar as travas de segurança.

### 7. Relatório de Uso de Energia
* **História:** Como usuário, quero saber quanto de energia cada objeto gastou em um certo período para monitorar meus custos e identificar aparelhos ineficientes.
* **Critérios de Aceitação:**
    * O sistema deve calcular o consumo baseado na potência do objeto e tempo de uso.
    * Deve ser exibida uma estimativa financeira baseada em uma tarifa (R$/kWh) configurável.
    * O relatório deve permitir a visualização do gasto total da residência e por categoria.

---

## 📝 Descrição do Problema e Contextualização

O projeto aborda a dificuldade de gerenciar múltiplos dispositivos inteligentes, focando em resolver a falta de controle centralizado sobre a segurança infantil , o monitoramento de gastos energéticos e a organização física dos aparelhos por cômodos. Em suma, o objetivo é unificar o controle da Smart Home para tornar a interação tecnológica mais segura e organizada.

### Motivação

O projeto nasce do desejo de simplificar a relação entre as pessoas e a tecnologia, transformando a automação em uma ferramenta de proteção e clareza para o dia a dia. Acreditamos que uma casa inteligente deve ser um ambiente onde o morador detém o controle total sobre a segurança e os gastos. 

O desenvolvimento deste sistema é impulsionado pelo desafio de resolver problemas cotidianos mapeados em nossas *User Stories*: garantir que a tecnologia seja acessível, mas controlada (através do Controle Parental), que a gestão da casa seja intuitiva (via organização por cômodos) e que o consumo de recursos seja visível e econômico (através de relatórios financeiros de energia).

## Funcionalidades/Objetivos Principais

1.  **Gestão de Perfis e Segurança**: Criação de contas com validação e sistema de login.
2.  **Controle Parental**: Restrição de funcionalidades de dispositivos baseada na classificação do perfil (Adulto vs. Infantil).
3.  **Organização Espacial**: Gerenciamento de dispositivos por cômodos para facilitar a interação do usuário.
4.  **Automação Inteligente**: Uso de sensores e modos pré-definidos para otimizar o funcionamento da residência.
5.  **Monitoramento Energético**: Visualização em forma de relatórios do consumo elétrico da casa.

---

## 🏗️ Estrutura Técnica e Contratos (C++)

O projeto é desenvolvido em C++, utilizando os princípios de Orientação a Objetos.

### Arquivos de Cabeçalho - Contratos (.hpp)
* `Conta.hpp`;
* `Login.hpp`;
* `ObjetoInteligente.hpp`;
* `Smarthome.hpp`;
* `Comodo.hpp`;
* `Sensor.hpp`;
* `Modo.hpp`;
* `RelatorioEnergia.hpp`.

---

## 📂 Organização do Repositório
```text
├── include/           # Arquivos de cabeçalho (.hpp)
├── src/               # Implementações (.cpp)
├── docs/              # PDFs com Cartões CRC e documentação de design
└── README.md          # Documentação principal