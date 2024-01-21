#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int saldo = 0;
pthread_mutex_t mutex;

pthread_t get_tid() {
  return pthread_self();
}

void *incrementar_saldo(void *arg) {
  pthread_t tid = get_tid();
  printf("[TID %lu]: Pegando o mutex\n", (long)tid);
  pthread_mutex_lock(&mutex);
  printf("[TID %lu]: Incrementando o saldo em 500\n", (long)tid);
  saldo += 500;
  pthread_mutex_unlock(&mutex);
  printf("[TID %lu]: Liberando o mutex\n", (long)tid);
  return NULL;
}


void *decrementar_saldo(void *arg) {
  pthread_t tid = get_tid();
  printf("[TID %lu]: Pegando o mutex\n", (long)tid);
  pthread_mutex_lock(&mutex);
  printf("[TID %lu]: Decrementando o saldo em 500\n", (long)tid);
  saldo -= 500;
  pthread_mutex_unlock(&mutex);
  printf("[TID %lu]: Liberando o mutex\n", (long)tid);
  return NULL;
}

void *imprimir_saldo(void *arg) {
  pthread_t tid = get_tid();
  printf("[TID %lu]: Pegando o mutex\n", (long)tid);
  pthread_mutex_lock(&mutex);
  printf("[TID %lu]: Imprimindo o saldo: %d\n", (long)tid, saldo);
  pthread_mutex_unlock(&mutex);
  printf("[TID %lu]: Liberando o mutex\n", (long)tid);
  return NULL;
}



int main() {
    pthread_t thread1,thread2,thread3;
    pthread_mutex_init(&mutex, NULL);

    char operacao[10];

    while (1) {
        printf("Digite a operação (+ para incrementar, - para decrementar, E para exibir o saldo, ou 'exit' para sair): ");
        scanf("%s", operacao);

        if (strcmp(operacao, "+") == 0) {
            pthread_create(&thread1, NULL, incrementar_saldo, NULL);
            pthread_join(thread1, NULL);
        } else if (strcmp(operacao, "-") == 0) {
            pthread_create(&thread2, NULL, decrementar_saldo, NULL);
            pthread_join(thread2, NULL);
        } else if (strcmp(operacao, "E") == 0) {
            pthread_create(&thread3, NULL, imprimir_saldo, NULL);
            pthread_join(thread3, NULL);
        } else if (strcmp(operacao, "exit") == 0) {
            break;
        } else {
            printf("Operação invalida!\n");
        }
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}
