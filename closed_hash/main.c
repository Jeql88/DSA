#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "closedhash.h"


void main(){
    Student josh = {10,"Josh",true,"BSIT",2};
    Student jansen = {2,"Jansen",true,"BSIT",2};
    Student jio = {3,"Jio",true,"BSIT",2};
    Student jio2 = {4,"Jio2",true,"BSIT",2};
    Student jio3 = {5,"Jio3",true,"BSIT",2};
    
    Student jio5 = {6,"Jio5",true,"BSIT",2};
    Student jio6 = {7,"Jio6",true,"BSIT",2};
    Student jio7 = {8,"Jio7",true,"BSIT",2};
    
    Student jio1 = {1,"Jio8",true,"BSIT",2};
    
    StudDictionary list;
    initDictionary(&list);
    
    insertStudent(&list,jio3);
    insertStudent(&list,josh);
    insertStudent(&list,jansen);
    insertStudent(&list,jio2);
    
    insertStudent(&list,jio);
    insertStudent(&list,jio5);
    insertStudent(&list,jio6);
    insertStudent(&list,jio7);
    insertStudent(&list,jio1);
    // Student temp = getStudent(list,jio);
    // printf("test %d - %s",temp.studID, temp.studName);
    // removeStudent(&list,jio3);
    visualize(list);
}


