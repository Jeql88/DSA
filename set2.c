#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef int Set;

Set createSet();
bool addElement(Set* s, int item);
bool removeElement(Set* s, int item);
void displaySet(Set s);

Set unionSet(Set a, Set b);
Set intersectionSet(Set a, Set b);
Set differenceSet(Set a, Set b);
Set symmetricDifferenceSet(Set a, Set b);
int cardinality(Set s);
bool isElement(Set s, int item);

int main(){
    Set testSet = createSet();
    addElement(&testSet,3);
    addElement(&testSet,1);
    addElement(&testSet,2);
    addElement(&testSet,7);
    removeElement(&testSet,3);
    removeElement(&testSet,7);
    displaySet(testSet);
}

Set createSet(){
    Set x = 0;
    return x;
}

bool addElement(Set* s, int item){
    int x = 1;
    x = x << item;
    
    if ((*s >> item) == 1){
        return false;
    } 
    *s = x | *s;
    return true;
}

void displaySet(Set s){
    Set temp = s;
    for (int i = 0; temp > 0; ++i, temp = temp >> 1){
        if (temp & 1){
            printf("%d",i);
        }
    }
}

bool removeElement(Set *s, int item){
    int x = 1;
    x = x << item;
    // if (!(*s >> item)){
    //     return false;
    // } 
    *s = x ^ *s;
    return true;
}

