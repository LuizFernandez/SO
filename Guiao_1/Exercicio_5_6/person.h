#ifndef _PERSON_H_
#define _PERSON_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h>

#define FILENAME "Pessoas"

typedef struct person{
    char name[200];
    int age;
}Person;

int new_person(char* name, int age);
int person_change_age(char* name, int age);
int person_change_age_v2(long pos, int age);

#endif