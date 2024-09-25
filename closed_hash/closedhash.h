#ifndef CLOSEDHASH_H
#define CLOSEDHASH_H

#include <stdbool.h>

#define MAX 10

typedef enum {Empty = 0, Deleted = -1} Flag;

typedef struct{
    int studID;
    char studName[20];
    bool sex;
    char program[8];
    int level;
} Student;

typedef struct{
    Student *data;
    int count;
    int max;
} StudDictionary;

int getHash(Student s);
void initDictionary(StudDictionary *S);
bool insertStudent(StudDictionary *S, Student stud);
void visualize(StudDictionary S);
Student getStudent(StudDictionary d, Student s);
bool removeStudent(StudDictionary *S, Student stud);
void resizeDictionary(StudDictionary *S);

#endif 