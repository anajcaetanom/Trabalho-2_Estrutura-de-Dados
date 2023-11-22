#include "tp2.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int main() {

    char nomeArquivo[30], nome[30], cpf[20];
    int idade;
    int id, uT = 0;
    
    Lista *lista_de_pacientes = create_lista(); // Criação da lista de pacientes.
    Fila *fila_para_exame = create_fila(); // Criação da fila para exame.
    
    uT++; // Incremento na unidade de tempo.

    // Abrindo o arquivo e armazenando os dados.
    printf("Insira nome do arquivo (com a extensão): ");
    scanf("%s", nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        puts("Erro ao abrir arquivo.");
        exit(EXIT_FAILURE);
    }

    uT++; // Incremento na unidade de tempo.

    /* CHEGADA DE PACIENTES */
    while (fscanf(arquivo, "%30[^\n]\n%15[^\n]\n%d\n", nome, cpf, &idade) == 3) {
        srand(time(NULL));

        do {
            srand(time(NULL));
            uT++; // Incremento na unidade de tempo.
            printf("%d\n", uT);
        } while (!(rand() % 10 + 1 <= 2)); // Probabilidade de 20% de chegar um paciente. 
            
        id++;
        Paciente *paciente = novo_paciente(nome, cpf, idade, id); // Criação de paciente.
        add_no_inicio(lista_de_pacientes, paciente); // Inserção do paciente na lista de pacientes.
        free(paciente);
        print_lista(lista_de_pacientes);

        enfileirar_id(fila_para_exame, id); // Inserção do id na fila para exame.
        print_fila(fila_para_exame);
        
        uT++; // Incremento na unidade de tempo.
    }

    free(arquivo);

   
}