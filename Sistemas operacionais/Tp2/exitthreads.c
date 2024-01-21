#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg) {
    printf("Thread em execucao...\n");
    sleep(3); 
    printf("Thread concluida.\n");
    return NULL;
}

int main() {
    pthread_t thread_id;
    int ret;

    ret = pthread_create(&thread_id, NULL, thread_function, NULL);
    if (ret != 0) {
        printf("Erro ao criar a thread.\n");
        exit(EXIT_FAILURE);
    }

    ret = pthread_join(thread_id, NULL);
    if (ret != 0) {
        printf("Erro ao aguardar a thread.\n");
        exit(EXIT_FAILURE);
    }
    printf("pthread_join: Thread concluida.\n");

    ret = pthread_kill(thread_id, SIGKILL);
    if (ret != 0) {
        printf("Erro ao enviar o sinal para a thread.\n");
        exit(EXIT_FAILURE);
    }
    printf("pthread_kill: Sinal enviado para a thread.\n");

    pthread_exit(NULL);
    printf("pthread_exit: Thread terminada explicitamente.\n");

    return 0;
}
