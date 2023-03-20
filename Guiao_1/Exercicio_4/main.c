
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
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
        while(bytes_testes < bytes_read_aux && buffer_aux[bytes_testes] != '\n'){
            line[i++] = buffer_aux[bytes_testes++];
        }
        if(buffer_aux[bytes_testes] == '\n'){
            line[i++] = buffer_aux[bytes_testes++];
            line[i] = '\0';
            if(bytes_testes >= bytes_read_aux)
                bytes_testes = 0;
            return i;
        }else{
            bytes_testes = 0;
            temp = i;
        }
    }

    bytes_read_aux = read(fd, buffer_aux, size);
    
    while(bytes_testes < bytes_read_aux && buffer_aux[bytes_testes] != '\n'){
        line[temp++] = buffer_aux[bytes_testes++];
    }

    if(buffer_aux[bytes_testes] == '\n'){
        line[temp++] = buffer_aux[bytes_testes++];
        line[temp] = '\0';
    }

    return temp;
}

int main(int argc, char** argv){

    ssize_t bytes_read;
    int newline = 1;
    int line_counter = 1;

    char* buffer = malloc(sizeof(char) * BUFFER_SIZE);

    while((bytes_read = readln(0, buffer, BUFFER_SIZE)) > 0){

        char line_number[10] = "";
        if(newline && buffer[0] != '\n'){
            snprintf(line_number, 10, "     %d  ", line_counter);
            write(1, line_number, sizeof(line_number));
            line_counter++;
        }

        write(1, buffer, bytes_read);

        if(buffer[bytes_read - 1] != '\n'){
            newline = 0;
        }else{
            newline = 1;
        }  
    }

        free(buffer);

        return 0;
}