/*
Andry Canel
12/03/2023
Arup Guha
inventory.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 19
#define TABLESIZE 300007

typedef struct item {
 char name[MAXLEN+1];
 int quantity;
 int saleprice;
} item;
typedef struct node {
 item* iPtr;
 struct node* next;
} node;
typedef struct hashtable {
 node** lists;
 int size;
} hashtable;
int totalCash = 100000;
int totalComplexity = 0;

int hashfunc(char* word, int size) {
 int len = strlen(word);
 int res = 0;
 for (int i=0; i<len; i++)
 res = (1151*res + (word[i]-'a'))%size;
 return res;
}

hashtable* initHashTable() {//function that initilializes a hash table with the TABLESIZE amount of list and sets them all to NULL
   hashtable* ht = malloc(sizeof(hashtable));
   ht->lists = malloc(sizeof(node*) * TABLESIZE);
   for (int i = 0; i < TABLESIZE; i++) {
       ht->lists[i] = NULL;
   }
   ht->size = TABLESIZE;//assignment told us to do this

   return ht;
}

int buyItem(hashtable* ht, char* itemName, int itemQuant, int itemPrice) {//function that gets called whenever buy command is inputed
   //finding the right index with given hash function
    int index = hashfunc(itemName, ht->size);
    //creating new node and 
    node* newNode = malloc(sizeof(node));
    item* newItem = malloc(sizeof(item));
    strcpy(newItem->name, itemName);
    newItem->quantity = itemQuant;
    newItem->saleprice = itemPrice; 
    newNode->iPtr = newItem;

    node* temp = ht->lists[index];
    int complexity = 0;

    while (temp != NULL && strcmp(temp->iPtr->name, itemName) != 0) {
        temp = temp->next;
        complexity++;
    }

    if (temp == NULL) {
        // item not found | insert at the beginning
        newNode->next = ht->lists[index];
        ht->lists[index] = newNode;
        complexity++; // length of the linked list after insertion
    } else {
        // item found | complexity is the position in the list
        complexity++;
        temp->iPtr->quantity += itemQuant;
    }

    totalCash -= itemPrice;
    printf("%s %d %d\n", itemName, itemQuant, totalCash);
    //free(newItem);
    //free(newNode);
    return complexity;
}


int sellItem(hashtable* ht, char* itemName, int itemQuant) {
    int index = hashfunc(itemName, ht->size);
    node* temp = ht->lists[index];
    int complexity = 0;

    while (temp != NULL && strcmp(temp->iPtr->name, itemName) != 0) {
        temp = temp->next;
        complexity++;
    }

    if (temp != NULL) {
        // Item found, complexity is the position in the list
        complexity++;
  
        if (temp->iPtr->quantity >= itemQuant) {
            temp->iPtr->quantity -= itemQuant;
            totalCash += (itemQuant * temp->iPtr->saleprice);

        } else {
            totalCash += (temp->iPtr->quantity * temp->iPtr->saleprice);
            temp->iPtr->quantity = 0;
            

        }
        printf("%s %d %d\n", itemName, temp->iPtr->quantity, totalCash);
    }

    return complexity;
}

int changePrice(hashtable* ht, char* itemName, int newPrice) {
    int index = hashfunc(itemName, ht->size);
    node* temp = ht->lists[index];
    int complexity = 0;

    while (temp != NULL && strcmp(temp->iPtr->name, itemName) != 0) {
        temp = temp->next;
        complexity++;
    }

    if (temp != NULL) {
        // item found | complexity is the position in the list
        complexity++;

        temp->iPtr->saleprice = newPrice;
    }

    return complexity;
}
int main(){

    int numCommands;
    hashtable* ht = initHashTable();
    scanf("%d", &numCommands);

    for(int i=0; i < numCommands; i++){
       // printf("we are here");
        char command[13];
          scanf("%s", command);

        if(strcmp(command, "buy")==0){
       // printf("we are buying");

            char itemName[MAXLEN+1];
            int itemQuant, itemPrice;

            scanf("%s %d %d", itemName, &itemQuant, &itemPrice);
            //adjust linked list and hashtable
         
          totalComplexity += buyItem(ht, itemName, itemQuant, itemPrice);

        }
        else if(strcmp(command, "sell")==0){
                   // printf("we are selling");

            char itemName[MAXLEN+1];
            int itemQuant;

            scanf("%s %d", itemName, &itemQuant);
            //adjust linked list and hashtable
          totalComplexity += sellItem(ht, itemName, itemQuant);

        }
        else if(strcmp(command, "change_price")==0){
                 //   printf("we are price changing");

            char itemName[MAXLEN+1];
            int  itemNewPrice;

            scanf("%s %d", itemName, &itemNewPrice);
            //adjust linked list and hashtable
          totalComplexity += changePrice(ht, itemName, itemNewPrice);
        }


    }

  printf("%d\n%d\n", totalCash,totalComplexity);

  for (int i = 0; i < ht->size; i++) {
    node* temp = ht->lists[i];
    while (temp != NULL) {// freeing the item and node struct
        node* next = temp->next;
        free(temp->iPtr); 
        free(temp);       
        temp = next;
    }
}
        free(ht->lists);         // freeing the array of lists
        free(ht);
    return 0;
}