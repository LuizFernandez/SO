
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <sys/wait.h> /* chamadas wait*() e macros relacionadas */

#define ROWS 10
#define COLUMNS 10000

#define FILENAME "Matrix"

int genMatrix(){

    int fp = open(FILENAME, O_CREAT | O_WRONLY, 0640);
    if(fp < 0){
        size_t line_error = strlen("Error open file\n");
        write(2, "Error open file\n", line_error);
        return -1;
    }

    srand(457);
    int matrix[ROWS][COLUMNS];
    size_t line_error = strlen("Generating Matrix...\n");
    write(1, "Generating Matrix...\n", line_error);

    for(int i = 0; i < ROWS; i++){
        for(int j = 0; j < COLUMNS; j++){
            matrix[i][j] = rand() % COLUMNS;
            int res;
            res = write(fp, &matrix[i][j], sizeof(int));
            if(res < 0){
                size_t line_error = strlen("Error Write\n");
                write(2, "Error Write\n", line_error);
                return -1;
            }
        }
    }

    close(fp);

    return 0;

}

int main(int argc, char** argv){

    genMatrix();

    int fp = open(FILENAME, O_RDONLY, 0640);
    if(fp < 0){
        size_t line_error = strlen("Error open file\n");
        write(2, "Error open file\n", line_error);
        return -1;
    }

    int num = rand() % COLUMNS;

    pid_t* pids = malloc(sizeof(pid_t) * ROWS);

    for(int i = 0; i < ROWS; i++){
        pid_t fpid;
        if((fpid = fork()) == 0){
            int vetor[COLUMNS];
            int res = read(fp, vetor, sizeof(int) * COLUMNS);
            if(res < 0){
                size_t line_error = strlen("Error Read\n");
                write(2, "Error Read\n", line_error);
                return -1;
            }
            for(int j = 0; j < COLUMNS; j++)
                if(vetor[j] == num){
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

    close(fp);

    return 0;
}