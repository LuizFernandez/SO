
#include <stdio.h>
#include <string.h>

#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

int mysystem(char* comand){

    int fork_ret, exec_ret, status, res;

    char* exec_args[20];
    char* string;
    int i = 0;

    string = strtok(comand, " ");

    // Partir a string em argumentos e executavel
    while (string != NULL){
        exec_args[i++] = string;
        string = strtok(NULL, " ");
    }
    
    exec_args[i] = NULL;

    // Criar filho para evitar terminaçao do pai
    if((fork_ret = fork()) == 0){
        // Executar exec e guardar o valor de retorno em caso de erro para ser usado para terminar filho
        exec_ret = execvp(exec_args[0], exec_args);
        _exit(exec_ret);
    }else{
        if(fork_ret != -1){
            // Esperar que o filho termine atraves do seu pid
            waitpid(fork_ret, &status, 0);

            if(WIFEXITED(status)){
                res = WEXITSTATUS(status);
            }else{
                res = -1;
            }
        }else{
            res = -1;
        }
    }

    return res;
}

int main(int argc, char** argv){

    char comand1[] = "ls -l -a -h";
    char comand2[] = "sleep 1";
    char comand3[] = "ps";

    int ret;

    size_t comand_start = strlen("Begining comand 1!!\n");
    write(1, "Begining comand 1!!\n", comand_start);
    ret = mysystem(comand1);
    printf("Ret: %d\n", ret);

    comand_start = strlen("Begining comand 2!!\n");
    write(1, "Begining comand 2!!\n", comand_start);
    ret = mysystem(comand2);
    printf("Ret: %d\n", ret);

    comand_start = strlen("Begining comand 3!!\n");
    write(1, "Begining comand 3!!\n", comand_start);
    ret = mysystem(comand3);
    printf("Ret: %d\n", ret);
    

    return 0;
}