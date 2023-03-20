
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h> /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

int main(int argc, char** argv){

    if (argc != 3){
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

        int f_output = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0640);
        if(f_output < 0){
            size_t line_error = strlen("Error on Open: No such file ou directory\n");
            write(2, "Error on Open: No such file ou directory\n", line_error);
            return -1;
        }
        
        size_t buffer_size = 1024;
        ssize_t bytes_readed = 0;

        char* buffer = malloc(sizeof(char) * buffer_size);

        while((bytes_readed = read(f_input, buffer, buffer_size)) > 0){
            ssize_t bytes_writed = write(f_output, buffer, bytes_readed);
            if(bytes_writed < 0){
                perror("Falta de Memoria");
                return -1;
            }
        } 

        free(buffer);

        close(f_input);
        close(f_output);
    }

    return 0;
}