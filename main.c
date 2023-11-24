#include "tp2.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    srand(time(NULL));
    char nomeArquivo[30], nome[30], cpf[20], p[30];
    int idade, r, tempo_de_exame, tempo, id_retirado;
    int id, uT, qtd = 0;
    
    Lista *lista_de_pacientes = create_lista(); // Criação da lista de pacientes.
    Fila *fila_para_exame = create_fila(); // Criação da fila para exame.

    // Abrindo o arquivo e armazenando os dados.
    printf("Insira nome do arquivo (com a extensão): ");
    scanf("%s", nomeArquivo);
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        puts("Erro ao abrir arquivo.");
        exit(EXIT_FAILURE);
    }

    /* SIMULAÇÃO */

    /* CHEGADA DE PACIENTES */
    while ((fscanf(arquivo, "%30[^\n]\n%15[^\n]\n%d\n", nome, cpf, &idade) == 3) && (uT <= 43200)) {

        do {
            r = rand() % 10 + 1;
            uT++; // Incremento na unidade de tempo.

            if (uT > 43200) {
                puts("Tempo máximo excedido.");
                exit(EXIT_FAILURE);
            }

        } while (!(r <= 2)); // Probabilidade de 20% de chegar um paciente. 

        id++;
        Paciente *paciente = novo_paciente(nome, cpf, idade, id); // Criação de paciente.
        add_no_inicio(lista_de_pacientes, paciente); // Inserção do paciente na lista de pacientes.
        free(paciente);

        enfileirar_id(fila_para_exame, id); // Inserção do id na fila para exame.
        
        if (uT > 43200) {
            puts("Tempo máximo excedido.");
            exit(EXIT_FAILURE);
        }
        qtd++;
    }

    fclose(arquivo); // Fechar arquivo.

    Occupation *aparelhos = create_array(5); // Criação de uma array com 5 aparelhos disponíveis.
    Fila *fila_para_laudo = create_fila(); // Criação da fila para laudo (vazia).

    Tempos **array_tempos = create_array_tempos(qtd);

    for (int i = 0; i < 5; i++) {

        /* REALIZAÇÃO DO EXAME DE RAIO-X */
        if ((get_occupation(aparelhos, i)) == 0) {
            if ((fila_is_empty(fila_para_exame)) == 1) {
                int k = 0;
                tempo_de_exame = (rand() % 6 + 5);
                id_retirado = desenfileirar_id(fila_para_exame);
                change_occupation(aparelhos, i, 1); // Muda ocupação para "1" (ocupado).

                for (int j = 0; j <= tempo_de_exame; j++) uT++;

                puts("Exame finalizado.");

                tempo = uT + tempo_de_exame;

                if(array_tempos[k])

                strcpy(p, condition());
                Registro *registro = create_registro(id_retirado, tempo, p); 
                enfileirar_registro(fila_para_laudo, registro); // Adiciona registro na fila para laudo.

                print_fila_registro(fila_para_laudo);
                uT = tempo;



                change_occupation(aparelhos, i, 0); // Muda ocupação para "0" (livre).

                uT++; // Incremento na unidade de tempo.  
            }
            
        }
    }   

    /* REALIZAÇÃO DE LAUDOS */

    Occupation *radiologista = create_array(3); //

    for (int i = 0; i < 3; i++) {
        if ((get_occupation(radiologista, i)) == 0) {

            desenfileirar_registro(fila_para_laudo); // Tira registro da fila para laudo.

            int tempo_de_exame = rand() % 20 + 10;

            change_occupation(radiologista, i, 1); // Muda ocupação para "1" (ocupado).

            for (int j = 0; j <= tempo_de_exame; j++) uT++; // Preparação do laudo.

            change_occupation(radiologista, i, 0); // Muda ocupação para "0" (livre).

        }

        uT++;

    }





    return 0;
}