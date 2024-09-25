#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "closedhash.h"

void resizeDictionary(StudDictionary *S){
    StudDictionary temp;
    
    Student* to_delete = S->data; 
    
    temp.data = malloc(sizeof(Student)*(S->max*2));
    temp.max = S->max*2;
    temp.count = 0;
    
    int hash;
    
    for (int i = 0; i < S->max; ++i){
        hash = getHash(S->data[i]);
        for (hash = getHash(S->data[i]); temp.data[hash].studID != Empty && S->data[i].studID != Deleted; hash = (hash+1) % temp.max){}
            temp.data[hash] = S->data[i];
            temp.count++;
    }
    *S = temp;
    free(to_delete);
}
int getHash(Student s){
    int hash = 0;

    for (int i = 0; i < 31; ++i){
        if (((s.studID >> i) & 1) == 1){
            hash += i+1;
        }
    }
    return hash % MAX;
}

void initDictionary(StudDictionary *S){
    S->data = malloc(sizeof(Student)*MAX);
    S->count = 0;
    S->max = MAX;
    for (int i = 0; i < MAX; ++i){
        S->data[i].studID = Empty;
    }
}

bool insertStudent(StudDictionary *S, Student stud){
    
    int hash = getHash(stud);
    
    if (S->count >= (S->max * 0.8)){
        resizeDictionary(S);
    }
    
    int i = hash;
    for (; S->data[i].studID != Empty; i = (i + 1) % S->max){
        if (S->data[i].studID == Deleted){
            break;
        }
        if (S->data[i].studID == stud.studID){
            printf("already exists\n");
            return false;
        } 
    }
    
    S->data[i] = stud;
    S->count++;
    return true;
        
    
    
}

bool removeStudent(StudDictionary *S, Student stud){
    int hash = getHash(stud);
    int i;
    for (i = hash; S->data[i].studID != Empty; i = (i + 1)% S->max){
            if (S->data[i].studID == stud.studID){
                S->data[i].studID = Deleted;
                S->count--;
            }
        }
}
void visualize(StudDictionary S){
    for (int i = 0; i < S.max; ++i){
        printf("Index: %d - ", i);
        if (S.data[i].studID != Deleted && S.data[i].studID != Empty){
            printf("%s - %d", S.data[i].studName, S.data[i].studID);
        } 
        printf("\n");
        
    }
}

Student getStudent(StudDictionary S, Student s){
    int hash = getHash(s);
    int i = hash;
    int not_start = 0;
    for (; S.data[i].studID != Empty; i = (i + 1)% S.max){
        if (s.studID == S.data[i].studID){
            return s;
        } 
        if (i == hash && not_start != 0){
            break;
        }
        not_start = 1;
    }
}
