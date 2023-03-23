
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

    for(int i = 0; i < ROWS; i++){
        pid_t fpid;
        if((fpid = fork()) == 0){
            for(int j = 0; j < COLUMNS; j++)
                if(matrix[i][j] == num)
                    _exit(1); 
            _exit(0);
        }
    }

    int occor = 0;
    int status;

    while(wait(&status) != -1){
        if(WEXITSTATUS(status) == 1)
            occor++;
    }

    printf("%d ocurrences of %d were found!\n", occor, num);

    return 0;
}