
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#define ROWS 10
#define COLUMNS 10000

int main(int argc, char** argv){

    srand(457);
    int matrix[ROWS][COLUMNS];
    size_t line_error = strlen("Generating Matrix...\n");
    write(1, "Generating Matrix...\n", line_error);

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            matrix[i][j] = rand() % COLUMNS;
        }
    }

    int num = rand() % COLUMNS;

    pid_t* pids = malloc(sizeof(pid_t) * ROWS);

    for(int i = 0; i < ROWS; i++){
        pid_t fpid;
        if((fpid = fork()) == 0){
            for(int j = 0; j < COLUMNS; j++)
                if(matrix[i][j] == num){
                    _exit(j); 
                }
            _exit(-1);
        }else{
            pids[i] = fpid;
        }
    }

    int status;

    for(int i = 0; i < ROWS; i++){
        waitpid(pids[i], &status, 0);  
        if(WEXITSTATUS(status) >= 0)
            printf("Process %d returned the value %d in the Colum %d\n", (i+1), num, WEXITSTATUS(status));
    }

    return 0;
}