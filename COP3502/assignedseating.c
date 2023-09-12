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

// Returns a pointer to a dynamically allocated order storing the given
// start row, end row, and the name this_name. Note: strcpy should be
// used to copy the contents into the struct after its name field is
// dynamically allocated.
order* make_order(int start, int end, char* this_name);

order* make_order(int start, int end, char* this_name){
    order* newOrder = (order*)malloc(sizeof(order));
    newOrder->s_seat = start;
    newOrder->e_seat = end;
    newOrder->name = (char*)malloc(MAXLEN*sizeof(char));
    strcpy(newOrder->name, this_name);
    return newOrder;
}

// This function will allocate the memory for one theaterrow, including
// allocating its array of orders to a default maximum size of 10, and
// setting its current size to 0.
theaterrow* make_empty_row();
theaterrow* make_empty_row(){
    theaterrow* mtRow = (theaterrow*) malloc(sizeof(theaterrow));
    mtRow->list_orders = (order**) malloc(INITSIZE * sizeof(order*));
    mtRow->max_size = INITSIZE;
    mtRow->cur_size = 0;
    return mtRow;
}

// Assuming that order1 and order2 point to orders on the same row, this
// function returns 1 if the orders conflict, meaning that they share
// at least 1 seat in common, and returns 0 otherwise.

int conflict(order* order1, order* order2);
int conflict(order* order1, order* order2){
    if(order1->s_seat > order2->e_seat || order2->s_seat > order1->e_seat){
        printf("There is no conflict\n");
        return 0;
    }
    else{
        return 1;
    }
}
// Returns 1 if the order pointed to by this_order can be added to the
// row pointed to by this_row. Namely, 1 is returned if and only if
// this_order does NOT have any seats in it that are part of any order
// already on this_row.
int can_add_order(theaterrow* this_row, order* this_order);
int can_add_order(theaterrow* this_row, order* this_order){
    printf("This row current size is %d\n",this_row->cur_size );
    for(int i = 0; i < this_row->cur_size; i++){
       printf("IN THE CAN ADD ORDER FOR LOOP\n" );
        if(conflict(this_order, this_row->list_orders[i]) == 1){
            return 0;  
        }
    }
    return 1; 
}
// This function tries to add this_order to this_row. If successful,
// the order is added and 1 is returned. Otherwise, 0 is returned and
// no change is made to this_row. If the memory for this_row is full,
// this function will double the maximum # of orders allocated for the
// row (via realloc), before adding this_order, and adjust max_size and
// cur_size of this_row.
void add_order(theaterrow* this_row, order* this_order);
void add_order(theaterrow* this_row, order* this_order){
    if(this_row->cur_size == this_row->max_size){
        this_row->max_size *= 2;
        this_row->list_orders = (order**)realloc(this_row->list_orders, this_row->max_size * sizeof(order*));

    }
    this_row->list_orders[this_row->cur_size] = this_order;
    this_row->cur_size++;
}

// If seat_num seat number in row number row is occupied, return a
// pointer to the owner’s name. Otherwise, return NULL.
char* get_owner(theaterrow** theater, int row, int seat_num);
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
// If seat_num in the row pointed to by this_row is occupied, return a
// pointer to the string storing the owner’s name. If no one is sitting
// in this seat, return NULL.
char* get_row_owner(theaterrow* this_row, int seat_num);
char* get_row_owner(theaterrow* this_row, int seat_num){
    for(int i = 0; i < this_row->cur_size; i++){
        order* this_order = this_row->list_orders[i];
        if(this_order->s_seat <= seat_num && this_order->e_seat >= seat_num){
            return this_order->name;
        }
    }
    return NULL;
}

// This function returns 1 if the seat number seat_no is contained in
// the range of seats pointed to by myorder, and returns 0 otherwise.
int contains(order* myorder, int seat_no);
int contains(order* myorder, int seat_no){
    if(myorder->s_seat <= seat_no && myorder->e_seat >= seat_no){
        return 1;
    }
    return 0;
}
// Frees all memory associated with this_order.
void free_order(order* this_order);
void free_order(order* this_order){
    free(this_order->name);  // Free the memory allocated for the name
    free(this_order);  // Free the memory allocated for the order struct
}
// Frees all memory associated with this_row.
void free_row(theaterrow* this_row);
void free_row(theaterrow* this_row){
    for(int i = 0; i < this_row->cur_size; i++){
        free_order(this_row->list_orders[i]);  // Free each order in the row
    }
    free(this_row->list_orders);  // Free the memory allocated for the list of orders
    free(this_row);  // Free the memory allocated for the row struct
}


int main(void){
    theaterrow** myTheater = calloc(MAXROWS+1, sizeof(theaterrow*));

    char command[10];

    while(scanf("%s", command)){

        if(strcmp(command, "QUIT")==0) break;


        if(strcmp(command, "BUY") == 0){
            int row, start, end;
            char name[MAXLEN];
            scanf("%d %d %d %s", &row, &start, &end, name);

            order* new_order = make_order(start, end, name);

            if(myTheater[row] == NULL){
                myTheater[row] = make_empty_row();
            }
            if(can_add_order(myTheater[row], new_order)==1){
                printf("can add order\n");
                add_order(myTheater[row], new_order);
                printf("SUCCESS\n");
            }
            else{
                printf("FAILURE\n");
                free_order(new_order);  
            }
        }
        else if(strcmp(command, "LOOKUP") == 0){
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

    for(int i = 0; i < MAXROWS+1; i++){
        if(myTheater[i] != NULL){
            free_row(myTheater[i]);
        }
    }
    free(myTheater);

    return 0;
}
