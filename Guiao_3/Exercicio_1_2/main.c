
#include <stdio.h>

#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

int main(int agrc, char** argv){

    pid_t fpid;
    
    // Fork porque se o exec for chamado na main, neste caso no processo pai, ao terminar
    // a sua execuçao, o programa ira terminar independente se ha mais codigo ou nao
    if((fpid = fork()) == 0){
        int res = execl("/bin/ls", "ls", "-l", NULL);

        if(res < 0){
            printf("RES: %d\n", res);
        }
    }else{
        int status;
        wait(&status);
        if(WIFEXITED(status)){
            printf("OK: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}