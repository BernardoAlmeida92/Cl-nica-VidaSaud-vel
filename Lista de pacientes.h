#ifndef LISTA_PACIENTES_H
#define LISTA_PACIENTES_H

// 1. O dado em si
typedef struct {
    int id;
    char nome[100];
} Paciente;

// 2. O Nó da Lista
typedef struct no {
    Paciente paciente;
    struct no *prox;
} No;

// 3. O TAD encapsulado (Substitui a necessidade de usar No** no main)
typedef struct {
    No *cabeca;   // Ponteiro para o seu "nó cabeça" (dummy node)
    int tamanho;  // O contador que antes ficava em p->dado
} ListaPacientes;

// Assinaturas adaptadas para o contexto da clínica
ListaPacientes* criar_lista_pacientes();
void inserir_paciente(ListaPacientes *lista, Paciente p);
int buscar_paciente_por_id(ListaPacientes *lista, int id, Paciente *retorno);
void remover_paciente_por_id(ListaPacientes *lista, int id);
void listar_pacientes(ListaPacientes *lista);
void destruir_lista_pacientes(ListaPacientes *lista);

#endif