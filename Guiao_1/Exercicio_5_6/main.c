
#include "person.h"

int main(int argc, char** argv){

    if(argc == 4){
        if(strcmp("-i", argv[1]) == 0){
            int registo = new_person(argv[2], atoi(argv[3]));
            printf("Registo %d\n", registo);
        }else if(strcmp("-u", argv[1]) == 0){
            person_change_age(argv[2], atoi(argv[3]));
        }else if(strcmp("-o", argv[1]) == 0){
            person_change_age_v2(atoi(argv[2]), atoi(argv[3]));
        }
    }
    

    return 0;
}