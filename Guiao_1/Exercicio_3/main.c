
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#define BUFFER_SIZE 1024

char buffer_aux[1024];
size_t bytes_testes = 0;
size_t bytes_read_aux = 0;

ssize_t readln(int fd, char *line, size_t size){

    size_t temp = 0;

    if(bytes_testes < bytes_read_aux){
        int i = 0;
        while(bytes_testes < bytes_read_aux && buffer_aux[bytes_testes] != '\n' && bytes_read_aux > 0){
            line[i++] = buffer_aux[bytes_testes++];
        }
        if(buffer_aux[bytes_testes] == '\n'){
            line[i++] = buffer_aux[bytes_testes++];
            line[i] = '\0';
            if(bytes_testes >= bytes_read_aux)
                bytes_read_aux = 0;
            return i;
        }else{
            bytes_read_aux = 0;
            temp = i;
        }
    }

    bytes_read_aux = read(fd, buffer_aux, size);
    bytes_testes = 0;

    while(bytes_testes < bytes_read_aux && buffer_aux[bytes_testes] != '\n' && bytes_read_aux > 0){
        line[temp++] = buffer_aux[bytes_testes++];
    }

    if(buffer_aux[bytes_testes] == '\n'){
        line[temp++] = buffer_aux[bytes_testes++];
        line[temp] = '\0';
    }

    return temp;
}

int main(int argc, char** argv){

    if(argc != 2){
        size_t line_error = strlen("Wrong number of arguments\n");
        write(2, "Wrong number of arguments\n", line_error);
        return -1;
    }else{
        int f_input = open(argv[1], O_RDONLY);
        if(f_input < 0){
            size_t line_error = strlen("Error on Open: No such file ou directory\n");
            write(2, "Error on Open: No such file ou directory\n", line_error);
            return -1;
        }

        ssize_t bytes_read;

        char* buffer = malloc(sizeof(char) * BUFFER_SIZE);
        while((bytes_read = readln(f_input, buffer, BUFFER_SIZE)) > 0){
            write(1, buffer, bytes_read);
        }

        free(buffer);
        close(f_input);
    }

    return 0;
}
