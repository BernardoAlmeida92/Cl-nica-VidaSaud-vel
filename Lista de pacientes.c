#include "Lista de pacientes.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Adaptado do seu criar_lista()
ListaPacientes* criar_lista_pacientes() {
    ListaPacientes *lista = (ListaPacientes*) malloc(sizeof(ListaPacientes));
    lista->cabeca = (No*) malloc(sizeof(No)); // Nó cabeça (dummy node)
    lista->cabeca->prox = NULL;
    lista->tamanho = 0;
    return lista;
}

// Adaptado do seu adicionar_final()
void inserir_paciente(ListaPacientes *lista, Paciente p) {
    No *q = (No*) malloc(sizeof(No));
    q->paciente = p;
    q->prox = NULL;
    
    No *aux = lista->cabeca;
    // Percorre até o último nó
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    
    aux->prox = q;
    lista->tamanho++; // Substitui o seu p->dado++
}

// Adaptado do seu imprimir_lista()
void listar_pacientes(ListaPacientes *lista) {
    if (lista->tamanho == 0) {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }
    
    No *q;
    printf("\n--- Lista de Pacientes ---\n");
    for (q = lista->cabeca->prox; q != NULL; q = q->prox) {
        printf("ID: %d | Nome: %s\n", q->paciente.id, q->paciente.nome);
    }
    printf("--------------------------\n");
}

// Adaptado do seu buscar_valor()
// Retorna 1 se achou e preenche o ponteiro 'retorno', ou 0 se não achou
int buscar_paciente_por_id(ListaPacientes *lista, int id, Paciente *retorno) {
    No *p = lista->cabeca->prox;
    while (p != NULL) {
        if (p->paciente.id == id) {
            *retorno = p->paciente; // Copia os dados para retorno
            return 1; 
        }
        p = p->prox;
    }
    return 0; 
}

// Adaptado do seu remover_valor()
void remover_paciente_por_id(ListaPacientes *lista, int id) {
    No *q = lista->cabeca;
    
    while (q->prox != NULL) {
        if (q->prox->paciente.id == id) {
            break;
        }
        q = q->prox;
    }
    
    if (q->prox == NULL) {
        printf("Erro: Paciente com ID %d nao encontrado.\n", id);
        return;
    }
    
    No *tmp = q->prox;
    q->prox = tmp->prox;
    free(tmp);
    lista->tamanho--; // Substitui o seu p->dado--
    printf("Paciente ID %d removido com sucesso.\n", id);
}

// Adaptado da sua destruição iterativa
void destruir_lista_pacientes(ListaPacientes *lista) {
    No *atual = lista->cabeca;
    No *proximo;
    
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    free(lista); // Libera também o TAD gerenciador
}