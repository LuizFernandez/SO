
#include <stdio.h>

#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

int main(int argc, char** argv){

    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("Meu: %d;\nPai: %d;\n", pid, ppid);

    return 0;
}