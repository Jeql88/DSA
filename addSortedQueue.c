bool addProductBaseOnExpiry(Inventory *i, Product p) {
    // To do code logic here.
    NodePtr temp = malloc(sizeof(struct node));
    temp->link = NULL;
    temp->prod = p;
    
    Inventory tempQueue;
    initInventory(&tempQueue);
    
    NodePtr holder = NULL;
    if (temp == NULL || i->currQty + temp->prod.prodQty > 100){
        return false;
    }
    while (i->top != NULL && dateDifference(temp->prod.expiry,i->top->prod.expiry)<=0){
        holder = i->top;
        i->top = i->top->link;
        if (tempQueue.top == NULL){
            tempQueue.top = holder;
        } else{
            tempQueue.tail->link = holder;
        }
        tempQueue.tail = holder;
    }
    
    if (tempQueue.top == NULL){
        tempQueue.top = temp;
    } else{
        tempQueue.tail->link = temp;
    }
    tempQueue.tail = temp;
    if (i->top != NULL){
        tempQueue.tail->link = i->top;
    }
    i->currQty += temp->prod.prodQty;
    
    i->top = tempQueue.top;
    i->tail = tempQueue.tail;
    
    
    
    
    return true;
}
