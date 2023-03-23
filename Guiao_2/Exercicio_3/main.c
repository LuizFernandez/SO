
#include <stdio.h>

#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

int main(int argc, char** argv){

    int status;

    for(int i = 1; i <= 10; i++){
        pid_t fpid;
        if((fpid = fork()) == 0){
            pid_t pid = getpid();
            pid_t ppid = getppid();

            printf("(Filho %d)\nMeu: %d;\nPai: %d;\n", i, pid, ppid);
            _exit(i); 
        }else{
            wait(&status);
            if(WIFEXITED(status))
                printf("%d\n", WEXITSTATUS(status));
        }
    }
    return 0;
}