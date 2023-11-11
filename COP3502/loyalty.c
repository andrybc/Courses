#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 19
typedef struct customer {
 char name[MAXLEN+1];
 int points;
} customer;
typedef struct treenode {
 customer* cPtr;
 int size;
 struct treenode* left;
 struct treenode* right;
} treenode;

int compareName (char * firstName, char * secondName){

    return strcmp(firstName, secondName);

    
}
treenode *createCustomer (char * name, int points){
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

bool insertCustomerNode (treenode **rootptr, char * name, int points){

    treenode * root = *rootptr;
    if(root == NULL){
       // printf("we about to create a new node\n");   
        (*rootptr) = createCustomer(name, points);
       // printf("setting size to 1 now\n");
        return true;
    }
    if( strcmp(name, root->cPtr->name)==0){
        printf("this already in here...just gonna add points to previous one\n");
        root->cPtr->points+= points;
        printf("%s %d",root->cPtr->name, root->cPtr->points );
        return true;
    }
    if(strcmp(name, root->cPtr->name)<0){
        root->size++;
        return insertCustomerNode (&(root->left), name, points);
    }
    else{
         root->size++;
        return insertCustomerNode (&(root->right), name, points);
    }

}
bool doesCustomerExist (treenode *root, char * name){

    if(root == NULL) return false;

    if(strcmp(root->cPtr->name, name) == 0){
        printf("%s %d %d",root->cPtr->name, root->cPtr->points, root->size );
        return true;
    }
    if(strcmp(name, root->cPtr->name)<0){
        
        return doesCustomerExist (root->left, name);
    }
    else{
         
        return doesCustomerExist (root->right, name);
    }
}

treenode* findCustomer (treenode *root, char * name){
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

void subtractPoints(treenode **rootptr, char * name, int subpoints){
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

int main(){

    int numCommands;

    scanf("%d", &numCommands);
    treenode *root = NULL;

    for(int i=0; i < numCommands; i++){

        char command[8];
          scanf("%s", command);

        if(strcmp(command, "add")==0){
            char name[MAXLEN+1];
            int points;

            scanf("%s %d", name, &points);

            if(insertCustomerNode(&root, name, points)) printf("success!\n");

            
        }
        else if(strcmp(command, "search")==0){
            char name[MAXLEN+1];
            scanf("%s", name);

            if(doesCustomerExist(root, name)){
                printf("success!\n");
            }
            else{
                printf("%s not found\n", name);
            }


        }
        else if(strcmp(command, "sub")==0){
            char name[MAXLEN+1];
            int subtractPoint;
            scanf("%s %d", name, &subtractPoint);

            treenode* customer  = findCustomer(root, name);
            subtractPoints( &customer,name, subtractPoint);


        }







    }

    return 0;
}