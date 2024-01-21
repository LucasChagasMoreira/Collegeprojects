#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h> // Inclui a declaração da função strcmp

int saldo = 0; // Declara a variável saldo como global

void separacao() {
 printf("\n--------------------------------\n\n");
}

void incrementasaldo() {
 // Incrementa o saldo
 saldo += 500;

 // Imprime o saldo
 printf("Saldo sendo incrementado: %d\n", saldo);

 // Imprime o número do processo atual
 printf("PID atual: %d\n", getpid());
}

void decrementasaldo() {
 // Decrementa o saldo
 saldo -= 500;

 // Imprime o saldo
 printf("Saldo sendo decrementado: %d\n", saldo);

 // Imprime o número do processo atual
 printf("PID atual: %d\n", getpid());
}

void exibesaldo() {
 // Imprime o saldo
 printf("Saldo: %d\n", saldo);

 // Imprime o número do processo atual
 printf("PID atual: %d\n", getpid());
}

int main() {
 // Cria os processos
 pid_t pid_incremento = fork();
 pid_t pid_decremento = fork();

 // Executa o código do processo pai
 if (pid_incremento == 0) {
   incrementasaldo();
   exit(0);
 } else if (pid_decremento == 0) {
   decrementasaldo();
   exit(0);
 }
 system("clear");
 // Loop principal
 char opcao;
 do {
   // Imprime o menu
   printf("Escolha uma opção:\n");
   printf(" + Para incrementar o saldo\n");
   printf(" - Para decrementar o saldo\n");
   printf(" E Para exibir o saldo\n");
   printf(" exit Para encerrar o programa\n");

   // Lê a opção do usuário
   scanf(" %s", &opcao);

   // Executa a ação correspondente à opção escolhida
   if (strcmp((char *)&opcao, "exit") == 0) {
     break;
   } else if (opcao == '+') {
     incrementasaldo();
   } else if (opcao == '-') {
     decrementasaldo();
   } else if (opcao == 'E') {
     // Cria o processo que irá imprimir o saldo
     pid_t pid_impressao = fork();

     // Executa o código do processo pai
     if (pid_impressao == 0) {
       // Imprime o saldo
       exibesaldo();
       exit(0);
     }
   } else {
     printf("Opção inválida.\n");
   }

   separacao();
   // Imprime o número do processo atual
   printf("PID atual: %d\n", getpid());
 } while (strcmp((char *)&opcao, "exit") != 0);

 // Aguarda o término dos processos filhos
 waitpid

