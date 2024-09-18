#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Data.h"
#include "Stack.h"

bool addProductBaseOnExpiry(Inventory *i, Product p) {
    // To do code logic here.
    NodePtr temp = malloc(sizeof(struct node));
    temp->link = NULL;
    temp->prod = p;
    
    NodePtr tempStack = NULL;
    NodePtr holder = NULL;
    
    if (temp != NULL && temp->prod.prodQty + i->currQty <= 100){
        while (i->top != NULL && dateDifference(i->top->prod.expiry, p.expiry)>= 0){
            holder = i->top;
            i->top = i->top->link;
            holder->link = tempStack;
            tempStack = holder;
        }
        temp->link = i->top;
        i->top = temp;
        i->currQty += temp->prod.prodQty;
        while (tempStack != NULL){
            holder = tempStack;
            tempStack = tempStack->link;
            holder->link = i->top;
            i->top = holder;
        }
        return true;
    }
    return false;
}

int main() {
    ProductList myProd;
    int numCount, selection;

    printf("Enter sequence or selection: (1-6): ");
    scanf("%d", &selection);
    printf("Enter the number of data: ");
    scanf("%d", &numCount);

    createAndPopulate(&myProd, selection, numCount);

    Inventory myInventory;
    initInventory(&myInventory);

    printf("\nORIGINAL PRODUCT:\n");
    for(int i = 0; i < myProd.count; ++i) {
        displayProduct(myProd.prods[i]);
        printf("\n");
    }

    for(int i = 0; i < myProd.count; ++i) {
        printf("\n[%d.] Adding %s (%d): %s\n", i+1, myProd.prods[i].prodName, myProd.prods[i].prodQty, addProductBaseOnExpiry(&myInventory, myProd.prods[i])? "Success":"Fail");
        visualize(myInventory);
    }

    printf("\nUSING ADD PRODUCT:\n");
    visualize(myInventory);


    return 0;
}