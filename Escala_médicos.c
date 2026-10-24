#include "Escala_médicos.h"
#include <stdlib.h>
#include <stdio.h>

EscalaMedicos* criar_escala() {
    EscalaMedicos *escala = (EscalaMedicos*) malloc(sizeof(EscalaMedicos));
    escala->plantonista_atual = NULL;
    escala->total_medicos = 0;
    return escala;
}

// Insere um novo médico na roda
void inserir_medico(EscalaMedicos *escala, Medico m) {
    NoMedico *novo = (NoMedico*) malloc(sizeof(NoMedico));
    novo->medico = m;

    if (escala->plantonista_atual == NULL) {
        // Lista vazia: o médico aponta para si próprio e torna-se o plantonista
        novo->prox = novo;
        escala->plantonista_atual = novo;
    } else {
        // Insere o novo médico antes do plantonista atual (no "final" do ciclo)
        NoMedico *aux = escala->plantonista_atual;
        while (aux->prox != escala->plantonista_atual) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->prox = escala->plantonista_atual;
    }
    escala->total_medicos++;
}

// Passa o plantão para o próximo médico da lista circular
void avancar_plantao(EscalaMedicos *escala) {
    if (escala->plantonista_atual != NULL) {
        escala->plantonista_atual = escala->plantonista_atual->prox;
        printf("Plantao avancado. O novo plantonista e: %s\n", escala->plantonista_atual->medico.nome);
    } else {
        printf("Nenhum medico na escala.\n");
    }
}

// Remove o médico que está atualmente de plantão
void remover_medico_atual(EscalaMedicos *escala) {
    if (escala->plantonista_atual == NULL) return;

    NoMedico *alvo = escala->plantonista_atual;

    if (alvo->prox == alvo) { 
        // Apenas um médico na escala
        escala->plantonista_atual = NULL;
    } else {
        // Procura o médico anterior para ajustar o ponteiro
        NoMedico *anterior = escala->plantonista_atual;
        while (anterior->prox != alvo) {
            anterior = anterior->prox;
        }
        
        anterior->prox = alvo->prox;
        // O próximo médico assume o plantão automaticamente
        escala->plantonista_atual = alvo->prox; 
    }
    
    printf("Medico %s removido da escala.\n", alvo->medico.nome);
    free(alvo);
    escala->total_medicos--;
}

// Lista todos a partir do plantonista da vez (exigência do enunciado)
void listar_escala(EscalaMedicos *escala) {
    if (escala->plantonista_atual == NULL) {
        printf("A escala esta vazia.\n");
        return;
    }

    NoMedico *q = escala->plantonista_atual;
    printf("\n--- Escala de Medicos (Plantonista Atual: %s) ---\n", q->medico.nome);
    
    // O laço do-while é a melhor abordagem para listas circulares
    do {
        printf("CRM: %d | Nome: %s", q->medico.id, q->medico.nome);
        if (q == escala->plantonista_atual) {
            printf(" [DE PLANTAO]");
        }
        printf("\n");
        q = q->prox;
    } while (q != escala->plantonista_atual);
    
    printf("---------------------------------------------------\n");
}

void destruir_escala(EscalaMedicos *escala) {
    if (escala->plantonista_atual != NULL) {
        NoMedico *q = escala->plantonista_atual->prox;
        NoMedico *aux;
        
        while (q != escala->plantonista_atual) {
            aux = q;
            q = q->prox;
            free(aux);
        }
        free(escala->plantonista_atual); // Liberta o último nó
    }
    free(escala); // Liberta o TAD
}