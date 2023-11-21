/*
Andry Canel
11/14/2023
Arup Guha
loyalty.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 19



typedef struct customer {//customer struct that has the points and name variables declared
 char name[MAXLEN+1];
 int points;
} customer;


typedef struct treenode {//node struct to hold each customer struct | has regular treenode variables along with a size variable
 customer* cPtr;
 int size;
 struct treenode* left;
 struct treenode* right;
} treenode;



treenode *createCustomer (char * name, int points){//fucntion that returns a pointer to a customer treenode initilizing essential variables
    treenode* customerNode = malloc(sizeof(treenode));
        //    printf("trying to malloc a new node\n");

    if(customerNode!=NULL){
       
        customerNode->cPtr =malloc(sizeof(customer));
      //  printf("trying to malloc a new customer\n");
        customerNode->left = NULL;
        customerNode->right = NULL;
        customerNode->size =1;
        strcpy(customerNode->cPtr->name, name);
        customerNode->cPtr->points = points;
        printf("%s %d\n",customerNode->cPtr->name, customerNode->cPtr->points );

       //  printf("successfully malloced\n");
    }

    return customerNode;
}

//function to compare customers names
int compareName (char * firstName, char * secondName){
    return strcmp(firstName, secondName);    
}

bool insertCustomerNode (treenode **rootptr, char * name, int points){//function that inserts customer in the correct spot based on alphabetical order

    treenode * root = *rootptr;
    if(root == NULL){
       // printf("we about to create a new node\n");   
        (*rootptr) = createCustomer(name, points);
       // printf("setting size to 1 now\n");
        return true;
    }

   if (strcmp(name, root->cPtr->name) < 0) {
        if (insertCustomerNode(&(root->left), name, points)) {
            root->size++;  // Increment the size for the left subtree
            return true;
        }
    } else {
        if (insertCustomerNode(&(root->right), name, points)) {
            root->size++;  // Increment the size for the right subtree
            return true;
        }
    }

    return false;
}

int findDepth(treenode* root, char* target, int depth) {//function that finds the height of a given node
    if (root == NULL) {
        return -1; // node not found
    }

    if (strcmp(root->cPtr->name, target) == 0) {
        return depth;
    }

    int leftDepth = findDepth(root->left, target, depth + 1);
    if (leftDepth != -1) {
        return leftDepth; // node found in the left subtree
    }

    int rightDepth = findDepth(root->right, target, depth + 1);
    return rightDepth; // node found in the right subtree
}


bool doesCustomerExist (treenode *root, char * name){//function that checks if customer node exists | do not use it anymore 

    if(root == NULL) return false;

    if(strcmp(root->cPtr->name, name) == 0){
       // printf("%s %d %d",root->cPtr->name, root->cPtr->points, root->size );
        return true;
    }
    if(strcmp(name, root->cPtr->name)<0){
        
        return doesCustomerExist (root->left, name);
    }
    else{
         
        return doesCustomerExist (root->right, name);
    }
}

treenode* findCustomer (treenode *root, char * name){//function that returns the pointer of where the customer resides..if no customer exists, returns null
    treenode * head = root;
    if(root == NULL) return NULL;

    if(strcmp(head->cPtr->name, name) == 0){
      // printf("%s %d %d",root->cPtr->name, root->cPtr->points, root->size );
        return head;
    }
    if(strcmp(name, head->cPtr->name)<0){
        
        return findCustomer (head->left, name);
    }
    else{
         
        return findCustomer (head->right, name);
    }
}

void subtractPoints(treenode **rootptr, char * name, int subpoints){//function that subtracts the points from a given customer
        treenode * root = *rootptr;
        if(root ==NULL){
            printf("%s not found", name);
        }

    if( strcmp(name, root->cPtr->name)==0){
        
        if(subpoints>=root->cPtr->points ){
            root->cPtr->points = 0;
        }
        else{
        root->cPtr->points-= subpoints;
        }
        
        printf("%s %d\n",root->cPtr->name, root->cPtr->points );
    }

}

treenode* findPredecessor(treenode* root) {//function that finds the largest value in a subtree given a node
    if (root == NULL || root->right == NULL)
        return root;
    return findPredecessor(root->right);
}

void deleteCustomer(treenode** rootptr, char* name) {//function that deletes the node and replaces it with the proper node
    treenode* root = *rootptr;
    if (root == NULL)
        return;

    if (strcmp(name, root->cPtr->name) == 0) {
      //  printf("found what to delete\n");

        if (root->left == NULL && root->right == NULL) {
           // printf("no children, so deleting the node");
            free(root->cPtr);
            free(root);
            *rootptr = NULL;
        } else if (root->left == NULL) {
         //  printf("nothing on the left, so moving what's on the right up");
            treenode* temp = root->right;
            free(root->cPtr);
            free(root);
            *rootptr = temp;
          //  printf("nothing on the left, so moving what's on the right up");

        } else if (root->right == NULL) {
          //  printf("nothing on the right, so moving what's on the left up");
            treenode* temp = root->left;
            free(root->cPtr);
            free(root);
            *rootptr = temp;
          //  printf("nothing on the right, so moving what's on the left up");

        } else {
          //  printf("both children are present, replacing with predecessor");
            treenode* predecessor = findPredecessor(root->left);
            strcpy(root->cPtr->name, predecessor->cPtr->name);
            root->cPtr->points = predecessor->cPtr->points;
            deleteCustomer(&(root->left), predecessor->cPtr->name);
        }
    } else if (strcmp(name, root->cPtr->name) < 0) {
        deleteCustomer(&(root->left), name);
    } else {
        deleteCustomer(&(root->right), name);
    }

    // update the size after deleting
    if (*rootptr != NULL) {
        (*rootptr)->size = 1 + ((*rootptr)->left ? (*rootptr)->left->size : 0) + ((*rootptr)->right ? (*rootptr)->right->size : 0);
    }
}

int countNamesBefore(treenode* root, char* name) {//function that counts customers that come before a given node alphabetically
    if (root == NULL) {
        return 0; // empty tree case
    }

    if (strcmp(name, root->cPtr->name) <= 0) {
        //target name is greater  means it's not before this node
        return countNamesBefore(root->left, name);
    } else {
        //target name is smaller means  it's before this node
  
        int leftSize = (root->left == NULL) ? 0 : root->left->size;
        return leftSize + 1 + countNamesBefore(root->right, name);
    }
}


int compareCustomers(const void* a, const void* b) {//function that compares two customers points
//if points are equal then it goes by which comes first alphabetically
    customer* customerA = *(customer**)a;
    customer* customerB = *(customer**)b;

    // Compare by points first
    if (customerA->points > customerB->points) {
        return -1;
    } else if (customerA->points < customerB->points) {
        return 1;
    } else {
        // If points are tied, compare by name
        return strcmp(customerA->name, customerB->name);
    }
}
/*below are two funcitons required for a proper merge sort
made sure to use the compareCUstomers function to correctly order the customers
*/
void merge(customer** arr, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    customer* L[n1];
    customer* R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        // sort by points first, and if points are tied, then by name
        if (compareCustomers(&L[i], &R[j]) < 0) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    while (i < n1) {
        arr[k++] = L[i++];
    }

    while (j < n2) {
        arr[k++] = R[j++];
    }
}

void mergeSort(customer** arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // merge the sorted halves
        merge(arr, left, mid, right);
    }
}

//function that fills in the pointers that point to customer pointers  from the tree into the array
void fillinCustomerArray(treenode* root, customer** customerArray, int* index) {//using a preordertraversal
    if (root == NULL)
        return;

    // store the pointer to the customer node in the array
    customerArray[*index] = root->cPtr;
    (*index)++;

    fillinCustomerArray(root->left, customerArray, index);
    fillinCustomerArray(root->right, customerArray, index);
}

void printSortedCustomers(treenode* root) {//function that calls fulinCustomerArray and mergesort to print out the remain customers and their points in order 
    int numCustomers = root ? root->size : 0;
    customer** customerArray = malloc(numCustomers * sizeof(customer*));

    int index = 0;
    fillinCustomerArray(root, customerArray, &index);

    // perform merge sort on the array based on points and names
    mergeSort(customerArray, 0, numCustomers - 1);

    // print the sorted result
    for (int i = 0; i < numCustomers; i++) {
        printf("%s %d\n", customerArray[i]->name, customerArray[i]->points);
    }

    free(customerArray);
}
void freeTree(treenode* root) {//function to free a tree
    if (root == NULL) {
        return;
    }

    // Free the left and right subtrees
    freeTree(root->left);
    freeTree(root->right);

    if (root->cPtr != NULL) {
        free(root->cPtr);
    }

    free(root);
}

int main(){

    int numCommands;

    scanf("%d", &numCommands);
    treenode *root = NULL;
    treenode* customer;
    for(int i=0; i < numCommands; i++){
        
        char command[15];
          scanf("%s", command);

        if(strcmp(command, "add")==0){
            char name[MAXLEN+1];
            int points;

            scanf("%s %d", name, &points);
                
                customer  = findCustomer(root, name);

            if(customer != NULL){
                customer->cPtr->points+= points;
               printf("%s %d",customer->cPtr->name, customer->cPtr->points );
            //free(customer);

            }
            else if(insertCustomerNode(&root, name, points)) {
                //printf("success!\n");

            }
        }
        else if(strcmp(command, "search")==0){
            char name[MAXLEN+1];
            scanf("%s", name);
                
                customer  = findCustomer(root, name);
            if(customer != NULL){
               
               printf("%s %d %d\n",customer->cPtr->name, customer->cPtr->points, findDepth(root,name, 0) );
            ///free(customer);

                //printf("success!\n");
            }
            else{
                printf("%s not found\n", name);
            }


        }
        else if(strcmp(command, "sub")==0){
            char name[MAXLEN+1];
            int subtractPoint;
            scanf("%s %d", name, &subtractPoint);


            customer  = findCustomer(root, name);

           if(customer != NULL){


            subtractPoints( &customer,name, subtractPoint);
                       // free(customer);

            }
            else{
                printf("%s not found\n", name);
            }
        }

        else if(strcmp(command, "del")==0){
            char name[MAXLEN+1];
            scanf("%s", name);

            customer  = findCustomer(root, name);

             if(customer != NULL){
                
                deleteCustomer(&root,name);
                printf("%s deleted\n", name);
            }
            else{
                printf("%s not found\n", name);
            }


        }
        else if (strcmp(command, "count_smaller") == 0) {
        char name[MAXLEN + 1];
        scanf("%s", name);
        int count = countNamesBefore(root, name);
        printf("%d\n", count);
    }


    }

        printSortedCustomers(root);

        freeTree(customer);
        freeTree(root);

    return 0;
}