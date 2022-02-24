
#include "person.h"

int main(int argc, char* argv[]){

    char* name = strdup(argv[2]);
    int age = atoi(argv[3]);
    int pos;

    if(strcmp(argv[1], "-i") == 0){
        new_person(name, age, &pos);
        printf("registo %d", pos);
    }else if(strcmp(argv[1], "-u") == 0)
        person_change_age(name, age);
    else if(strcmp(argv[1], "-o") == 0)
        person_change_age_v2(atoi(argv[2]),age);
    else{
        printf("Opção invalida!!\n");
    }

    return 0;
}