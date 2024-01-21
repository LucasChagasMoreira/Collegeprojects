#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>
int mail = 0;

void* routine(){
    for(int i = 0; i<1000000; i++){
        mail++;
    }
}

void* routine2(){
    printf("%d\n",2*mail);
}

int main(){
    pthread_t p1,p2;

    pthread_create(&p1,NULL, &routine, NULL);
    pthread_create(&p2,NULL, &routine2, NULL);
    
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
}