#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef char String[30];

typedef struct{
    int minute;
    int hour;
} Schedule;

typedef struct{
    String destName;
    int destPriority;
} Destination;

typedef struct{
    int flightCode;
    String aircraft;
    Schedule flightSched;
    Destination flightDest;
} Flight;

typedef struct {
    Flight elems[MAX];
    int count;
} PriorityQueue;

Flight newFlight(int flightCode, String aircraft, Schedule flightSched, Destination flightDest);
Schedule newSched(int minute, int hour);
Destination newDest(String destName, int destPriority);
void displayFlight(Flight a);
void insertFlight(PriorityQueue *list, Flight a);
int comparePrio(Flight a, Flight b);
void display(PriorityQueue list);
Flight dequeue(PriorityQueue* list);
void flightsBefore(PriorityQueue *list, Flight a, PriorityQueue* new);

int main(){
    Flight flightList[MAX];
    Destination NAIA = newDest("NAIA",1);
    Destination Clark = newDest("Clark Airport",2);
    Destination Francisco = newDest("Francisco Airport",2);
    Destination Iloilo = newDest("Iloilo Airport",2);
    Destination Panglao = newDest("Panglao Airport",3);
    Destination Bicol = newDest("Bicol Airport",4);
    Destination Bantayan = newDest("Bantayan AP",5);
    Destination Alto = newDest("Alto Airfield",6);
    
    flightList[0] = newFlight(201,"PAL",newSched(30,10),NAIA);
    flightList[1] = newFlight(202,"CebuPac",newSched(30,10),Clark);
    flightList[2] = newFlight(203,"PAL",newSched(30,12),Francisco);
    flightList[3] = newFlight(204,"SG",newSched(30,5),Iloilo);
    flightList[4] = newFlight(205,"Boieng",newSched(45,6),Panglao);
    flightList[5] = newFlight(206,"PAL",newSched(30,6),Bicol);
    flightList[6] = newFlight(207,"CebuPac",newSched(10,15),Bantayan);
    flightList[7] = newFlight(208,"Emirates",newSched(10,15),NAIA);
    flightList[8] = newFlight(209,"PAL",newSched(20,22),NAIA);
    
    FILE *fp;
    
    fp = fopen("destination_file.dat","wb");
    if (fp != NULL){
        fwrite(flightList,sizeof(Flight),9,fp);
    }
    fclose(fp);
    
    PriorityQueue flights;
    
    
    
    Flight p;
    fp = fopen("destination_file.dat","rb");
    if (fp != NULL){
        while (fread(&p, sizeof(Flight),1,fp)){
            insertFlight(&flights,p);
        }
    }

    
    display(flights);
    fclose(fp);
    
    PriorityQueue new;
    new.count = 0;
    flightsBefore(&flights,flightList[6], &new);
    display(new);
    
}
void flightsBefore(PriorityQueue *list, Flight a, PriorityQueue* new){
    FILE *fp;
    int og_count = list->count;
    fp = fopen("new_file.dat","wb");
    
    for (int i = 0; i < og_count ; ++i){
        if (fp != NULL){
            Flight dequeuedFlight = dequeue(list);
            if (dequeuedFlight.flightCode == a.flightCode){
                break;
            }
            fwrite(&dequeuedFlight,sizeof(Flight),1,fp);
        }
    }
    fclose(fp);
    Flight p;
    fp = fopen("new_file.dat","rb");
    if (fp != NULL){
        while (fread(&p, sizeof(Flight),1,fp)){
            insertFlight(new,p);
        }
    }
    fclose(fp);
    
}

Flight dequeue(PriorityQueue* list){
    Flight a = list->elems[0];
    list->count--;
    int smallest = 0;
    int left = 0, right = 0;
    while (1){
        left = smallest*2+1;
        right = smallest*2+2;
        
        if (right < list->count){
            if (comparePrio(list->elems[list->count],list->elems[right])==1 && comparePrio(list->elems[list->count],list->elems[left])==1){
                break;
            }
            if (comparePrio(list->elems[left],list->elems[right])==1){
                list->elems[smallest] = list->elems[left];
                smallest = left;
            } else {
                list->elems[smallest] = list->elems[right];
                smallest = right;
            }
        } else if (left < list->count){
            if (comparePrio(list->elems[list->count],list->elems[left])==1){
                break;
            } else {
                list->elems[smallest] = list->elems[left];
                smallest = left;
            }
        } else {
            break;
        }
    }
    list->elems[smallest] = list->elems[list->count];
    return a;
}
void display(PriorityQueue list){
    for (int i = 0; i < list.count; ++i){
        displayFlight(list.elems[i]);
    }
    printf("\n");
}
void insertFlight(PriorityQueue *list, Flight a){
    int i;
    for (i = list->count; i > 0 && comparePrio(a,list->elems[(i-1)/2]) == 1; i = (i-1)/2){
        list->elems[i] = list->elems[(i-1)/2];
    }
    list->elems[i] = a;
    list->count++;
}

int comparePrio(Flight a, Flight b){
    if (a.flightSched.hour < b.flightSched.hour){
        return 1;
    } else if (a.flightSched.hour > b.flightSched.hour){
        return 0;
    } else {
        if (a.flightSched.minute < b.flightSched.minute){
            return 1;
        } else if (a.flightSched.minute > b.flightSched.minute){
            return 0;
        } else {
            if (a.flightDest.destPriority < b.flightDest.destPriority){
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}
void displayFlight(Flight a){
    printf("Flight code: %d | Aircraft: %s | Sched: %d:%d | Destination: %s",a.flightCode,a.aircraft,a.flightSched.hour,a.flightSched.minute,a.flightDest.destName);
    printf("\n");
}
Destination newDest(String destName, int destPriority){
    Destination a;
    strcpy(a.destName,destName);
    a.destPriority = destPriority;
    return a;
}
Schedule newSched(int minute, int hour){
    Schedule a = {minute,hour};
    return a;
}
Flight newFlight(int flightCode, String aircraft, Schedule flightSched, Destination flightDest){
    Flight a;
    a.flightCode = flightCode;
    strcpy(a.aircraft,aircraft);
    a.flightSched = flightSched;
    a.flightDest = flightDest;
    return a;
}
