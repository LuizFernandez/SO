
#include <stdio.h>
#include <string.h>

#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

int main(int argc, char** argv){

    if(argc > 1){
        pid_t fpid;
        for(int i = 1; i < argc; i++){
            if((fpid = fork()) == 0){
                int res = execlp(argv[i], argv[i], NULL);
                if(res < 0){
                    printf("RES: %d\n", res);
                }
            }
        }

        for(int i = 1; i < argc; i++){
            int status;
            wait(&status);
            if(WIFEXITED(status)){
                printf("OK: %d\n", WEXITSTATUS(status));
            }
        }
    }else{
        size_t line_error = strlen("Wrong number of elements!!\n");
        write(2, "Wrong number of elements!!\n", line_error);
        return -1;
    }

    return 0;
}