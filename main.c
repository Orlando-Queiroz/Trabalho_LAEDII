#include "tabela_hash.h"
#include <time.h>

// FUNÇÕES AUXILIARES

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pausar() {
    printf("\n[Pressione ENTER para continuar...]");
    getchar(); 
}

void ler_texto(char *buffer, int tamanho) {
    fgets(buffer, tamanho, stdin);
    buffer[strcspn(buffer, "\n")] = 0; 
}


// MÓDULO 1: AGENDA INTERATIVA

void modulo_interativo() {
    int capacidade;
    int opcao = -1;

    printf("\n--- MODO INTERATIVO ---\n");
    printf("Digite a capacidade inicial da tabela: ");
    scanf("%d", &capacidade);
    limpar_buffer(); 

    tabelahash *th = criar_tabela(capacidade);

    while (opcao != 0) {
        printf("\n1. Inserir | 2. Buscar | 3. Atualizar | 4. Remover | 5. Imprimir | 0. Voltar\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        limpar_buffer(); 

        if (opcao == 1) {
            contato c;
            printf("Telefone (Chave): "); ler_texto(c.telefone, sizeof(c.telefone));
            printf("Nome: "); ler_texto(c.nome, sizeof(c.nome));
            printf("E-mail: "); ler_texto(c.email, sizeof(c.email));
            printf("Observacao: "); ler_texto(c.observacao, sizeof(c.observacao));
            inserir(th, c);
            printf("Contato inserido com sucesso!\n");
        } 
        else if (opcao == 2) {
            char tel[20];
            printf("Telefone para buscar: "); ler_texto(tel, sizeof(tel));
            contato *busca = buscar(th, tel);
            if (busca) printf("Encontrado: %s | %s | %s\n", busca->nome, busca->email, busca->observacao);
            else printf("Contato nao encontrado.\n");
        }
        else if (opcao == 3) {
            contato c;
            printf("Telefone para atualizar: "); ler_texto(c.telefone, sizeof(c.telefone));
            printf("Novo Nome: "); ler_texto(c.nome, sizeof(c.nome));
            printf("Novo E-mail: "); ler_texto(c.email, sizeof(c.email));
            printf("Nova Observacao: "); ler_texto(c.observacao, sizeof(c.observacao));
            if (atualizar(th, c)) printf("Contato atualizado!\n");
            else printf("Contato nao encontrado.\n");
        }
        else if (opcao == 4) {
            char tel[20];
            printf("Telefone para remover: "); ler_texto(tel, sizeof(tel));
            if (remover(th, tel)) printf("Contato removido!\n");
            else printf("Contato nao encontrado.\n");
        }
        else if (opcao == 5) {
            exibirEstrutura(th);
        }
    }
    destruir_tabela(th);
}

// MÓDULO 2: ANÁLISE EXPERIMENTAL 

void modulo_analise_experimental() {
    int tamanhos[] = {100, 1000, 10000}; 
    int repeticoes = 5; 

    printf("\n========================================================\n");
    printf("           TESTE DE CARGA           \n");
    printf("========================================================\n");

    double tempos_ins[3], tempos_b_ok[3], tempos_b_aus[3];
    int medias_colisoes[3];

    for (int t = 0; t < 3; t++) {
        int n = tamanhos[t];
        double t_ins = 0, t_busca_ok = 0, t_busca_aus = 0;
        int colisoes = 0;

        printf("-> Processando carga de %d registros... ", n);
        fflush(stdout); 

        for (int r = 0; r < repeticoes; r++) {
            tabelahash *th = criar_tabela(n);
            clock_t inicio, fim;

            inicio = clock();
            for (int i = 0; i < n; i++) {
                contato c = {"", "", "", ""};
                sprintf(c.telefone, "839%07d", i); 
                inserir(th, c);
            }
            fim = clock();
            t_ins += ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;
            colisoes += th->total_colisoes;

            inicio = clock();
            for (int i = 0; i < n; i++) {
                char tel[20];
                sprintf(tel, "839%07d", i);
                buscar(th, tel);
            }
            fim = clock();
            t_busca_ok += ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;

            inicio = clock();
            for (int i = 0; i < n; i++) {
                char tel[20];
                sprintf(tel, "111%07d", i); 
                buscar(th, tel);
            }
            fim = clock();
            t_busca_aus += ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000.0;

            destruir_tabela(th);
        }
        
        printf("Concluido!\n"); 
        
        tempos_ins[t] = t_ins / repeticoes;
        tempos_b_ok[t] = t_busca_ok / repeticoes;
        tempos_b_aus[t] = t_busca_aus / repeticoes;
        medias_colisoes[t] = colisoes / repeticoes;
    }

    printf("\n===================================================================================\n");
    printf("                              RELATORIO DE DESEMPENHO (Medias de 5 repeticoes)\n");
    printf("===================================================================================\n");
    printf(" Registros | Capacidade |  Colisoes  | Ins. (ms)   | B. Sucesso (ms) | B. Falha (ms)\n");
    printf("-----------------------------------------------------------------------------------\n");
    for (int t = 0; t < 3; t++) {
        printf(" %9d | %10d | %10d | %11.4f | %15.4f | %13.4f \n", 
               tamanhos[t], tamanhos[t], medias_colisoes[t], 
               tempos_ins[t], tempos_b_ok[t], tempos_b_aus[t]);
    }
    printf("===================================================================================\n");
    pausar();
}

// FUNÇÃO MAIN

int main() {
    int opcao = -1;

    while (opcao != 0) {
        printf("\n=========================================\n");
        printf(" PAINEL DE CONTROLE - TRABALHO HASH\n");
        printf(" Config: E2.3 (Circular), H2 (Mult), C1 (Sep), A3 (Agenda)\n");
        printf("=========================================\n");
        printf("1. Agenda Interativa (Demonstracao Manual)\n");
        printf("2. Executar Analise Experimental (Desempenho)\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        limpar_buffer(); 

        if (opcao == 1) modulo_interativo();
        else if (opcao == 2) modulo_analise_experimental();
        else if (opcao == 0) printf("A encerrar e a libertar memoria...\n");
        else printf("Opcao invalida. Tente novamente.\n");
    }
    return 0;
}