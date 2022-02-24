#ifndef _PERSON_H_
#define _PERSON_H_

#define FILENAME "file_pessoas"

struct person{
    char name[200];
    int age;
};

typedef struct person Person;

int new_person(char* name, int age, int* pos);
int person_change_age(char* name, int age);
int person_change_age_v2(int registo, int age);

#endif