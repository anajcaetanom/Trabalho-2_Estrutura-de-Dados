#include "tp2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>


struct _paciente {
    char nome[30];
    char cpf[15];
    int idade;
    int id;
};

struct _node {
    struct Paciente *dados;
    struct _node *prev; 
    struct _node *next; 
};

struct _list {
    Node *begin;
    Node *end;
    int size;
};

struct _fila_node {
    int id;
    Registro *registro;
    FilaNode *next;
};

struct _fila {
    FilaNode *front;
    FilaNode *rear;
};

struct _aparelho {
    int occupation;
};

struct _registro {
    int id;
    int tempo;
    int condition;
};


// Criação de novo paciente.
Paciente *novo_paciente(const char nome[], const char cpf[], const int idade, const int id) {
    Paciente *novoPaciente = (Paciente*) calloc(1, sizeof(Paciente));

    strcpy(novoPaciente->nome, nome);
    strcpy(novoPaciente->cpf, cpf);
    novoPaciente->idade = idade;
    novoPaciente->id = id;
    
    return novoPaciente;
}

// Cria nó com o paciente novo.
Node *create_node(Paciente *novoPaciente) {
    Node *new_node = (Node*) calloc(1, sizeof(Node));
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->dados = novoPaciente;

    return new_node;
}

// Cria lista (vazia).
Lista *create_lista() {
    Lista *nova_lista = (Lista*) calloc(1, sizeof(Lista));
    nova_lista->begin = NULL;
    nova_lista->end = NULL;
    nova_lista->size = 0;

    return nova_lista;
}

// Cria fila (vazia).
Fila *create_fila() {
    Fila *F = (Fila*) calloc(1, sizeof(Fila));
    F->front = F->rear = NULL;

    return F;
}

// Verifica se lista está vazia.
bool list_is_empty(const Lista *L) {
    return L->size == 0;
}

// Verifica se fila está vazia.
bool fila_is_empty(const Fila *F) {
     return F->front == NULL;
}

// Adiciona elemento no começo da lista.
void add_no_inicio(Lista *L, Paciente *novoPaciente) {
    Node *n = create_node(novoPaciente);
    n->next = L->begin;

    if (list_is_empty(L)) {
        L->end = n;
    }
    else {
        L->begin->prev = n;
    }
    L->begin = n;
    L->size++;
}

// Adiciona id no final da fila.
void enfileirar_id(Fila *F, int id) {
    FilaNode *node = (FilaNode*) calloc(1, sizeof(FilaNode));
    node->id = id;
    node->registro == NULL;
    node->next = NULL;

    if (fila_is_empty(F))
        F->front = node;
    else
        F->rear->next = node;

    F->rear = node;
}

void enfileirar_registro(Fila *F, Registro *registro) {
    FilaNode *node = (FilaNode*) calloc(1, sizeof(FilaNode));
    node->id = NULL;
    node->registro == registro;
    node->next = NULL;

    if (fila_is_empty(F))
        F->front = node;
    else
        F->rear->next = node;

    F->rear = node;
}

// Retira elemento no início da fila e o retorna.
int desenfileirar_id(Fila *F) {

   assert(!fila_is_empty(F));

   int id = F->front->id;
   FilaNode *f = F->front; // Store for removal

   if (F->front != F->rear)
      F->front = F->front->next;
   else
      F->front = F->rear = NULL;

   free(f);
   return id;
}

void desenfileirar_registro(Fila *F) {

   assert(!fila_is_empty(F));

   FilaNode *f = F->front; // Store for removal

   if (F->front != F->rear)
      F->front = F->front->next;
   else
      F->front = F->rear = NULL;

   free(f);
   
}

Registro *create_registro(const int id, const int tempo, const int condition) {
    Registro *registro = (Registro*) calloc(1, sizeof(Registro));
    registro->id = id;
    registro->tempo = tempo;
    registro->condition = condition;

    return registro;
}

Aparelho *create_array() {
    int tamanho_array = 5;
    Aparelho *aparelhos = (Aparelho*) calloc(tamanho_array, sizeof(Aparelho));

    for (int i = 0; i < tamanho_array; i++) {
        aparelhos[i].ocupation = 0;
    }

    return aparelhos;
}   

int get_occupation(Aparelho *aparelhos, const int i) {
    return aparelhos[i].occupation;
}

void change_occupation(Aparelho *aparelhos, const int i, int new_ocupation) {
    aparelhos[i].occupation = new_ocupation;
}

int condition() {
    srand(time(NULL));
    int n = rand() % 100 + 1;
    int prob1 =  30;
    int prob2 =  50;
    int prob3 =  70;
    int prob4 =  85;
    int prob5 =  100;

    if (n <= prob1) {
        return 1;
    }
    else if (n > prob1 && n <= prob2) {
        return 2;
    }
    else if (n > prob2 && n <= prob3) {
        return 3;
    }
    else if (n > prob3 && n <= prob4) {
        return 4;
    }
    else {
        return 5;
    }
}



