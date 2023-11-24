#ifndef TP2_H
#define TP2_H


typedef struct _paciente Paciente;

typedef struct _node Node;
typedef struct _list Lista;

typedef struct _fila Fila;
typedef struct _fila_node FilaNode;

typedef struct _occupation Occupation;

typedef struct _fila_node_registro NodeRegistro;
typedef struct _fila_registro FilaRegistro;
typedef struct _registro Registro;

typedef struct _tempos Tempos;

// Criação de novo paciente.
Paciente *novo_paciente(const char nome[], const char cpf[], const int idade, const int id);

// Cria nó com o paciente novo.
Node *create_node(Paciente *novoPaciente);

// Cria lista (vazia).
Lista *create_lista();

// Cria fila (vazia).
Fila *create_fila();

// Verifica se lista está vazia.
int list_is_empty(const Lista *L);

// Verifica se fila está vazia.
int fila_is_empty(const Fila *F);

// Adiciona elemento no começo da lista.
void add_no_inicio(Lista *L, Paciente *novoPaciente);

// Adiciona id no final da fila.
void enfileirar_id(Fila *F, int id);

// Adiciona registro no final da fila.
void enfileirar_registro(Fila *F, Registro *registro);

// Retira id no início da fila e o retorna.
int desenfileirar_id(Fila *F);

// Desenfileira registro.
void desenfileirar_registro(Fila *F);

// Criação de registro.
Registro *create_registro(const int id, const int tempo, const char condition[]);

// Criação de array de structs.
Occupation *create_array(int tamanho);

// Retorna ocupação de struct que contenha ocupação.
int get_occupation(Occupation *estrutura, const int i);

// Altera ocupação.
void change_occupation(Occupation *estrutura, const int i, int new_ocupation);

// Retorna a patologia de acordo com suas probabilidades.
char* condition();

// Função para imprimir fila para exame.
void print_fila(Fila *F);

// Função para imprimir struct Paciente.
void print_paciente(Paciente *p);

// Função para imprimir lista de pacientes.
void print_lista(Lista *l);

// Função para imprimir fila de laudo.
void print_fila_registro(Fila *F);

Tempos **create_array_tempos(int tamanho);


Tempos* create_tempos();


int tempo_laudo(Tempos *tempos);


#endif