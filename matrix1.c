#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTEX 6
#define SENTINEL 100

typedef char vertexType;
typedef int labelType;
typedef enum {False = 0,True = 1} Boolean;
typedef struct {
    vertexType tail;
    vertexType head;
    int weight;
} edgeType;

typedef struct {
    vertexType adjVertex;
    int weight;
} adjType;

typedef struct node {
    adjType info;
    struct node* link;
} *AdjList;

typedef struct {
    AdjList head[MAX_VERTEX];
    int edgeCount;
} directedAdjList;

typedef struct {
    int matrix[MAX_VERTEX][MAX_VERTEX];
    int edgeCount;
} labeledAdjMatrix;

typedef struct {
    int arr[MAX_VERTEX];
    int top;
} Stack;

typedef struct {
    vertexType arr[MAX_VERTEX];
    int front;
    int rear;
} Queue;

void initDirectedAdjList(directedAdjList* a);
directedAdjList populateDirectAdjList();
void displayAdjList(directedAdjList a);
void insertAdjList(vertexType from, vertexType to, int weight, directedAdjList* a);
void deleteEdgeAdjList(vertexType from, vertexType to, directedAdjList* a);
void deleteVertexAdjList(vertexType vertexName, directedAdjList* a);

void initLabeledAdjMatrix(labeledAdjMatrix *a);
labeledAdjMatrix convertListToAdjMatrix();
void displayAdjMatrix(labeledAdjMatrix a);
void helper(directedAdjList a, vertexType curr, Stack *stackList, Boolean wasVisited[]);
Stack dfsList(directedAdjList a, vertexType curr);
void displayStack(Stack stackList);
void recursionListDFS(directedAdjList G, vertexType src, Boolean visArr[]);
void iterativeListBFS(directedAdjList a, vertexType curr);
void iterativeMatrixBFS(labeledAdjMatrix a, vertexType curr);
void recursionMatrixDFS(labeledAdjMatrix b, vertexType curr, Boolean visArr[]);
labeledAdjMatrix floydWarshall(labeledAdjMatrix b);


//to do deleteList and deleteMatrix
void main(){
    directedAdjList a;
    a = populateDirectAdjList();
    displayAdjList(a);
    
    labeledAdjMatrix b;
    b = convertListToAdjMatrix(a);
    displayAdjMatrix(b);    
    
    Stack s;
    s = dfsList(a, 'A');
    displayStack(s);
    
    Boolean visArr[MAX_VERTEX] = {False};
    recursionListDFS(a,'A',visArr);
    
    Boolean visArr2[MAX_VERTEX] = {False};
    printf("\n");
    recursionMatrixDFS(b,'A',visArr2);
    
    printf("\nIterative BFS\n");
    iterativeListBFS(a,'A');
    printf("\n");
    iterativeMatrixBFS(b,'A');
    
    labeledAdjMatrix c = floydWarshall(b);
    displayAdjMatrix(c);
}
labeledAdjMatrix floydWarshall(labeledAdjMatrix b){
    
    labeledAdjMatrix m;
    m.edgeCount = 0;
    for (int i = 0; i < MAX_VERTEX; ++i){
        for (int k = 0; k < MAX_VERTEX; ++k){
            if (i == k){
                m.matrix[i][k] = 0;
            } else {
                m.matrix[i][k] = b.matrix[i][k];
            }
        }
    }
    
    for (int i = 0; i < MAX_VERTEX; ++i){
        for (int j = 0; j < MAX_VERTEX; ++j){
            for (int k = 0; k < MAX_VERTEX; ++k){
                if ((b.matrix[i][k] + b.matrix[j][i]) < b.matrix[j][k]){
                    m.matrix[j][k] = b.matrix[i][k] + b.matrix[j][i];
                }
            }
        }
    }
    return m;
}
void recursionMatrixDFS(labeledAdjMatrix b, vertexType curr, Boolean visArr[]){
    visArr[curr-'A'] = True;
    printf("%c ",curr);
    
    for (int k = 0; k < MAX_VERTEX; ++k){
        if (b.matrix[curr-'A'][k] != SENTINEL && visArr[k] == False){
            recursionMatrixDFS(b, k + 'A',visArr);
        }
    }
}
void recursionListDFS(directedAdjList G, vertexType src, Boolean visArr[]){
    visArr[src-'A'] = True;
    printf("%c ",src);
    AdjList trav;
    for (trav = G.head[src-'A']; trav != NULL; trav = trav->link){
        if (visArr[trav->info.adjVertex - 'A']== False){
            recursionListDFS(G,trav->info.adjVertex,visArr);
        }
    }
}
void displayStack(Stack stackList){
    printf("\n");
    for (int i = 0; i < stackList.top; ++i){
        printf("%c ",stackList.arr[i]);
    }
    printf("\n");
}
void helper(directedAdjList a, vertexType curr, Stack *stackList, Boolean wasVisited[]){
    wasVisited[curr-'A'] = True;
    stackList->arr[stackList->top++] = curr;
    AdjList trav;
    
    for (trav = a.head[curr-'A']; trav != NULL; trav = trav->link){
        if (!(wasVisited[trav->info.adjVertex - 'A'])){
            helper(a, trav->info.adjVertex, stackList, wasVisited);
        }
    }
    
}
void iterativeMatrixBFS(labeledAdjMatrix a, vertexType curr){
    Queue q = {.front = 0, .rear = -1};
    Boolean wasVisited[MAX_VERTEX] = {False};
    q.rear = (q.rear+1)%MAX_VERTEX;
    wasVisited[curr-'A'] = True;
    q.arr[q.rear] = curr;
    int i,k;
    while ((q.rear + 1)% MAX_VERTEX != q.front){
        vertexType temp = q.arr[q.front];
        q.front = (q.front + 1)%MAX_VERTEX;
        printf("%c ",temp);
        int currIndex = temp - 'A';
        for (k = 0; k < MAX_VERTEX; ++k){
            if (a.matrix[currIndex][k] != SENTINEL && wasVisited[k] == False){
                q.rear = (q.rear + 1 ) % MAX_VERTEX;
                q.arr[q.rear] = 'A' + k;
                wasVisited[k] = True;
            }
        }
        
    }
    
}
void iterativeListBFS(directedAdjList a, vertexType curr){
    Queue q;
    Boolean wasVisited[MAX_VERTEX] = {False};
    wasVisited[curr-'A'] = True;
    q.front = 0;
    q.rear = -1;
    q.rear = (q.rear + 1) % MAX_VERTEX;
    q.arr[q.rear] = curr;
    
    while ((q.rear+1) % MAX_VERTEX != q.front){
        vertexType front = q.arr[q.front];
        printf("%c ",front);
        
        q.front = (q.front+1)%MAX_VERTEX;
        AdjList trav;
        for (trav = a.head[front-'A']; trav!= NULL; trav = trav->link){
            if (wasVisited[trav->info.adjVertex-'A']==False){
                wasVisited[trav->info.adjVertex-'A'] = True;
                q.rear = (q.rear+1)%MAX_VERTEX;
                q.arr[q.rear] = trav->info.adjVertex;
            }
        }
    }
}
Stack dfsList(directedAdjList a, vertexType curr){
    Stack s;
    Boolean wasVisited[MAX_VERTEX] = {False};
    for (int i = 0; i < MAX_VERTEX; ++i){
        s.arr[i] = 0;
        wasVisited[i] = 0;
    }
    s.top = 0;
    
    helper(a, curr, &s, wasVisited);
    
    return s;
}

void initLabeledAdjMatrix(labeledAdjMatrix *a){
    for (int i = 0; i < MAX_VERTEX; ++i){
        for (int k = 0; k < MAX_VERTEX; ++k){
            a->matrix[i][k] = SENTINEL;
        }
    }
    a->edgeCount = 0;
}
labeledAdjMatrix convertListToAdjMatrix(directedAdjList a){
    labeledAdjMatrix b;
    initLabeledAdjMatrix(&b);
    AdjList trav;
    for (int i = 0; i < MAX_VERTEX; ++i){
        for (trav = a.head[i]; trav != NULL; trav = trav->link){
            b.matrix[i][trav->info.adjVertex - 'A'] = trav->info.weight;
            b.edgeCount++;
        }
    }
    return b;
}
void initDirectedAdjList(directedAdjList* a){
    for (int i = 0; i < MAX_VERTEX; ++i){
        a->head[i] = NULL;
    }
    a->edgeCount = 0;
}

directedAdjList populateDirectAdjList(){
    directedAdjList populated;
    initDirectedAdjList(&populated);
    
    int count = 15;
    edgeType data[] = { {'A','E',6}, {'C','A',4}, {'E','C',6}, {'A','F',3},
                        {'C','D',6}, {'E','F',6}, {'B','A',4}, {'D','A',8},
                        {'F','B',3}, {'B','C',3}, {'D','B',6}, {'D','E',3},
                        {'B','E',6}, {'F','D',3}, {'B','F',10} };
                        
    AdjList *trav, temp;
    
    for (int i = 0; i < count; ++i){
        for (trav = &(populated.head[data[i].tail - 'A']); *trav != NULL && (data[i].head > (*trav)->info.adjVertex); trav = &(*trav)->link){}
        if (*trav != NULL && (*trav)->info.adjVertex == data[i].head){
            (*trav)->info.weight = (data[i].weight < (*trav)->info.weight) ? data[i].weight: (*trav)->info.weight ;
        } else {
            temp = malloc(sizeof(struct node));
            temp->info.adjVertex = data[i].head;
            temp->info.weight = data[i].weight;
            temp->link = *trav;
            *trav = temp;
        }
        populated.edgeCount++;
    }
    return populated;
}
void displayAdjMatrix(labeledAdjMatrix L){
    int i;
    AdjList temp;
    
    printf("\n\nTHE ADJACENCY MATRIX::");
    printf("\n%-8s","VERTEX");
    printf("%-20s","ADJACENT VERTICES");
    printf("\n%-8s","------");
    printf("%-19s","-----------------");
    
    for (int i = 0; i < MAX_VERTEX; ++i){
        printf("\n %c :: ", 'A'+i);
        for (int k = 0; k < MAX_VERTEX; ++k){
            if (L.matrix[i][k] == SENTINEL){
                printf(" INF");
            } else {
                printf(" %3d",L.matrix[i][k]);
            }
        }
    }
    printf("\n\nNumber of arcs: %d\n\n",L.edgeCount);
}
void displayAdjList(directedAdjList L){
    int i;
    AdjList temp;
    
    printf("\n\nTHE ADJACENCY LIST::");
    printf("\n%-8s","VERTEX");
    printf("%-20s","ADJACENT VERTICES");
    printf("\n%-8s","------");
    printf("%-19s","-----------------");
    
    for (i = 0; i < MAX_VERTEX; ++i){
        printf("\n %c :: ", 'A' + i);
        if (L.head[i] == NULL){
            printf(" NULL");
        } else {
            for (temp = L.head[i]; temp != NULL; temp = temp->link){
                printf(" %c (%3d)\t",temp->info.adjVertex, temp->info.weight);
            }
        } 
    }
    printf("\n\nNumber of arcs: %d\n\n",L.edgeCount);
}
