#ifndef TP2_H
#define TP2_H
#include <stdbool.h>

typedef struct _paciente Paciente;

typedef struct _node Node;
typedef struct _list Lista;

typedef struct _fila Fila;
typedef struct _fila_node FilaNode;

typedef struct _aparelho Aparelho;

typedef struct _fila_node_registro NodeRegistro;
typedef struct _fila_registro FilaRegistro;
typedef struct _registro Registro;

Paciente *novo_paciente(const char nome[], const char cpf[], const int idade, const int id);

Node *create_node(Paciente *novoPaciente);

Lista *create_lista();

Fila *create_fila();

bool list_is_empty(const Lista *L);

bool fila_is_empty(const Fila *F);

void add_no_inicio(Lista *L, Paciente *novoPaciente);

void enfileirar_id(Fila *F, int id);

int desenfileirar(Fila *F);

Registro *create_registro(const int id, const int tempo, const int condition);

Aparelho *create_array();

int get_occupation(Aparelho *aparelhos, const int i);

void change_occupation(Aparelho *aparelhos, const int i, int new_ocupation);

int condition();

#endif