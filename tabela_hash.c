#include "tabela_hash.h"

void normalizar_telefone(const char *entrada, char *saida) { 
    int j = 0; 
    for (int i = 0; entrada[i] != '\0'; i++) {
        if (isdigit((unsigned char)entrada[i])) {
            saida[j++] = entrada[i];
        }
    }
    saida[j] = '\0';
}

// H2: Método da Multiplicação
int funcao_hash_h2(const char *telefone_norm, int m) {
    unsigned long long k = strtoull(telefone_norm, NULL, 10);
    double A = 0.6180339887; 
    double produto = k * A; 
    double parte_fracionaria = produto - floor(produto);
    return (int)floor(m * parte_fracionaria);
}

tabelahash* criar_tabela(int capacidade) {
    tabelahash *th = (tabelahash*) malloc(sizeof(tabelahash));
    th->capacidade = capacidade;
    th->total_elementos = 0;
    th->total_colisoes = 0;
    th->vetor = (No**) calloc(capacidade, sizeof(No*));
    return th;
}

// E2.3 + C1: Inserção na Lista Circular Simples
void inserir(tabelahash *th, contato c) {
    char tel_norm[20];
    normalizar_telefone(c.telefone, tel_norm);
    strcpy(c.telefone, tel_norm);

    if (buscar(th, tel_norm) != NULL) return; // Evita chaves duplicadas

    int idx = funcao_hash_h2(tel_norm, th->capacidade);
    No *novo = (No*) malloc(sizeof(No)); 
    novo->info = c;

    if (th->vetor[idx] == NULL) {
        th->vetor[idx] = novo;
        novo->prox = novo; // Circular: aponta para si mesmo
    } else {
        th->total_colisoes++;
        novo->prox = th->vetor[idx]->prox;
        th->vetor[idx]->prox = novo;
    }
    th->total_elementos++;
}

contato* buscar(tabelahash *th, const char *telefone) {
    char tel_norm[20];
    normalizar_telefone(telefone, tel_norm);
    int idx = funcao_hash_h2(tel_norm, th->capacidade);

    if (th->vetor[idx] == NULL) return NULL;

    No *inicio = th->vetor[idx];
    No *atual = inicio;

    do {
        if (strcmp(atual->info.telefone, tel_norm) == 0) {
            return &(atual->info);
        }
        atual = atual->prox;
    } while (atual != inicio);

    return NULL;
}

int atualizar(tabelahash *th, contato c) {
    char tel_norm[20];
    normalizar_telefone(c.telefone, tel_norm);
    contato *existente = buscar(th, tel_norm);

    if (existente != NULL) {
        strcpy(existente->nome, c.nome);
        strcpy(existente->email, c.email);
        strcpy(existente->observacao, c.observacao);
        return 1;
    }
    return 0;
}

int remover(tabelahash *th, const char *telefone) {
    char tel_norm[20];
    normalizar_telefone(telefone, tel_norm);
    int idx = funcao_hash_h2(tel_norm, th->capacidade);

    if (th->vetor[idx] == NULL) return 0;

    No *inicio = th->vetor[idx];
    No *atual = inicio;
    No *anterior = NULL;

    No *ultimo = inicio;
    while (ultimo->prox != inicio) {
        ultimo = ultimo->prox;
    }

    do {
        if (strcmp(atual->info.telefone, tel_norm) == 0) {
            if (atual == atual->prox) {
                th->vetor[idx] = NULL; 
            } else {
                if (atual == inicio) {
                    th->vetor[idx] = atual->prox; 
                    ultimo->prox = th->vetor[idx];
                } else {
                    anterior->prox = atual->prox; 
                }
            }
            free(atual);
            th->total_elementos--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    } while (atual != inicio);

    return 0;
}

void exibirEstrutura(tabelahash *th) {
    printf("\n--- ESTADO DA TABELA HASH ---\n");
    printf("(m=%d, n=%d, Colisoes=%d)\n", th->capacidade, th->total_elementos, th->total_colisoes);

    for (int i = 0; i < th->capacidade; i++) {
        printf("Bucket [%02d]: ", i);
        if (th->vetor[i] == NULL) {
            printf("NULL\n");
        } else {
            No *inicio = th->vetor[i];
            No *atual = inicio;
            do {
                printf("[%s | %s] -> ", atual->info.telefone, atual->info.nome);
                atual = atual->prox;
            } while (atual != inicio);
            printf("(volta ao inicio: %s)\n", inicio->info.telefone);
        }
    }
}

void destruir_tabela(tabelahash *th) {
    for (int i = 0; i < th->capacidade; i++) {
        if (th->vetor[i] != NULL) {
            No *inicio = th->vetor[i];
            No *atual = inicio->prox;
            while (atual != inicio) {
                No *temp = atual;
                atual = atual->prox;
                free(temp);
            }
            free(inicio);
        }
    }
    free(th->vetor);
    free(th);
}