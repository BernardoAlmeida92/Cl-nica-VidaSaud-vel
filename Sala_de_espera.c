#include "Sala_de_espera.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializa a sala de espera com sua fila (FIFO) e o nó organizador
SalaEspera* criar_sala_de_espera() {
    SalaEspera *sala = (SalaEspera*) malloc(sizeof(SalaEspera));
    sala->fila_pacientes = criar_lista_pacientes();
    // O organizador aponta inicialmente para o nó cabeça da lista
    sala->organizador = sala->fila_pacientes->cabeca;
    return sala;
}

// Insere o paciente no final da fila (o último a entrar é o último a ser atendido)
void entrar_na_fila(SalaEspera *sala, Paciente p) {
    if (sala == NULL || sala->fila_pacientes == NULL) {
        printf("Erro: Sala de espera nao inicializada.\n");
        return;
    }

    No *novo = (No*) malloc(sizeof(No));
    novo->paciente = p;
    novo->prox = NULL;

    // Garante que o organizador aponte para o último nó
    if (sala->organizador == NULL) {
        sala->organizador = sala->fila_pacientes->cabeca;
        while (sala->organizador->prox != NULL) {
            sala->organizador = sala->organizador->prox;
        }
    }

    // Inserção no final em O(1) através do organizador
    sala->organizador->prox = novo;
    sala->organizador = novo;
    sala->fila_pacientes->tamanho++;

    printf("Paciente '%s' (ID: %d) entrou na sala de espera. [Posicao na fila: %d]\n",
           p.nome, p.id, sala->fila_pacientes->tamanho);
}

// Remove o primeiro paciente da fila (quem entrou primeiro sai primeiro - FIFO)
void sair_da_fila(SalaEspera *sala) {
    if (sala == NULL || sala->fila_pacientes == NULL || sala->fila_pacientes->tamanho == 0 || sala->fila_pacientes->cabeca->prox == NULL) {
        printf("A sala de espera esta vazia. Nenhum paciente na fila.\n");
        return;
    }

    // O primeiro paciente da fila é o nó logo após o nó cabeça
    No *remover = sala->fila_pacientes->cabeca->prox;
    sala->fila_pacientes->cabeca->prox = remover->prox;
    sala->fila_pacientes->tamanho--;

    // Se a fila esvaziou, o organizador volta a apontar para o nó cabeça
    if (sala->fila_pacientes->cabeca->prox == NULL) {
        sala->organizador = sala->fila_pacientes->cabeca;
    }

    printf("Paciente '%s' (ID: %d) saiu da fila de espera.\n",
           remover->paciente.nome, remover->paciente.id);
    free(remover);
}

// Chama o próximo paciente respeitando a regra FIFO: quem entrou primeiro é atendido primeiro
void chamar_proximo(SalaEspera *sala) {
    if (sala == NULL || sala->fila_pacientes == NULL || sala->fila_pacientes->tamanho == 0 || sala->fila_pacientes->cabeca->prox == NULL) {
        printf("Nenhum paciente aguardando na sala de espera.\n");
        return;
    }

    // Identifica o primeiro paciente da fila
    No *proximo = sala->fila_pacientes->cabeca->prox;
    printf("\n=========================================\n");
    printf("         CHAMADA PARA ATENDIMENTO        \n");
    printf("=========================================\n");
    printf("Proximo paciente da vez: %s (ID: %d)\n", proximo->paciente.nome, proximo->paciente.id);
    printf("Dirija-se ao consultorio do medico plantonista.\n");
    printf("=========================================\n");

    // Realiza o atendimento e remove o paciente da fila de espera
    sair_da_fila(sala);
}

// Libera toda a memória alocada para a sala de espera
void destruir_sala_de_espera(SalaEspera *sala) {
    if (sala != NULL) {
        if (sala->fila_pacientes != NULL) {
            destruir_lista_pacientes(sala->fila_pacientes);
        }
        free(sala);
    }
}
