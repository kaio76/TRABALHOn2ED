#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont = 0;
// Estrutura da tarefa
typedef struct Task {
    int id;
    char description[256];
    struct Task* next;
    struct Task* prev;
} Task;

// Estrutura da lista de tarefas
typedef struct TaskList {
    Task* head;
    Task* tail;
} TaskList;

// Função para criar uma nova lista de tarefas
TaskList* createTaskList() {
    TaskList* list = (TaskList*)malloc(sizeof(TaskList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Função para inserir uma nova tarefa
void insertTask(TaskList* list, int id, const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = id;
    strncpy(newTask->description, description, 256);
    newTask->next = NULL;
    newTask->prev = list->tail;

    if (list->tail) {
        list->tail->next = newTask;
    } else {
        list->head = newTask; // Se a lista estava vazia, a nova tarefa é o head
    }
    list->tail = newTask;
    cont++;
}

// Função para remover uma tarefa
void removeTask(TaskList* list, int id) {
    Task* current = list->head;

    while (current) {
        if (current->id == id) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                list->head = current->next; // Se for o head, atualiza o head
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev; // Se for o tail, atualiza o tail
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

// Função para encontrar uma tarefa
Task* findTask(TaskList* list, int id) {
    Task* current = list->head;

    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Função para imprimir uma tarefa
void printTask(Task* task) {
    if (task) {
        printf("ID: %d, Description: %s\n", task->id, task->description);
    } else {
        printf("Task not found.\n");
    }
}

// Função para imprimir todas as tarefas
void printAllTasks(TaskList* list) { 
    Task* current = list->head; 
    if (!current) { 
        printf("No tasks in the list.\n");
        return;
    } 
    printf("All tasks:\n"); 
    while (current) {
        printTask(current);
        current = current->next; 
    }  
}

// Função principal
int main() {
    TaskList* myTasks = createTaskList();
    int option = 0;

    while (1) { // Loop para manter o menu ativo
        printf("GERENCIADOR DE TAREFAS\n");
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
            printf("Digite a descrição da tarefa:\n");
            printf("**Inserindo uma task**\n");
            scanf(" %[^\n]s", str); // Lê a string incluindo espaços
            insertTask(myTasks, cont, str);
            printf("Nova tarefa criada\n");
            Task* task = findTask(myTasks, cont - 1); // id deve ser cont - 1
            printf("----------------------\n");
            printTask(task);
            break;
        }
        case 2: {
            int remocao = 0;
            printf("Digite o ID da tarefa que deseja excluir\n");
            printf("**Removendo uma task**\n");
            scanf("%d", &remocao);
            removeTask(myTasks, remocao);
            break;
        }
        case 3: {
            int idTarefa = 0;
            printf("Digite o ID da tarefa que deseja encontrar\n");
            printf("**Procurando uma task**\n");
            scanf("%d", &idTarefa);
            printf("------------------------\n");
            Task* task = findTask(myTasks, idTarefa);
            printTask(task);
            break;
        }
        case 4:
            printf("Mostrando todas as tasks\n");
            printAllTasks(myTasks);
            break;
        case 5: {
            // Libera todos os nós antes de sair
            Task* current = myTasks->head;
            while (current) {
                Task* toFree = current;
                current = current->next;
                free(toFree);
            }
            free(myTasks);
            return 0; // Sai do programa
        }
        default:
            printf("Valor incorreto.\n");
            break;
        }
    }

    return 0;
}#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cont = 0;
// Estrutura da tarefa
typedef struct Task {
    int id;
    char description[256];
    struct Task* next;
    struct Task* prev;
} Task;

// Estrutura da lista de tarefas
typedef struct TaskList {
    Task* head;
    Task* tail;
} TaskList;

// Função para criar uma nova lista de tarefas
TaskList* createTaskList() {
    TaskList* list = (TaskList*)malloc(sizeof(TaskList));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

// Função para inserir uma nova tarefa
void insertTask(TaskList* list, int id, const char* description) {
    Task* newTask = (Task*)malloc(sizeof(Task));
    newTask->id = id;
    strncpy(newTask->description, description, 256);
    newTask->next = NULL;
    newTask->prev = list->tail;

    if (list->tail) {
        list->tail->next = newTask;
    } else {
        list->head = newTask; // Se a lista estava vazia, a nova tarefa é o head
    }
    list->tail = newTask;
    cont++;
}

// Função para remover uma tarefa
void removeTask(TaskList* list, int id) {
    Task* current = list->head;

    while (current) {
        if (current->id == id) {
            if (current->prev) {
                current->prev->next = current->next;
            } else {
                list->head = current->next; // Se for o head, atualiza o head
            }
            if (current->next) {
                current->next->prev = current->prev;
            } else {
                list->tail = current->prev; // Se for o tail, atualiza o tail
            }
            free(current);
            return;
        }
        current = current->next;
    }
}

// Função para encontrar uma tarefa
Task* findTask(TaskList* list, int id) {
    Task* current = list->head;

    while (current) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Função para imprimir uma tarefa
void printTask(Task* task) {
    if (task) {
        printf("ID: %d, Description: %s\n", task->id, task->description);
    } else {
        printf("Task not found.\n");
    }
}

// Função para imprimir todas as tarefas
void printAllTasks(TaskList* list) { 
    Task* current = list->head; 
    if (!current) { 
        printf("No tasks in the list.\n");
        return;
    } 
    printf("All tasks:\n"); 
    while (current) {
        printTask(current);
        current = current->next; 
    }  
}

// Função principal
int main() {
    TaskList* myTasks = createTaskList();
    int option = 0;

    while (1) { // Loop para manter o menu ativo
        printf("GERENCIADOR DE TAREFAS\n");
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
            printf("Digite a descrição da tarefa:\n");
            printf("**Inserindo uma task**\n");
            scanf(" %[^\n]s", str); // Lê a string incluindo espaços
            insertTask(myTasks, cont, str);
            printf("Nova tarefa criada\n");
            Task* task = findTask(myTasks, cont - 1); // id deve ser cont - 1
            printf("----------------------\n");
            printTask(task);
            break;
        }
        case 2: {
            int remocao = 0;
            printf("Digite o ID da tarefa que deseja excluir\n");
            printf("**Removendo uma task**\n");
            scanf("%d", &remocao);
            removeTask(myTasks, remocao);
            break;
        }
        case 3: {
            int idTarefa = 0;
            printf("Digite o ID da tarefa que deseja encontrar\n");
            printf("**Procurando uma task**\n");
            scanf("%d", &idTarefa);
            printf("------------------------\n");
            Task* task = findTask(myTasks, idTarefa);
            printTask(task);
            break;
        }
        case 4:
            printf("Mostrando todas as tasks\n");
            printAllTasks(myTasks);
            break;
        case 5: {
            // Libera todos os nós antes de sair
            Task* current = myTasks->head;
            while (current) {
                Task* toFree = current;
                current = current->next;
                free(toFree);
            }
            free(myTasks);
            return 0; // Sai do programa
        }
        default:
            printf("Valor incorreto.\n");
            break;
        }
    }

    return 0;
}