# Battleship
Primeiro trabalho de programação de redes

## Descrição
Implementação de jogo de batalha naval que rode sobre o protocolo TCP. O jogo terá um lado cliente e um lado servidor:

* O cliente se conecta ao servidor;
* O servidor escuta por solicitações de conexão.

O que deverá ser passado como parâmetro para o cliente:

* Endereço IP do servidor;
* Porta do servidor.

O que deverá ser passado como parâmetro para o servidor:

* Porta em que o servidor atuará;

O jogo deverá seguir as regras de um protocolo específico. Ele deverá conter vários tipos de mensagem:

1. Código tipo 1: Mensagem de apresentação:
    * Possui o objetivo de apresentar um usuário a outro e trocar os nicknames.
2. Código tipo 2: Mensagem de ataque:
    * Tem o dever de entregar uma coordenada de ataque ao outro jogador.
3. Código tipo 3:
4. Código tipo 4:

