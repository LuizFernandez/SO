
#include <stdio.h>

#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

int main(int argc, char** argv){

    pid_t f_pid;
    pid_t pid;
    pid_t ppid;

    if((f_pid = fork()) == 0){
        pid = getpid();
        ppid = getppid();

        printf("(FILHO)\nMeu: %d;\nPai: %d;\n", pid, ppid);
    }else{
        pid = getpid();
        ppid = getppid();

        printf("(PAI)\nMeu: %d;\nPai: %d;\nFilho: %d\n", pid, ppid, f_pid);
    }
    return 0;
}