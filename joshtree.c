#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<stdbool.h>


typedef struct node {
    int data;
    struct node* left;
    struct node* right;
    struct node* link;
} *BST, *NodePtr;


typedef struct {
    struct node* head;
    struct node* tail;
} Queue;


void breadthFS(BST b){
    Queue q;
    q.head = b;
    q.tail = b;
    
    while (q.head != NULL){
        printf("%d ",q.head->data);
        if (q.head->left != NULL){
            if (q.head == NULL){
                q.head = q.head->left;
            } else {
                q.tail->link = q.head->left;
            }
            q.tail = q.head->left;
        }
        if (q.head->right != NULL){
            if (q.head == NULL){
                q.head = q.head->right;
            } else {
                q.tail->link = q.head->right;
            }
            q.tail = q.head->right;
        }
        q.head = q.head->link;
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
    // inorder(b);
    breadthFS(b);
}