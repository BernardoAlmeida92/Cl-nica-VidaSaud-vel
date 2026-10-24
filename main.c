#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Escala_médicos.h"
#include "Lista de pacientes.h"
#include "Sala_de_espera.h"

// Função auxiliar para limpar o buffer do teclado (evita problemas com scanf/fgets)
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função auxiliar para ler strings com espaços de forma segura
void ler_string(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        }
    }
}

void exibir_menu() {
    printf("\n=========================================\n");
    printf("         SISTEMA DE GESTAO MEDICA        \n");
    printf("=========================================\n");
    printf(" [CADASTRO GERAL DE PACIENTES]\n");
    printf("  1. Cadastrar paciente (entra de imediato na fila de espera)\n");
    printf("  2. Listar pacientes cadastrados\n");
    printf("  3. Buscar paciente por ID\n");
    printf("  4. Remover paciente do cadastro\n");
    printf("\n [ESCALA DE MEDICOS PLANTONISTAS]\n");
    printf("  5. Inserir medico na escala\n");
    printf("  6. Listar escala de plantonistas\n");
    printf("  7. Avancar plantao para o proximo\n");
    printf("  8. Remover medico do plantao atual\n");
    printf("\n [SALA DE ESPERA (FILA FIFO)]\n");
    printf("  9. Paciente entra na sala de espera\n");
    printf(" 10. Chamar proximo paciente para atendimento\n");
    printf(" 11. Paciente sai da fila (desistencia)\n");
    printf(" 12. Listar fila da sala de espera\n");
    printf("\n  0. Sair e liberar memoria\n");
    printf("=========================================\n");
    printf("Escolha uma opcao: ");
}

int main() {
    // Inicialização das estruturas de dados
    ListaPacientes *lista_pacientes = criar_lista_pacientes();
    EscalaMedicos *escala_medicos = criar_escala();
    SalaEspera *sala_espera = criar_sala_de_espera();

    int opcao;

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            printf("\nOpcao invalida! Digite apenas numeros.\n");
            limpar_buffer();
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1: {
                Paciente p;
                printf("\n--- Cadastrar Paciente ---\n");
                printf("Informe o ID do paciente: ");
                scanf("%d", &p.id);
                limpar_buffer();

                // Verifica se o paciente já está cadastrado
                Paciente existente;
                if (buscar_paciente_por_id(lista_pacientes, p.id, &existente)) {
                    printf("Aviso: Paciente com ID %d ja cadastrado (%s).\n", p.id, existente.nome);
                    printf("Encaminhando para a sala de espera...\n");
                    entrar_na_fila(sala_espera, existente);
                    break;
                }

                printf("Informe o Nome do paciente: ");
                ler_string(p.nome, sizeof(p.nome));

                // Cadastra na lista geral e coloca de imediato na fila da sala de espera
                inserir_paciente(lista_pacientes, p);
                entrar_na_fila(sala_espera, p);

                printf("Paciente cadastrado com sucesso e inserido na fila de espera!\n");
                break;
            }

            case 2:
                listar_pacientes(lista_pacientes);
                break;

            case 3: {
                int id;
                Paciente p;
                printf("\n--- Buscar Paciente ---\n");
                printf("Informe o ID a pesquisar: ");
                scanf("%d", &id);
                limpar_buffer();

                if (buscar_paciente_por_id(lista_pacientes, id, &p)) {
                    printf(">> Paciente encontrado! ID: %d | Nome: %s\n", p.id, p.nome);
                } else {
                    printf(">> Paciente com ID %d nao encontrado.\n", id);
                }
                break;
            }

            case 4: {
                int id;
                printf("\n--- Remover Paciente ---\n");
                printf("Informe o ID a remover: ");
                scanf("%d", &id);
                limpar_buffer();

                remover_paciente_por_id(lista_pacientes, id);
                break;
            }

            case 5: {
                Medico m;
                printf("\n--- Inserir Medico na Escala ---\n");
                printf("Informe o CRM / ID do medico: ");
                scanf("%d", &m.id);
                limpar_buffer();

                printf("Informe o Nome do medico: ");
                ler_string(m.nome, sizeof(m.nome));

                inserir_medico(escala_medicos, m);
                printf("Medico inserido na escala com sucesso!\n");
                break;
            }

            case 6:
                listar_escala(escala_medicos);
                break;

            case 7:
                printf("\n--- Avancando Plantao ---\n");
                avancar_plantao(escala_medicos);
                break;

            case 8:
                printf("\n--- Remover Medico Atual do Plantao ---\n");
                remover_medico_atual(escala_medicos);
                break;

            case 9: {
                int id;
                Paciente p;
                printf("\n--- Entrar na Sala de Espera ---\n");
                printf("Informe o ID do paciente ja cadastrado: ");
                scanf("%d", &id);
                limpar_buffer();

                if (buscar_paciente_por_id(lista_pacientes, id, &p)) {
                    entrar_na_fila(sala_espera, p);
                } else {
                    printf("Paciente nao encontrado no cadastro geral. Deseja cadastrar agora? (1-Sim / 0-Nao): ");
                    int cad;
                    scanf("%d", &cad);
                    limpar_buffer();
                    if (cad == 1) {
                        p.id = id;
                        printf("Informe o Nome do paciente: ");
                        ler_string(p.nome, sizeof(p.nome));
                        inserir_paciente(lista_pacientes, p);
                        entrar_na_fila(sala_espera, p);
                    } else {
                        printf("Operacao cancelada.\n");
                    }
                }
                break;
            }

            case 10:
                if (escala_medicos->plantonista_atual != NULL) {
                    printf("\nPlantonista atual em atendimento: Dr(a). %s\n", escala_medicos->plantonista_atual->medico.nome);
                } else {
                    printf("\n[Aviso] Nenhum medico na escala de plantao no momento.\n");
                }
                chamar_proximo(sala_espera);
                break;

            case 11:
                printf("\n--- Desistencia da Sala de Espera ---\n");
                sair_da_fila(sala_espera);
                break;

            case 12:
                printf("\n--- Pacientes Aguardando na Sala de Espera ---");
                listar_pacientes(sala_espera->fila_pacientes);
                break;

            case 0:
                printf("\nEncerrando o sistema e liberando memoria...\n");
                break;

            default:
                printf("\nOpcao inexistente. Tente novamente.\n");
                break;
        }

    } while (opcao != 0);

    // Desalocação completa de memória de todas as estruturas
    destruir_lista_pacientes(lista_pacientes);
    destruir_escala(escala_medicos);
    destruir_sala_de_espera(sala_espera);

    printf("Memoria liberada com sucesso. Programa finalizado!\n");
    return 0;
}
