#include "tp2.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    srand(time(NULL));
    char nomeArquivo[30], nome[30], cpf[20], p[30];
    int idade, r, tempo_de_exame, tempo, id_retirado, index, TempoMedioLaudo, SN, BQ, PN, FF, AP;
    int id, uT, qtd, SumTempoLaudo, sSN, sBQ, sPN, sFF, sAP, qSN, qBQ, qPN, qFF, qAP = 0;
    
    Lista *lista_de_pacientes = create_lista(); // Criação da lista de pacientes.
    Fila *fila_para_exame = create_fila(); // Criação da fila para exame.

    // Abrindo o arquivo e armazenando os dados.
    /* printf("Insira nome do arquivo (com a extensão): ");
    scanf("%s", nomeArquivo); */
    FILE *arquivo = fopen("input.txt", "r");

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

        } while (!(r <= 2)); // Probabilidade de 20% de chegar um paciente. 

        id++;
        Paciente *paciente = novo_paciente(nome, cpf, idade, id); // Criação de paciente.
        add_no_inicio(lista_de_pacientes, paciente); // Inserção do paciente na lista de pacientes.
        free(paciente);

        enfileirar_id(fila_para_exame, id); // Inserção do id na fila para exame.
        
        qtd++;
    }

    fclose(arquivo); // Fechar arquivo.

    Occupation *aparelhos = create_array(5); // Criação de uma array com 5 aparelhos disponíveis.
    Fila *fila_para_laudo = create_fila(); // Criação da fila para laudo (vazia).

    Tempos *array_tempos = create_array_tempos(qtd);

    for (int i = 0; i < 5; i++) {

        /* REALIZAÇÃO DO EXAME DE RAIO-X */
        if ((get_occupation(aparelhos, i)) == 0) {
            if ((fila_is_empty(fila_para_exame)) == 1) {

                tempo_de_exame = (rand() % 6 + 5);

                id_retirado = desenfileirar_id(fila_para_exame);

                change_occupation(aparelhos, i, 1); // Muda ocupação para "1" (ocupado).

                for (int j = 0; j <= tempo_de_exame; j++) uT++;

                tempo = uT + tempo_de_exame;

                strcpy(p, condition());

                if (strcmp(p, "Saúde Normal") == 0) qSN++;
                else if (strcmp(p, "Bronquite") == 0) qBQ++;
                else if (strcmp(p, "Pneumonia") == 0) qPN++;
                else if (strcmp(p, "Fratura de Fêmur") == 0) qFF++;
                else qAP++;

                Registro *registro = create_registro(id_retirado, tempo, p); 

                enfileirar_registro(fila_para_laudo, registro); // Adiciona registro na fila para laudo.

                if (empty_array_index(array_tempos, qtd) == -1) {
                    printf("Nenhuma struct vazia. Realização do exame de raio x.\n");
                    exit(EXIT_FAILURE);
                }

                index = empty_array_index(array_tempos, qtd);

                insert_entrada(array_tempos, tempo, index, id_retirado, p); // Insere tempo de entrada na fila para laudo, id do paciente e patologia em uma struct vazia.

                print_array(array_tempos, index);

                uT = tempo;

                change_occupation(aparelhos, i, 0); // Muda ocupação para "0" (livre).

                uT++; // Incremento na unidade de tempo.  
            
            
            }
            
        }
    }   

    /* REALIZAÇÃO DE LAUDOS */

    Occupation *radiologista = create_array(3); //

    for (int i = 0; i < qtd; i++) {
        if ((get_occupation(radiologista, i)) == 0) {

            Registro *r = desenfileirar_registro(fila_para_laudo); // Tira registro da fila para laudo e o retorna.

            id_retirado = get_id_registro(r);
            strcpy(p, get_diagnostico_registro(r));

            index = index_from_id(array_tempos, id_retirado, qtd); // Pega o indice do elemento na array que contem o id do paciente.

            insert_tempo_saida(array_tempos, uT, index); // Insere tempo que o paciente saiu da fila para laudo.

            if (strcmp(p, "Saúde Normal") == 0) sSN += tempo_laudo(array_tempos, index);
            else if (strcmp(p, "Bronquite") == 0) sBQ = tempo_laudo(array_tempos, index);
            else if (strcmp(p, "Pneumonia") == 0) sPN = tempo_laudo(array_tempos, index);
            else if (strcmp(p, "Fratura de Fêmur") == 0) sFF = tempo_laudo(array_tempos, index);
            else sAP = tempo_laudo(array_tempos, index);

            print_array(array_tempos, index);

            SumTempoLaudo += tempo_laudo(array_tempos, index); // Acrescenta tempo do laudo na variavel auxiliar para calculo da media.

            printf("\nSum: %d\n", SumTempoLaudo);

            int tempo_de_exame = rand() % 20 + 10; 

            change_occupation(radiologista, i, 1); // Muda ocupação para "1" (ocupado).

            for (int j = 0; j <= tempo_de_exame; j++) uT++; // Preparação do laudo.

            change_occupation(radiologista, i, 0); // Muda ocupação para "0" (livre).

        }

        uT++;

    }

    TempoMedioLaudo = SumTempoLaudo/qtd;
    SN = sSN/qSN;
    BQ = sBQ/qBQ;
    PN = sPN/qPN;
    FF = sFF/qFF;
    AP = sAP/qAP;

    printf("\nTempo médio geral na fila de laudo: %d\n", TempoMedioLaudo);
    printf("\nTempo médio do diagnostico 'Saude Normal' na fila de laudo: %d", SN);
    printf("\nTempo médio do diagnostico 'Bronquite' na fila de laudo: %d", BQ);
    printf("\nTempo médio do diagnostico 'Pneumonia' na fila de laudo: %d", PN);
    printf("\nTempo médio do diagnostico 'Fratura de Fêmur' na fila de laudo: %d", FF);
    printf("\nTempo médio do diagnostico 'Apendicite' na fila de laudo: %d", AP);




    return 0;
}