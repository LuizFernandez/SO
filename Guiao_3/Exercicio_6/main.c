
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */

int main(int argc, char** argv){

    pid_t fork_ret;
    int n_argc = argc-1;

    int* times = (int *)calloc(n_argc, sizeof(int));
    bool complet[n_argc];
    pid_t pids[n_argc];
    int status[n_argc];

    for(int i = 0; i < n_argc; i++){
        complet[i] = false;
    }

    while(1){
        for(int i = 0; i < argc; i++){
            if(!complet[i]){
                if((fork_ret = fork()) == 0){
                    execlp(argv[i+1], argv[i+1], NULL);
                    _exit(0);
                }else{
                    if(fork_ret != -1)
                        pids[i] = fork_ret;
                }
            }
        }

        for(int i = 0; i < n_argc; i++){
            if(!complet[i]){
                waitpid(pids[i], &status[i], 0);
                if(WIFEXITED(status[i])){
                    int time_temp = WEXITSTATUS(status[i]);
                    if(time_temp != 0){
                        times[i]++;
                    }
                }
            }
        }

        bool done = true;

        for (int i = 0; i < n_argc; i++) {
            if(!complet[i]){
                if (WIFEXITED(status[i])) {
                    if (WEXITSTATUS(status[i]) != 0) {
                        done = false;
                    }else{
                        complet[i] = true;
                    }
                } else {
                    done = false;
                }
            }
        }

        if (done) {
            break;
        }

    }

    for(int i = 0; i < n_argc; i++){
        printf("%s %d \n", argv[i+1], times[i]);
    }

    free(times);


    return 0;
}

// Falta verificar se ja atingiu zero ou nao