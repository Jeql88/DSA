#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} *BST, *NodePtr;

typedef struct nodeA {
    NodePtr data;
    struct nodeA* link;
} *NodeAPtr;

typedef struct {
    NodeAPtr head;
    NodeAPtr tail;
} Queue;


void breadthFS(BST b){
    Queue q;
    
    NodeAPtr temp = malloc(sizeof(struct nodeA));
    temp->data = b;
    
    q.head = temp;
    q.tail = temp;
    
    while (q.head != NULL){
        printf("%d ", q.head->data->data);
        if (q.head->data->left != NULL){
            temp = malloc(sizeof(struct nodeA));
            temp->data = q.head->data->left;
            if (q.head == NULL){
                q.head = temp;
            } else{
                q.tail->link = temp;
            }
            q.tail = temp;
        }
        if (q.head->data->right != NULL){
            temp = malloc(sizeof(struct nodeA));
            temp->data = q.head->data->right;
            if (q.head == NULL){
                q.head = temp;
            } else{
                q.tail->link = temp;
            }
            q.tail = temp;
        }
        NodeAPtr toDel = q.head;
        q.head = q.head->link;
        free(toDel);
    }
    

    
  
}

void insertBST(BST* b, int data){
    NodePtr *trav = b;
    
    while (*trav != NULL && (*trav)->data != data){
        trav = (((*trav)->data) > data) ? &(*trav)->left : &(*trav)->right;
    }
    if (*trav == NULL){
        *trav = calloc(1,sizeof(struct node));
        (*trav)->data = data;
    }
}

void inorder(BST b){
    if (b != NULL){
        inorder(b->left);
        printf("%d ",b->data);
        inorder(b->right);
    }
}

void main(){
    BST b = NULL;
    insertBST(&b,5);
    insertBST(&b,6);
    insertBST(&b,4);
    insertBST(&b,2);
    insertBST(&b,9);
    insertBST(&b,15);
    insertBST(&b,12);
    // inorder(b);
    breadthFS(b);
}