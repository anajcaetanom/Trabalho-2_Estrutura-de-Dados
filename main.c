#include "tp2.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

int main() {

    char nomeArquivo[30], nome[30], cpf[15];
    int idade;
    int id, uT = 0;
    
    Lista *lista_de_pacientes = create_lista(); // Criação da lista de pacientes.
    Fila *fila_para_exame = create_fila(); // Criação da fila para exame.
    
    // Abrindo o arquivo e armazenando os dados.
    printf("Insira nome do arquivo (com a extensão): ");
    scanf("%s", nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "r");



    while (fscanf(arquivo, "%30[^\n]\n%d\n%15[^\n]\n", nome, &idade, cpf) == 3) {
        srand(time(NULL));
        if (((rand() % 5) + 1) == 2 && ((rand() % 5) + 1) == 1) { // Probabilidade de 20% de chegar um paciente. 
            id++;
            Paciente *paciente = novo_paciente(nome, cpf, idade, id); // Criação de paciente.
            add_no_inicio(lista_de_pacientes, paciente); // Inserção do paciente na lista de pacientes.
            enfileirar_id(fila_para_exame, id); // Inserção do id na fila para exame.
        }
    }

    Aparelho *aparelhos = create_array(); // Criação de uma array com 5 aparelhos disponíveis.

    for (int i = 0; i < 5; i++) {

        if ((get_occupation(aparelhos, i)) == 0) {
            srand(time(NULL));
            int id;
            int i = 0; 
            int tempo_de_exame = rand() % 6 + 5;
            change_occupation(aparelhos, i, 1); // Muda ocupação para "1" (ocupado).
            
            id = desenfileirar(fila_para_exame);
            printf("Paciente com o id %d retirado da fila para exame.", id);

            do {

            } while (i <= tempo_de_exame);
            puts("Exame finalizado.");

            Registro *registro = create_registro(id, tempo, condition());

        
        }
    }

    
    




}