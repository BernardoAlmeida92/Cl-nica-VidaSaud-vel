#ifndef SALA_DE_ESPERA_H
#define SALA_DE_ESPERA_H

#include "Lista de pacientes.h"

typedef struct {
    ListaPacientes *fila_pacientes;
    No *organizador;
} SalaEspera;

SalaEspera* criar_sala_de_espera();
void entrar_na_fila(SalaEspera *sala, Paciente p);
void sair_da_fila(SalaEspera *sala);
void chamar_proximo(SalaEspera *sala);
void destruir_sala_de_espera(SalaEspera *sala);

#endif
