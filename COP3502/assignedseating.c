/*
Andry Canel
Assigned Seating
09/12/2023
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define INITSIZE 10
#define MAXLEN 50
#define MAXROWS 100000


typedef struct order {
 int s_seat;
 int e_seat;
 char* name;
} order;


typedef struct theaterrow {
 order** list_orders;
 int max_size;
 int cur_size;
} theaterrow;



order* make_order(int start, int end, char* this_name){
    order* newOrder = (order*)malloc(sizeof(order));//dynamically allocating an order
    newOrder->s_seat = start;
    newOrder->e_seat = end;
    newOrder->name = (char*)malloc(MAXLEN*sizeof(char));//dynamically allocating the for the name size
    strcpy(newOrder->name, this_name);
    return newOrder;
}


theaterrow* make_empty_row(){
    theaterrow* mtRow = (theaterrow*) malloc(sizeof(theaterrow));//dynamically allocating an empty row when BUY command is called
    mtRow->list_orders = (order**) malloc(INITSIZE*sizeof(order*));
    mtRow->max_size = INITSIZE;
    mtRow->cur_size = 0;
    return mtRow;
}


//checking to see if order1 is in order2 or vice versa
int conflict(order* order1, order* order2){
    if(order1->s_seat > order2->e_seat || order2->s_seat > order1->e_seat){
       // printf("There is no conflict\n");
        return 0;
    }
    else{
        return 1;
    }
}

//using conflict function to check to see if the order in this row is conflicting with any other previous orders
int can_add_order(theaterrow* this_row, order* this_order){
  //  printf("This row current size is %d\n",this_row->cur_size );
    for(int i = 0; i < this_row->cur_size; i++){
      // printf("IN THE CAN ADD ORDER FOR LOOP\n" );
        if(conflict(this_order, this_row->list_orders[i]) == 1){
            return 0;  
        }
    }
    return 1; 
}
//after can_add_order returns a 1 call this function that dynamically allocates  an order( or reallocate depending on the current siz) in list orders
void add_order(theaterrow* this_row, order* this_order){
    if(this_row->cur_size == this_row->max_size){
        this_row->max_size *= 2;
        this_row->list_orders = (order**)realloc(this_row->list_orders, this_row->max_size * sizeof(order*));

    }
    this_row->list_orders[this_row->cur_size] = this_order;
    this_row->cur_size++;
}

//returns the string name who occupies that particular seat given the theatre 2D array, seat number, and row
char* get_owner(theaterrow** theater, int row, int seat_num){
    theaterrow* this_row = theater[row];
    for(int i = 0; i < this_row->cur_size; i++){
        order* this_order = this_row->list_orders[i];
        if(this_order->s_seat <= seat_num && this_order->e_seat >= seat_num){
            return this_order->name;
        }
    }
    return NULL;
}
//returns the string name who occupies that particular seat given the seat number and row
char* get_row_owner(theaterrow* this_row, int seat_num){
    for(int i = 0; i < this_row->cur_size; i++){
        order* this_order = this_row->list_orders[i];
        if(this_order->s_seat <= seat_num && this_order->e_seat >= seat_num){
            return this_order->name;
        }
    }
    return NULL;
}


int contains(order* myorder, int seat_no){
    if(myorder->s_seat <= seat_no && myorder->e_seat >= seat_no){
        return 1;
    }
    return 0;
}

// frees the memory allocated for one order...by freeding the dynamically allocated name first then the order
void free_order(order* this_order){
    free(this_order->name);  
    free(this_order);  
}
// recursivley frees the memory allocated for the row in a theatre...by freeing the dynamically allocated for the orders array  with the free_order function and then the row

void free_row(theaterrow* this_row){
    for(int i = 0; i < this_row->cur_size; i++){
        free_order(this_row->list_orders[i]);  
    }
    free(this_row->list_orders);  
    free(this_row);  
}


int main(void){
    theaterrow** myTheater = calloc(MAXROWS+1, sizeof(theaterrow*));

    char command[10];//array for to hold "BUY", "LOOKUP", "QUIT"

    while(scanf("%s", command)){//continue scanning in all the strings on each input

        if(strcmp(command, "QUIT")==0) break;//break out when string equal "QUIT"


        if(strcmp(command, "BUY") == 0){//if string equal BUY check to see if seat is occupied through the previous orders
            int row, start, end;
            char name[MAXLEN];
            scanf("%d %d %d %s", &row, &start, &end, name);

            order* new_order = make_order(start, end, name);

            if(myTheater[row] == NULL){
                myTheater[row] = make_empty_row();
            }
            if(can_add_order(myTheater[row], new_order)==1){
               // printf("can add order\n");
                add_order(myTheater[row], new_order);
                printf("SUCCESS\n");
            }
            else{
                printf("FAILURE\n");
                free_order(new_order);  
            }
        }
        else if(strcmp(command, "LOOKUP") == 0){//looks up who is in a row/seat
            int row, seat;
            scanf("%d %d", &row, &seat);
            if(myTheater[row] == NULL){
                printf("No one\n");
            }
            else{
            char* owner = get_row_owner(myTheater[row], seat);
            if(owner == NULL){
                printf("No one\n");
            }
            else{
                printf("%s\n", owner);
            }

            }

        }
    }
//sucessfully recursively frees all memory that was dynamically allocated
    for(int i = 0; i < MAXROWS+1; i++){
        if(myTheater[i] != NULL){
            free_row(myTheater[i]);
        }
    }

    free(myTheater);

    return 0;
}
