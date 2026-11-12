# Trabalho_LAEDII
___
## Autores
* Maria Rita de Almeida Silva - 2023011844 
* Fernando Gomes Teixeira - 2026022624
* Francisco Orlando Queiroz da Silva - 2022010340
___
## Agenda de Contatos - Tabela Hash em C

Este projeto é uma implementação de uma Tabela Hash na linguagem C, desenvolvida para a disciplina de Estruturas de Dados. O sistema funciona como uma agenda de contatos telefônicos otimizada 
___
## Requisitos do Trabalho

O projeto foi construído respeitando as seguintes restrições:

*   **Método de Hashing (H2):** Método da Multiplicação por constante. 
*   **Tratamento de Colisões (E2.3):** Encadeamento Separado.
*   **Estrutura (C1) :** Lista Encadeada Circular Simples.
*   **Aplicação (A3) :** Agenda Telefônica de contatos (nome, numero, email, observações) .

___

## Estrutura do Projeto

*   tabela_hash.h: Contém as definições das estruturas de dados  e as assinaturas das funções.
*   tabela_hash.c: Contém a lógica matemática de hashing, gerenciamento de memória e manipulação dos ponteiros da lista circular.
*   main.c: A interface do sistema. Contém o menu interativo e o Módulo Experimental para testes de carga e medição de tempo de execução em milissegundos.

___

## Como Compilar e Executar

Certifique-se de ter o compilador GCC instalado .

1. Abra o terminal na pasta do projeto.
2. Compile os arquivos juntos (o `-lm` é necessário no Linux para a biblioteca matemática `<math.h>` do método H2):
   ```bash
   gcc main.c tabela_hash.c -o agenda -lm
    ```
     ```bash
   agenda.exe
