/*
Andry Canel
Movie Line
09/25/2023
*/



#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//struct to represent a new customer
typedef struct customer {
    char name[50];
    int numTickets;
    int lineNumber;
    int arrivalTime;
} customer;

typedef struct CustomerNode {
    customer* customer;
    struct CustomerNode* next;
} CustomerNode;


typedef struct CustomerQueue {
    CustomerNode* front;
    CustomerNode* back;
    int size;
} CustomerQueue;


//function that dynamically allocates memory and intitializes a new customer and returns it
customer* createCustomer(char* newName, int newNumTickets, int newLineNumber, int newArrivalTime) {
    customer* newCustomer = (customer*)malloc(sizeof(customer));


    strcpy(newCustomer->name, newName);
    newCustomer->numTickets = newNumTickets;
    newCustomer->lineNumber = newLineNumber;
    newCustomer->arrivalTime = newArrivalTime;

    return newCustomer;
}

//function to insert a customer into the rear of the queue
void enqueue(CustomerQueue* queue, customer* customer) {
    CustomerNode* new_node = (CustomerNode*) malloc(sizeof(CustomerNode));
    new_node->customer = customer;
    new_node->next = NULL;

    if(queue->back != NULL) {//?
        queue->back->next = new_node;
    }

    queue->back = new_node;

    if(queue->front == NULL) {
        queue->front = new_node;
    }

    queue->size++;
}

customer* dequeue(CustomerQueue* queue) {
    if(queue->front == NULL) {
        printf("Queue is empty.");
        return NULL;
    }

    CustomerNode* front_node = queue->front;
    customer* customer = front_node->customer;

    queue->front = front_node->next;
    if(queue->front == NULL) {
        queue->back = NULL;
    }

    free(front_node);
    queue->size--;

    return customer;
}

customer* peek(CustomerQueue* queue) {
    if(queue->front != NULL) {
        return queue->front->customer;
    } else {
        printf("Queue is empty.");
        return NULL;
    }
}

int isEmpty(CustomerQueue* queue) {
    return queue->front == NULL;
}

int size(CustomerQueue* queue) {
    return queue->size;
}

//function that finds the first queue that has the least amount of customers but at least had size 1
int findSmallestQueue (CustomerQueue* queues[]){
      int minSize;
      int queueNumber = 0; 

    for(int j = 0; j < 12; j++) {
        if(!isEmpty(queues[j])) {
            minSize = size(queues[j]);
            queueNumber = j;
            break;
        }
    }
        
    for(int j = queueNumber +1 ; j < 12; j++) {
      // printf("queue %d isEmpty is set to %d\n", j, !isEmpty(queues[j]))  ;
       if(!isEmpty(queues[j]) &&size(queues[j]) < minSize ){
           // printf("we in here\n");
         
                minSize = size(queues[j]);
                queueNumber = j;
        
       }

    }

    return queueNumber;
    
}

void printQueue(CustomerQueue* queue) {
    if(isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue number: %d\n", queue->front->customer->lineNumber + 1);
    CustomerNode* current = queue->front;
    while(current != NULL) {
        printf("Customer name: %s\n", current->customer->name);
        current = current->next;
    }
    printf("\n");
}

void printAllQueues(CustomerQueue* queues[]) {
    for(int i = 0; i < 12; i++) {
        if(!isEmpty(queues[i])) {
            printQueue(queues[i]);
        } else {
            printf("Queue number %d is empty.\n", i + 1);
        }
    }
}



int main(){

    //creating an array of all the queues and allocating the memory for each
    CustomerQueue* movieQueues[12];

    for(int i = 0; i < 12; i++) {
        movieQueues[i] = (CustomerQueue*) malloc(sizeof(CustomerQueue));
        movieQueues[i]->front = NULL;
        movieQueues[i]->back = NULL;
        movieQueues[i]->size = 0;
    }



    int numCustomers, numBooths;


    scanf("%d %d", &numCustomers, &numBooths);

    for(int i = 0; i < numCustomers; i++){

        char name[50];
        int numTickets, arrivalTime;

        scanf("%s %d %d", name, &numTickets, &arrivalTime);//scan in the customers information

        //checking the first letter and then assigning to respected queue
        
        int firstLetter  = name[0] - 'A';
        //printf("%d\n", firstLetter);

        int queueNum = firstLetter %13 - 1;

        if(queueNum == -1){
            queueNum = findSmallestQueue(movieQueues);

        }

        customer* newCustomer = createCustomer(name, numTickets, queueNum, arrivalTime);//create the new customer

        enqueue(movieQueues[queueNum], newCustomer); //then add them to the correct queue


    }

    printAllQueues(movieQueues);



    // Freeing all dynamically allocated memory
    for(int i = 0; i < 12; i++) {
        while(!isEmpty(movieQueues[i])) {
            customer* tempCustomer = dequeue(movieQueues[i]);
            free(tempCustomer);
        }
        free(movieQueues[i]);
    }

 for(int i = 0; i < 12; i++) {
    printf("%d\n", size(movieQueues[i]));
       
    }
//printAllQueues(movieQueues);


    return 0;

}