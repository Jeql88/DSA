#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct {
    int elems[MAX];
    int count;
} MinHeap;

void insertMinHeap(MinHeap* h, int elem);
void display(MinHeap h);
void deleteMinHeap(MinHeap* h);

void main(){
    MinHeap myHeap;
    myHeap.count = 0;
    insertMinHeap(&myHeap,69);
    insertMinHeap(&myHeap,7);
    insertMinHeap(&myHeap,25);
    insertMinHeap(&myHeap,19);
    insertMinHeap(&myHeap,40);
    
    insertMinHeap(&myHeap,8);
    insertMinHeap(&myHeap,35);
    insertMinHeap(&myHeap,1);
    insertMinHeap(&myHeap,4);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
    
    deleteMinHeap(&myHeap);
    display(myHeap);
}

void insertMinHeap(MinHeap* h, int elem){
    int i;
    for (i = h->count; i > 0 && h->elems[(i-1)/2] > elem; i = (i-1)/2){
        h->elems[i] = h->elems[(i-1)/2];
    }
    h->elems[i] = elem;
    h->count++;
}

void deleteMinHeap(MinHeap* h){
    int i = 0;
    // h->elems[0] = h->elems[h->count--];
    // solution 1
    // while (1){
    //     if (i*2 + 1 < h->count && i*2 + 2 < h->count){
    //         if (h->elems[i*2 + 1] < h->elems[i*2 + 2]){
    //             h->elems[i] = h->elems[i*2 + 1];
    //             i = i*2 + 1;
    //         } else {
    //             h->elems[i] = h->elems[i*2 + 2];
    //             i = i*2 + 2;
    //         }
    //     } else{
    //         break;
    //     }
    // }
    h->count--;
    for (; i*2 + 1 < h->count ;){
        if (i*2 + 2 < h->count){
            if (h->elems[i*2+1] > h->elems[h->count] && h->elems[i*2+2] > h->elems[h->count]){
                break;
            } else if (h->elems[i*2+1] < h->elems[i*2+2]){
                h->elems[i] = h->elems[i*2+1];
                i = i*2+1;
            } else {
                h->elems[i] = h->elems[i*2+2];
                i = i*2+2;
            }
        } else if (i*2 + 1 < h->count){
            if (h->elems[i*2+1] > h->elems[h->count]){
                break;
            } else {
                h->elems[i] = h->elems[i*2+1];
                i = i*2+1;
            }
        } 
    }
    h->elems[i] = h->elems[h->count];
}
void display(MinHeap h){
    for (int i = 0; i < h.count; ++i){
        printf("%d ",h.elems[i]);
    }
    printf("\n");
}