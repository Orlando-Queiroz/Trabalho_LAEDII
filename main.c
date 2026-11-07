#include "tabela_hash.h"

int main() {
    tabelahash *th = criar_tabela(7);

    printf("\n --- INSERINDO CONTATOS DE TESTE ---\n");
    
    contato c1 = {"83 98918419", "Maria", "mariaritaalmeida@email.com", "eu"};
    contato c2 = {"83 999992222", "Ana", "ana@email.com", "amiga"};
    contato c3 = {"83 99999-3333", "Joao", "joao@email.com", "faculdade"};

    inserir(th, c1); // primeiro contato na tabela hash
    inserir(th, c2); // segundo contato 
    inserir(th, c3); // terceiro contato

    exibirEstrutura(th); // exibe a estrutura 

    printf("\n--- TESTE DE BUSCA ---\n");
    contato *busca = buscar(th, "83 98918419");
    if (busca) {
        printf("Encontrado: %s (%s)\n", busca->nome, busca->telefone);
    } else {
        printf("Contato nao encontrado.\n");
    }

    destruir_tabela(th);

    return 0;
}