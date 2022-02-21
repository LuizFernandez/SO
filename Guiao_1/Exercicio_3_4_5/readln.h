#ifndef _READ_LN_H_
#define _READ_LN_H_

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

ssize_t readln1(int fd_input, char *line, size_t size);
ssize_t readln2(int fd_input, char *line, size_t size);

#endif