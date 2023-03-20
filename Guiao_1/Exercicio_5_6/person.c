
#include "person.h"

int new_person(char* name, int age){

    Person p;
    strcpy(p.name, name);
    p.age = age;

    int f_input = open(FILENAME, O_CREAT | O_RDWR | O_APPEND, 0640);
    if(f_input < 0){
        size_t line_error = strlen("Error open file\n");
        write(2, "Error open file\n", line_error);
        return -1;
    }

    int res = write(f_input, &p, sizeof(Person));
    if(res < 0){
        size_t line_error = strlen("Error creating person\n");
        write(2, "Error creating person\n", line_error);
        return -1;
    }

    int file_size = lseek(f_input, -(sizeof(Person)), SEEK_END);
    int registo = file_size / sizeof(Person);

    close(f_input);

    return registo;

}

int person_change_age(char* name, int age){

    int fd = open(FILENAME, O_RDWR , 0640);
    if(fd < 0){
        size_t line_error = strlen("Error open file\n");
        write(2, "Error open file\n", line_error);
        return -1;
    }

    Person p;
    ssize_t bytes_read;
    int res;

    while((bytes_read = read(fd, &p, sizeof(Person))) > 0){
        if (strcmp(p.name, name) == 0){
            p.age = age;
            res = lseek(fd, -(sizeof(Person)), SEEK_CUR);
            if(res < 0){
                size_t line_error = strlen("Error lseek\n");
                write(2, "Error lseek\n", line_error);
                return -1;
            }

            res = write(fd, &p, sizeof(Person));
            if(res < 0){
                size_t line_error = strlen("Error write\n");
                write(2, "Error write\n", line_error);
                return -1;
            }
        }
    }

    close(fd);

    return 0;
}

int person_change_age_v2(long pos, int age){

    int fd = open(FILENAME, O_RDWR , 0640);
    if(fd < 0){
        size_t line_error = strlen("Error open file\n");
        write(2, "Error open file\n", line_error);
        return -1;
    }

    size_t person_location = pos * sizeof(Person);
    int res = lseek(fd, person_location, SEEK_SET);
    if(res < 0){
        size_t line_error = strlen("Error lseek\n");
        write(2, "Error lseek\n", line_error);
        return -1;
    }

    Person p;
    ssize_t bytes_read = read(fd, &p, sizeof(Person));
    if(bytes_read < 0){
        size_t line_error = strlen("Error read\n");
        write(2, "Error read\n", line_error);
        return -1;
    }
    p.age = age;
    res = lseek(fd, -(sizeof(Person)), SEEK_CUR);
    if(res < 0){
        size_t line_error = strlen("Error lseek\n");
        write(2, "Error lseek\n", line_error);
        return -1;
    }
    
    res = write(fd, &p, sizeof(Person));
    if(res < 0){
        size_t line_error = strlen("Error write\n");
        write(2, "Error write\n", line_error);
        return -1;
    }
    
    close(fd);

    return 0;

}
