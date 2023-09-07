#include <stdlib.h>


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
// This function will allocate the memory for one theaterrow, including
// allocating its array of orders to a default maximum size of 10, and
// setting its current size to 0.
theaterrow* make_empty_row();
// Assuming that order1 and order2 point to orders on the same row, this
// function returns 1 if the orders conflict, meaning that they share
// at least 1 seat in common, and returns 0 otherwise.
int conflict(order* order1, order* order2);
// Returns 1 if the order pointed to by this_order can be added to the
// row pointed to by this_row. Namely, 1 is returned if and only if
// this_order does NOT have any seats in it that are part of any order
// already on this_row.
int can_add_order(theaterrow* this_row, order* this_order);
// This function tries to add this_order to this_row. If successful,
// the order is added and 1 is returned. Otherwise, 0 is returned and
// no change is made to this_row. If the memory for this_row is full,
// this function will double the maximum # of orders allocated for the
// row (via realloc), before adding this_order, and adjust max_size and
// cur_size of this_row.
void add_order(theaterrow* this_row, order* this_order);
// If seat_num seat number in row number row is occupied, return a
// pointer to the owner’s name. Otherwise, return NULL.
char* get_owner(theaterrow** theater, int row, int seat_num);
// If seat_num in the row pointed to by this_row is occupied, return a
// pointer to the string storing the owner’s name. If no one is sitting
// in this seat, return NULL.
char* get_row_owner(theaterrow* this_row, int seat_num);
// This function returns 1 if the seat number seat_no is contained in
// the range of seats pointed to by myorder, and returns 0 otherwise.
int contains(order* myorder, int seat_no);
// Frees all memory associated with this_order.
void free_order(order* this_order);
// Frees all memory associated with this_row.
void free_row(theaterrow* this_row);


int main(void){
    

    theaterrow** myTheater = calloc(MAXROWS+1, sizeof(theaterrow*));





    return 0;
}