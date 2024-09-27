#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont = 0;

typedef struct Tarefa {
    int id;
    char descricao[256];
    struct Tarefa* next;
    struct Tarefa* prev;
} Tarefa;


typedef struct ListaDeTarefas {
    Tarefa* head;
    Tarefa* tail;
} ListaDeTarefas;

ListaDeTarefas* CriarListaDeTarefas() {
    ListaDeTarefas* lista = (ListaDeTarefas*)malloc(sizeof(ListaDeTarefas));
    lista->head = NULL;
    lista->tail = NULL;
    return lista;
}


void InserirTarefa(ListaDeTarefas* lista, int id, const char* descricao) {
    Tarefa* novaTarefa = (Tarefa*)malloc(sizeof(Tarefa));
    novaTarefa->id = id;
    strncpy(novaTarefa->descricao, descricao, 256);
    novaTarefa->next = NULL;
    novaTarefa->prev = lista->tail;

    if (lista->tail) {
        lista->tail->next = novaTarefa;
    } else {
        lista->head = novaTarefa;
    }
    lista->tail = novaTarefa;
    cont++;
}


void removerTarefa(ListaDeTarefas* lista, int id) {
    Tarefa* tarefaAtual = lista->head;

    while (tarefaAtual) {
        if (tarefaAtual->id == id) {
            if (tarefaAtual->prev) {
                tarefaAtual->prev->next = tarefaAtual->next;
            } else {
                lista->head = tarefaAtual->next; 
            }
            if (tarefaAtual->next) {
                tarefaAtual->next->prev = tarefaAtual->prev;
            } else {
                lista->tail = tarefaAtual->prev;
            }
            free(tarefaAtual);
            return;
        }
        tarefaAtual = tarefaAtual->next;
    }
}


Tarefa* encontrarTarefa(ListaDeTarefas* lista, int id) {
    Tarefa* tarefaAtual = lista->head;

    while (tarefaAtual) {
        if (tarefaAtual->id == id) {
            return tarefaAtual;
        }
        tarefaAtual = tarefaAtual->next;
    }
    return NULL;
}


void imprimirTarefa(Tarefa * tarefas) {
    if (tarefas) {
        printf("ID: %d, Descricao: %s\n", tarefas->id, tarefas->descricao);
    } else {
        printf("Tarefa não encontrada.\n");
    }
}


void ImprimirTodasAsTarefas(ListaDeTarefas* lista) { 
    Tarefa* tarefaAtual = lista->head; 
    if (!tarefaAtual) { 
        printf("Não tem tarefas na lista.\n");
        return;
    } 
    printf("Todas as tarefas:\n"); 
    while (tarefaAtual) {
        imprimirTarefa(tarefaAtual);
        tarefaAtual = tarefaAtual->next; 
    }  
}


int main() {
    ListaDeTarefas* minhaTarefa = CriarListaDeTarefas();
    int option = 0;

    while (1) { 
        printf("GERENCIADOR DE TAREFAS\n\n");
        printf("1 - INSERIR UMA TAREFA\n");
        printf("2 - REMOVER UMA TAREFA\n");
        printf("3 - ENCONTRAR UMA TAREFA PELO ID\n");
        printf("4 - LISTAR TODAS AS TAREFAS\n");
        printf("5 - SAIR\n");
        printf("Escolha uma opção: ");
        scanf("%d", &option);

        switch (option) {
        case 1: {
            char str[256];  
            printf("\nDigite a descrição da tarefa:\n");
            scanf(" %[^\n]s", str);
            printf("\n**Inserindo uma Tarefa**\n"); 
            InserirTarefa(minhaTarefa, cont, str);
            printf("\nNova tarefa criada\n");
            Tarefa* task = encontrarTarefa(minhaTarefa, cont - 1); 
            printf("----------------------\n");
            imprimirTarefa(task);
            break;
        }
        case 2: {
            int remocao = 0;
            printf("\nDigite o ID da tarefa que deseja excluir\n");
            scanf("%d", &remocao);
            printf("\n**Removendo uma Tarefa**\n");
            
            removerTarefa(minhaTarefa, remocao);
            break;
        }
        case 3: {
            int idTarefa = 0;
            printf("\nDigite o ID da tarefa que deseja encontrar\n");
            printf("\n**Procurando uma Tarefa**\n");
            scanf("%d", &idTarefa);
            printf("\n------------------------\n");
            Tarefa* task = encontrarTarefa(minhaTarefa, idTarefa);
            imprimirTarefa(task);
            break;
        }
        case 4:
            printf("\nMostrando todas as Tarefas\n");
            ImprimirTodasAsTarefas(minhaTarefa);
            break;
        case 5: {
            
            Tarefa* current = minhaTarefa->head;
            while (current) {
                Tarefa* toFree = current;
                current = current->next;
                free(toFree);
            }
            free(minhaTarefa);
            return 0; 
        }
        default:
            printf("\nValor incorreto.\n");
            break;
        }
    }

    return 0;
}
