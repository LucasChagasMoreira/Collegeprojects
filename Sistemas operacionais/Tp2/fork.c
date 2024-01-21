#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>

void draw_line() {
    printf("\n");
}

void display_menu() {
    printf("Increase : + \n");
    printf("Decrease: -\n");
    printf("Show balance: s\n");
    printf("Exit: 0\n");
}

char read_user_choice() {
    char user_input[300];
    fgets(user_input, 300, stdin);
    user_input[strlen(user_input) - 1] = '\0';

    if (strlen(user_input) > 1) return 'X';

    return user_input[0];
}

#define NUM_PROCESSES 3
#define CHILD_PROCESS 0
#define BALANCE_CHANGE 500

pid_t create_process(){
    pid_t pid = fork();
    if(pid == -1){
        printf("Error while forking\n");
        exit(1);
    }
    return pid;
}

void kill_processes(pid_t * process_pids, int total_processes){
    for(int i = 0; i < total_processes; i++){
        kill(process_pids[i], SIGKILL);
    }
}

void message_and_process_pid(char * message, pid_t pid){
    draw_line();
    printf("%s by process with PID: %d\n", message, pid);
    draw_line();
}

void increase_balance(int * parent_to_child_pipe, int * child_to_parent_pipe){
    int balance = 0;
    while(1){
        read(parent_to_child_pipe[0], &balance, sizeof(balance));
        message_and_process_pid("Increasing balance", getpid());
        balance += BALANCE_CHANGE;
        write(child_to_parent_pipe[1], &balance, sizeof(balance));
    }
}

void decrease_balance(int * parent_to_child_pipe, int * child_to_parent_pipe){
    int balance;
    while(1){
        read(parent_to_child_pipe[0], &balance, sizeof(balance));
        message_and_process_pid("Decreasing balance", getpid());
        balance -= BALANCE_CHANGE;
        write(child_to_parent_pipe[1], &balance, sizeof(balance));
    }
}

void show_balance(int * parent_to_child_pipe, int * child_to_parent_pipe){
    int balance;
    while(1){
        read(parent_to_child_pipe[0], &balance, sizeof(balance));

        char * text = "Balance of %d units being displayed";
        char result[150];
        sprintf(result, text, balance);

        message_and_process_pid(result, getpid());

        write(child_to_parent_pipe[1], &balance, sizeof(balance));
    }
}

typedef struct Process{
    pid_t process_pids[NUM_PROCESSES];

    int increment_parent_to_child[2], increment_child_to_parent[2];
    int decrement_parent_to_child[2], decrement_child_to_parent[2];
    int read_parent_to_child[2], read_child_to_parent[2];

} Process;

void execute_commands(Process * processes) {
    char operation = '_';
    int balance = 0;

    while (operation != '0') {
        display_menu();
        operation = read_user_choice();

        if(operation == '+'){       
            write(processes->increment_parent_to_child[1], &balance, sizeof(balance));
            read(processes->increment_child_to_parent[0], &balance, sizeof(balance));
        }
        else if(operation == '-'){
            write(processes->decrement_parent_to_child[1], &balance, sizeof(balance));
            read(processes->decrement_child_to_parent[0], &balance, sizeof(balance));

        }
        else if(operation == 's'){
            write(processes->read_parent_to_child[1], &balance, sizeof(balance));
            read(processes->read_child_to_parent[0], &balance, sizeof(balance));
        }        
    }
}

int main() {
    Process processes;

    if (pipe(processes.increment_child_to_parent) == -1 || pipe(processes.decrement_child_to_parent) == -1
    ||  pipe(processes.increment_parent_to_child) == -1 || pipe(processes.decrement_parent_to_child) == -1
    ||  pipe(processes.read_parent_to_child) == -1 || pipe(processes.read_child_to_parent) == -1) {
        perror("Error creating pipes");
        exit(EXIT_FAILURE);
    }

    pid_t pid_increase = create_process();
    processes.process_pids[0] = pid_increase;
    if(pid_increase == 0) increase_balance(processes.increment_parent_to_child, processes.increment_child_to_parent);
    else if(pid_increase == -1)return EXIT_FAILURE;

    pid_t pid_decrease = create_process();
    processes.process_pids[1] = pid_decrease;
    if(pid_decrease == 0) decrease_balance(processes.decrement_parent_to_child, processes.decrement_child_to_parent);
    else if(pid_decrease == -1){
        kill_processes(processes.process_pids, 1);
        return EXIT_FAILURE;
    }

    pid_t pid_display = create_process();
    processes.process_pids[2] = pid_display;
    if(pid_display == 0) show_balance(processes.read_parent_to_child, processes.read_child_to_parent);
    else if(pid_display == -1){
        kill_processes(processes.process_pids, 2);
        return EXIT_FAILURE;
    }    

    execute_commands(&processes);

    kill_processes(processes.process_pids, 3);

    return 0;
}
