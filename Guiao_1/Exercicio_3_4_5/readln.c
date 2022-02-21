#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <string.h>

#define MAX_BUF 1024

ssize_t readln1(int fd_input, char *line, size_t size){
    ssize_t i = 0;

    while(i < size - 1){
        ssize_t bytes_read = read(fd_input, &line[i], 1);
        if(bytes_read <= 0) break;
        if(line[i++] == '\n') break;
    }

    line[i] = 0;
    return i;
}

ssize_t readln2(int fd_input, char *line, size_t size){
    ssize_t bytes_read = read(fd_input, line, size);
    if(!bytes_read) return 0;

    size_t line_length = strcspn(line, "\n") + 1;
    if(bytes_read < line_length) line_length = bytes_read;
    line[line_length] = 0;

    lseek(fd_input, line_length - bytes_read, SEEK_CUR);
    return line_length;
}