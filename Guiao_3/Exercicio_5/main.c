
#include <stdio.h>
#include <string.h>

#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

#define BUFFER_SIZE 256

int batch(char* comand, int* background){

    int fork_ret, exec_ret, status, ret;

    char* exec_args[20];
    char* string;
    int i = 0;

    // Parte o comand no executavel e seu argumentos
    string = strtok(comand, " ");

    while(string != 0){
        exec_args[i++] = string;
        string = strtok(NULL, " ");
    }

    string = strtok(exec_args[i-1], "\n");
    exec_args[i-1] = string;
    
    // Verifica se e para executar em Background
    if(strcmp(exec_args[i-1], "&") == 0){
        (*background)++;
        exec_args[--i] = NULL;
    }else
        exec_args[i] = NULL;

    if((fork_ret = fork()) == 0){
        exec_ret = execvp(exec_args[0], exec_args);
        _exit(exec_ret);
    }else{
        if(fork_ret != -1){
            waitpid(fork_ret, &status, 0);
            if(WIFEXITED(status))
                ret = WEXITSTATUS(status);
            else
                ret = -1;
        }else
            ret = -1;
    }

    return ret;

}

int main(int argc, char** argv){

    char buffer[BUFFER_SIZE];
    size_t bytes_read = 0;

    int background = 0;

    while((bytes_read = read(0, buffer, BUFFER_SIZE)) > 0){
        // Verifica se o utilizador inseriu o comando interno exit
        if(strstr(buffer, "exit") != NULL){
            break;
        }
        int ret = batch(buffer, &background);
        if(ret < 0){
            size_t comand_start = strlen("Error in bacth\n");
            write(2, "Error in bacth\n", comand_start);
        }
    }

    // Espera por todos o processos que estao em background
    for(int i = 0; i < background; i++){
        wait(NULL);
    }

    return 0;

}