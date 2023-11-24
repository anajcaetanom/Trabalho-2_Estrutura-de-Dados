#include "tp2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct _paciente {
    char nome[30];
    char cpf[15];
    int idade;
    int id;
};

struct _node {
    Paciente *dados;
    Node *prev; 
    Node *next; 
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

struct _occupation {
    int occupation;
};

struct _registro {
    int id;
    int tempo;
    char condition[30];
};

struct _tempos {
    int tempo_entrada;
    int tempo_saida;
    char patologia[30];
};

// Criação de novo paciente.
Paciente *novo_paciente(const char nome[], const char cpf[], const int idade, const int id) {
    Paciente *novoPaciente = (Paciente*) calloc(1, sizeof(Paciente));

    if (novoPaciente == NULL) {
        puts("Falha na alocação de novo paciente.");
        exit(EXIT_FAILURE);
    }

    strcpy(novoPaciente->nome, nome);
    strcpy(novoPaciente->cpf, cpf);
    novoPaciente->idade = idade;
    novoPaciente->id = id;
    
    return novoPaciente;
}

// Cria nó com o paciente novo.
Node *create_node(Paciente *novoPaciente) {
    Node *new_node = (Node*) calloc(1, sizeof(Node));

    if (new_node == NULL) {
        puts("Falha na alocação de novo nó.");
        exit(EXIT_FAILURE);
    }
    
    new_node->prev = NULL;
    new_node->next = NULL;
    new_node->dados = novoPaciente;

    return new_node;
}

// Cria lista (vazia).
Lista *create_lista() {
    Lista *nova_lista = (Lista*) calloc(1, sizeof(Lista));

    if (nova_lista == NULL) {
        puts("Falha na alocação de nova lista.");
        exit(EXIT_FAILURE);
    }

    nova_lista->begin = NULL;
    nova_lista->end = NULL;
    nova_lista->size = 0;

    return nova_lista;
}

// Cria fila (vazia).
Fila *create_fila() {
    Fila *F = (Fila*) calloc(1, sizeof(Fila));

    if (F == NULL) {
        puts("Falha na alocação de nova fila.");
        exit(EXIT_FAILURE);
    }

    F->front = F->rear = NULL;

    return F;
}

// Verifica se lista está vazia.
int list_is_empty(const Lista *L) {
    if (L->size == 0) return 0;
    else return 1;
}

// Verifica se fila está vazia.
int fila_is_empty(const Fila *F) {
    if (F->front == NULL) return 0;
    else return 1;
}

// Adiciona elemento no começo da lista.
void add_no_inicio(Lista *L, Paciente *novoPaciente) {
    Node *n = create_node(novoPaciente);

    if (n == NULL) {
        puts("Falha na alocação de novo nó (add_no_inicio).");
        exit(EXIT_FAILURE);
    }

    n->next = L->begin;

    if ((list_is_empty(L)) == 0) {
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

    if (node == NULL) {
        puts("Falha na alocação de novo nó (enfileirar_id).");
        exit(EXIT_FAILURE);
    }

    node->id = id;
    node->registro = NULL;
    node->next = NULL;

    if ((fila_is_empty(F)) == 0) F->front = node;
    else F->rear->next = node;

    F->rear = node;
}

// Adiciona registro no final da fila.
void enfileirar_registro(Fila *F, Registro *registro) {
    FilaNode *node = (FilaNode*) calloc(1, sizeof(FilaNode));

    if (node == NULL) {
        puts("Falha na alocação de novo nó (enfileirar_registro).");
        exit(EXIT_FAILURE);
    }

    node->id = 0;
    node->registro = registro;
    node->next = NULL;

    if ((fila_is_empty(F)) == 0)F->front = node;
    else F->rear->next = node;

    F->rear = node;
}

// Retira elemento no início da fila e o retorna.
int desenfileirar_id(Fila *F) {

    int id = F->front->id;
    FilaNode *f = F->front; // Store for removal

    if (F->front != F->rear)
        F->front = F->front->next;
    else
        F->front = F->rear = NULL;

    free(f);
    return id;
}

// Desenfileira registro.
void desenfileirar_registro(Fila *F) {

   FilaNode *f = F->front; 

   if (F->front != F->rear)
      F->front = F->front->next;
   else
      F->front = F->rear = NULL;

   free(f);
   
}

// Criação de registro.
Registro *create_registro(const int id, const int tempo, const char condition[]) {
    Registro *registro = (Registro*) calloc(1, sizeof(Registro));

    if (registro == NULL) {
        puts("Falha na alocação de novo registro.");
        exit(EXIT_FAILURE);
    }

    registro->id = id;
    registro->tempo = tempo;
    strcpy(registro->condition, condition);
    
   

    return registro;
}

// Criação de array de structs.
Occupation *create_array(int tamanho) {
    Occupation *aparelhos = (Occupation*) calloc(tamanho, sizeof(Occupation));

    if (aparelhos == NULL) {
        puts("Falha na alocação de novo array.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; i++) {
        aparelhos[i].occupation = 0;
    }

    return aparelhos;
}   

// Retorna ocupação de struct que contenha ocupação.
int get_occupation(Occupation *estrutura, const int i) {
    return estrutura[i].occupation;
}

// Altera ocupação.
void change_occupation(Occupation *estrutura, const int i, int new_ocupation) {
    estrutura[i].occupation = new_ocupation;
}

// Retorna a patologia de acordo com suas probabilidades.
char* condition() {
    int n = rand() % 100 + 1;
    int prob1 =  30;
    int prob2 =  50;
    int prob3 =  70;
    int prob4 =  85;

    static char c[30];

    if (n <= prob1) strcpy(c, "Saúde Normal");
    else if (n > prob1 && n <= prob2) strcpy(c, "Bronquite");
    else if (n > prob2 && n <= prob3) strcpy(c, "Pneumonia");
    else if (n > prob3 && n <= prob4) strcpy(c, "Fratura de Fêmur ");
    else strcpy(c, "Apendicite");

    return c;
}

// Função para imprimir fila para exame.
void print_fila(Fila *F) {
   for (FilaNode *f = F->front; f != NULL; f = f->next)
      printf("%d ", f->id);

   printf("\n");
}

// Função para imprimir fila de laudo.
void print_fila_registro(Fila *F) {
    puts("\n-------------FILA DE REGISTRO-------------");
    for (FilaNode *f = F->front; f != NULL; f = f->next)
        printf("\n!registro!\nID: %d\nTempo: %d\nCondição: %s\n\n", f->registro->id, f->registro->tempo, f->registro->condition);

   printf("\n");
}

// Função para imprimir struct Paciente.
void print_paciente(Paciente *p) {
    char nome[30];
    char cpf[20];
    int idade;
    int id;
    
    strcpy(nome, p->nome);
    strcpy(cpf, p->cpf);
    idade = p->idade;
    id = p->id;
    
    printf("Nome: %s\nCPF: %s\nIdade: %d\nID: %d\n", nome, cpf, idade, id);
}

// Função para imprimir lista de pacientes.
void print_lista(Lista *l) {
   for (Node *p = l->begin; p != NULL; p = p->next)
   {
      print_paciente(p->dados); 
   }
   printf("\n"); 
}


void insert_tempo_entrada(Tempos *t, int tempo_entrada) {
    t->tempo_entrada = tempo_entrada;
}


void insert_tempo_saida(Tempos *t, int tempo_saida) {
    t->tempo_saida = tempo_saida;
}


void insert_tempo_patologia(Tempos *t, char patologia[]) {
    strcpy(t->patologia, patologia);
}


Tempos **create_array_tempos(int tamanho) {
    Tempos **tempos = (Tempos**) calloc(tamanho, sizeof(Tempos*));

    if (tempos == NULL) {
        puts("Falha na alocação de novo array.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < tamanho; i++) {
        tempos[i] = create_tempos();
    }

    return tempos;

}



Tempos* create_tempos() {
    Tempos *t = (Tempos*) calloc(1, sizeof(Tempos));
    t->tempo_entrada = 0;
    t->tempo_saida = 0;
    strcpy(t->patologia, NULL);

    return t;
}


int tempo_laudo(Tempos *tempos) {
    int t = (tempos->tempo_saida) - (tempos->tempo_entrada);
    return t;
}