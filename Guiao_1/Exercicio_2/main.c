
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char** argv){

    size_t buffer_size = 1024;
    ssize_t bytes_read;

    char* buffer = malloc(sizeof(char) * buffer_size);

    while((bytes_read = read(0, buffer, buffer_size)) > 0){
        ssize_t bytes_writed = write(1, buffer, bytes_read);
        if(bytes_writed < 0){
            perror("Falta de memoria");
            return -1;
        }
    }

    return 0;
}
