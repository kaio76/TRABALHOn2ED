#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarefa {
    int valor;
    char descricao[256];
    struct tarefa *next;
    struct tarefa *prev;
} Tarefa;

void InserirTarefa(Tarefa **lista, int id, const char* descricao) {
    Tarefa *novo = malloc(sizeof(Tarefa));
    if(novo) {
        novo->valor = id;
        strncpy(novo->descricao, descricao, 256);
        novo->next = *lista;
        novo->prev = NULL;
        if(*lista) {
            (*lista)->prev = novo;
        }
        *lista = novo;
    } else {
        printf("Erro ao alocar a memória\n");
    }
}

Tarefa* buscarTarefa(Tarefa **lista, int id) {
    Tarefa *aux, *tarefa = NULL;
    aux = *lista;

    while(aux && aux->valor != id) {
        aux = aux->next;
    }
    if(aux) {
        tarefa = aux;
    }
    return tarefa;
}

Tarefa* remover(Tarefa **lista, int id) {
    Tarefa *aux = NULL;
    Tarefa *remover = NULL;
    if(*lista) {
        if((*lista)->valor == id) {
            remover = *lista;
            *lista = remover->next;
            if(*lista) {
                (*lista)->prev = NULL;
            }
        } else {
            aux = *lista;
            while(aux->next && aux->next->valor != id) {
                aux = aux->next;
            }
            if(aux->next) {
                remover = aux->next;
                aux->next = remover->next;
                if(aux->next) {
                    aux->next->prev = aux;
                }
            }
        }
    }
    return remover;
}

void imprimirTarefas(Tarefa *tarefa) {
    printf("\n TAREFAS:\n\n");
    while(tarefa) {
        printf("ID: %d, Descricao: %s\n", tarefa->valor, tarefa->descricao);
        tarefa = tarefa->next;
    }
    printf("\n");
}

int main() {
    Tarefa *buscar, *removido, *lista = NULL;
    int opcao;
    int id;
    char str[256];
    do {
        printf("\nLISTA DE TAREFAS\n1 - Inserir Tarefa\n2 - Remover Tarefa\n3 - Buscar Tarefa\n4 - Listar Tarefas\n0 - Sair\n");
        scanf("%d", &opcao);
        switch(opcao) {
            case 1:
                printf("Digite o ID: \n");
                scanf("%d", &id);
                printf("\nDigite a descrição da tarefa:\n");
                scanf(" %[^\n]s", str);
                InserirTarefa(&lista, id, str);
                printf("Tarefa Criada:\nID: %d | Descrição: %s\n", lista->valor, lista->descricao);
                printf("\nNova tarefa criada com sucesso\n");
                break;
            case 2:
                printf("Digite o ID da tarefa para remover: \n");
                scanf("%d", &id);
                removido = remover(&lista, id);
                if(removido) {
                    printf("Tarefa removida:\nID: %d | Descrição: %s\n", removido->valor, removido->descricao);
                    free(removido);
                } else {
                    printf("Elemento Inexistente\n");
                }
                break;
            case 3:
                printf("Digite o ID do tarefa para busca: \n");
                scanf("%d", &id);
                buscar = buscarTarefa(&lista, id);
                if(buscar) {
                    printf("Tarefa Encontrado:\nID: %d | Descrição: %s\n", buscar->valor, buscar->descricao);
                } else {
                    printf("Elemento Inexistente\n");
                }
                break;
            case 4:
                imprimirTarefas(lista);
                break;
            default:
                if(opcao != 0) {
                    printf("Valor invalido");
                }
        }
    } while(opcao != 0);
}
