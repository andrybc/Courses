#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node {
 char letter;
 struct node* next;
} node;
int length(node* head){
    int count = 0;
    
    while(head != NULL){
        count++;
        head = head->next;
    }
return count;

}
char* toCString(node * head){
    int size = length(head);
    char *newString = malloc((size+1)* sizeof(char));

    for(int i = 0; i < size; i++ ){
        newString[i]= head->letter;
        head= head->next;
    }
   // newString[size+1] = '/0';
    return newString;
}
void printLinkedList(node* head) {
    while (head != NULL) {
        printf("%c ", head->letter);
        head = head->next;
    }
    printf("\n");
}


int main(){

node* node1 = (node*)malloc(sizeof(node));
node1->letter = 'B';
node1->next = NULL;

node* node2 = (node*)malloc(sizeof(node));
node2->letter = 'o';
node2->next = NULL;

node* node3 = (node*)malloc(sizeof(node));
node3->letter = 'b';
node3->next = NULL;

node1->next = node2;
node2->next = node3;

node* head = node1;
printLinkedList(head);

char* sameWord = toCString(head);


printf("%s", sameWord);







}
