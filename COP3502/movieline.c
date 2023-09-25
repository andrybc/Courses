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

typedef struct Booth {
    //CustomerQueue* line;
    int lastCheckoutTime;
    int numQueues;
    int* queueNumbers;
    int numOfCustomers;
} Booth;


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


Booth* assignQueuesToBooths(CustomerQueue* movieQueues[], int numBooths, int numQueues) {
    Booth* booths = (Booth*) malloc(numBooths * sizeof(Booth));
    int queuesPerBooth = numQueues / numBooths;
  //  printf("queues per booth is %d\n", queuesPerBooth);
    int extraQueues = numQueues % numBooths;
  //  printf("with %d remaining\n", extraQueues);

    int queueIndex = 0;
    int numofCustomers = 0;
    
    for(int i = 0; i < numBooths; i++) {
        booths[i].lastCheckoutTime = 0;
        booths[i].numQueues = queuesPerBooth + (i < extraQueues ? 1 : 0);
       // printf("Booth #%d will have %d queues\n", i+1, booths[i].numQueues);
      //  printf("Which will be: ");
         numofCustomers = 0;
        booths[i].queueNumbers = (int*) malloc(booths[i].numQueues * sizeof(int));

        for(int j = 0; j < booths[i].numQueues; j++) {
            //printf("im in the loop %d time\n", j+1);
            if (!isEmpty(movieQueues[queueIndex])) { // Check if queue is not empty
                
               //booths[i].queues[j] = movieQueues[queueIndex];
               numofCustomers+= size(movieQueues[queueIndex]);
                booths[i].queueNumbers[j] = queueIndex; // Store queue number
              // printf("non empty queue is queue #%d, ", queueIndex+1);

            } else {
            
                //skip assigning this queue to the booth 
                j--;
            }
            queueIndex++;
        }
        booths[i].numOfCustomers = numofCustomers;
        printf("Booth %d has %d customers in it\n", i+1, numofCustomers);




    }



    return booths;
}

void printBoothQueues(Booth* booths, int numBooths) {
    for (int i = 0; i < numBooths; i++) {
        printf("Booth %d: ", i + 1);
        for (int j = 0; j < booths[i].numQueues; j++) {
            printf("Queue %d", booths[i].queueNumbers[j]+1);
            if (j < booths[i].numQueues - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void processCustomers(Booth* booths, int numBooths, customer* customerLine[], int numCustomers) {
    for (int k = 0; k < numCustomers; k++) {
        customer* cust = customerLine[k];
        int lineNumber = cust->lineNumber; // Get the lineNumber of the customer
        int boothIndex = -1; // Initialize boothIndex to an invalid value

        // Find the booth in booths that is handling the queue with the given lineNumber
        for (int i = 0; i < numBooths; i++) {
            for (int j = 0; j < booths[i].numQueues; j++) {
                if (booths[i].queueNumbers[j] == lineNumber) {
                    boothIndex = i;
                    break;
                }
            }
            if (boothIndex != -1) {
                break;
            }
        }

        if (boothIndex != -1) {
            // Found the booth, process the customer
            int processingTime = 30 + cust->numTickets * 5;
            if (cust->arrivalTime < booths[boothIndex].lastCheckoutTime) {
                booths[boothIndex].lastCheckoutTime = cust->arrivalTime;
            }
            booths[boothIndex].lastCheckoutTime += processingTime;
            printf("%s from line %d checks out %d at time %d.\n",
                   cust->name, lineNumber + 1, boothIndex + 1,
                   booths[boothIndex].lastCheckoutTime);
            free(cust);
        } else {
            // Error: Customer's queue not found in any booth
            printf("Error: Customer's queue not found in any booth.\n");
        }
    }
}


void freeBooths(Booth* booths, int numBooths) {
    for (int i = 0; i < numBooths; i++) {
        for (int j = 0; j < booths[i].numQueues; j++) {
            if (booths[i].queues[j] != NULL) {
                free(booths[i].queues[j]); // Free the dynamically allocated queue
            }
        }
        if (booths[i].queueNumbers != NULL) {
            free(booths[i].queueNumbers); // Free the dynamically allocated queueNumbers array
        }
    }
    free(booths); // Free the dynamically allocated array of booths
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

    customer* customerLine[numCustomers];

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
        customerLine[i] = newCustomer;



    }

    printAllQueues(movieQueues);
     int numQueues = 0;
        for(int i = 0; i < 12; i++) {
            if(!isEmpty(movieQueues[i])){
                numQueues++;
            }
           
       
        }
        printf("%d\n", numQueues);

    Booth* booths = assignQueuesToBooths(movieQueues, numBooths, numQueues);
    printBoothQueues(booths,numBooths);

    processCustomers(booths, numBooths, numCustomers, customerLine);




    //freeBooths(booths, numBooths);




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