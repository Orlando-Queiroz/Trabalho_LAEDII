#ifndef tabela_hash_h
#define tabela_hash_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// A3: 
typedef struct {
    char telefone[20];   
    char nome[100];      
    char email[100];     
    char observacao[200];
} contato;

// E2.3:
typedef struct No {
    contato info;
    struct No *prox;     
} No;

typedef struct {
    No **vetor;           
    int capacidade;       
    int total_elementos;  
    int total_colisoes;   
} tabelahash;

// E2.4:
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