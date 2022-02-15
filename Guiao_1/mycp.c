
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <errno.h>

#define MAX_BUF 1024*1024

/*----------------------------------Exercicio 1----------------------------------*/
int main(int argc, char* argv[]){

    //Memoria Estatica
    char buffer[MAX_BUF];

    int fd_input, fd_output;

    if((fd_input = open(argv[1], O_RDONLY)) == -1){
        printf("Msg: %s, Nr: %d\n", strerror(errno), errno);
        perror("Erro no Open Input");
        return -1;
    }

    if((fd_output = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0640)) == -1){
        perror("Erro no Open Output");
        return -1;
    }

    int bytes_read;

    while((bytes_read = read(fd_input, buffer, MAX_BUF)) > 0)
        write(fd_output, buffer, bytes_read);

    close(fd_input);
    close(fd_output);

    return 0;

}