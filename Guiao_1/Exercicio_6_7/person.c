
#include <string.h>
#include <stdlib.h>
#include "person.h"

#include <sys/types.h>
#include <unistd.h> /* chamadas ao sistema: defs e decls essenciais */
#include <fcntl.h>  /* O_RDONLY, O_WRONLY, O_CREAT, O_* */

#include <errno.h>

int new_person(char* name, int age, int* pos){

    int res;

    Person p;
    strcpy(p.name, name);
    p.age = age;

    int fd_file;
    if(( fd_file = open(FILENAME, O_CREAT | O_APPEND | O_WRONLY,0600)) == -1){
        printf("Msg: %s, Nr: %d\n", strerror(errno), errno);
        perror("Erro no Open Input");
        return -1;
    }

    res = write(fd_file, &p, sizeof(Person));
    if(res < 0){
        perror("Error creating person");
        return -1;
    }

    int pseek = lseek(fd_file, -sizeof(Person), SEEK_CUR);
    pseek /= sizeof(Person);
    *pos = pseek;

    close(fd_file);
    
    return res;

}

int person_change_age(char* name, int age){

    int res;
    Person p;

    int fd_file;
    if(( fd_file = open(FILENAME, O_CREAT | O_WRONLY)) == -1){
        printf("Msg: %s, Nr: %d\n", strerror(errno), errno);
        perror("Erro no Open Input");
        return -1;
    }

    while((res = read(fd_file, &p, sizeof(Person))) > 0 && strcmp(p.name, name) != 0);

    if(res != -1){
        p.age = age;
        lseek(fd_file, -sizeof(Person), SEEK_CUR);
    }

    res = write(fd_file, &p, sizeof(Person));

    if(res < 0){
        perror("Error creating person");
        return -1;
    }

    close(fd_file);

    return 0;

}

int person_change_age_v2(int registo, int age){

    int fd_file;
    if(( fd_file = open(FILENAME, O_CREAT | O_WRONLY)) == -1){
        printf("Msg: %s, Nr: %d\n", strerror(errno), errno);
        perror("Erro no Open Input");
        return -1;
    }

    int pseek = lseek(fd_file, registo * sizeof(Person), SEEK_SET);

    Person p;
    int res = read(fd_file, &p, sizeof(Person));
    if(res < 0){
        perror("Error creating person");
        return -1;
    }

    p.age = age;

    lseek(fd_file, -sizeof(Person), SEEK_CUR);
    res = write(fd_file, &p, sizeof(Person));

    if(res < 0){
        perror("Error creating person");
        return -1;
    }

    close(fd_file);

    return 0;
}
