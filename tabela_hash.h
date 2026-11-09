#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// A3: Estrutura do Valor Armazenado
typedef struct {
    char telefone[20];   
    char nome[100];      
    char email[100];     
    char observacao[200];
} contato;

// E2.3: Estrutura do Nó para a Lista Circular Simples
typedef struct No {
    contato info;
    struct No *prox;     
} No;

// Estrutura Principal da Tabela Hash
typedef struct {
    No **vetor;           
    int capacidade;       
    int total_elementos;  
    int total_colisoes;   
} tabelahash;

void normalizar_telefone(const char *entrada, char *saida);
int funcao_hash_h2(const char *telefone_norm, int m);
tabelahash* criar_tabela(int capacidade);
void inserir(tabelahash *th, contato c);
contato* buscar(tabelahash *th, const char *telefone);
int atualizar(tabelahash *th, contato c);
int remover(tabelahash *th, const char *telefone);
void exibirEstrutura(tabelahash *th);
void destruir_tabela(tabelahash *th);

#endif