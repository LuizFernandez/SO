
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "readln.h"

#include <errno.h>

int main(int argc, char* argv[]){

    char line[1024];

    int fd_input;
    if((fd_input = open(argv[1], O_RDONLY)) == -1){
        printf("Msg: %s, Nr: %d\n", strerror(errno), errno);
        perror("Erro no Open Input");
        return -1;
    }

    clock_t start = clock();
    size_t size;
    
    int i = 1;
    while((size = readln2(fd_input, line, 1024))) {
        char linenumb[100];
        sprintf(linenumb, "%*d  ", 6, i++);
        write(1, linenumb, strlen(linenumb));
        write(1, line, size);
    }

    printf("\n\nExecution time (version %d) = %lf s\n", 2, (double)(clock() - start) / CLOCKS_PER_SEC);
    
    close(fd_input);

    return 0;
}