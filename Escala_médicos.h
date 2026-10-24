#ifndef ESCALA_MEDICOS_H
#define ESCALA_MEDICOS_H

// 1. A estrutura do Médico
typedef struct {
    int id;
    char nome[100];
} Medico;

// 2. O Nó da Lista Circular
typedef struct no_medico {
    Medico medico;
    struct no_medico *prox;
} NoMedico;

// 3. O TAD Encapsulado
typedef struct {
    NoMedico *plantonista_atual; // Aponta sempre para o médico que está a trabalhar agora
    int total_medicos;
} EscalaMedicos;

// Assinaturas das funções exigidas pelo projeto
EscalaMedicos* criar_escala();
void inserir_medico(EscalaMedicos *escala, Medico m);
void avancar_plantao(EscalaMedicos *escala);
void remover_medico_atual(EscalaMedicos *escala);
void listar_escala(EscalaMedicos *escala);
void destruir_escala(EscalaMedicos *escala);

#endif