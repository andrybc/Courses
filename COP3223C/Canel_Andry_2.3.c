/*
COP3223 Summer 2023 Assignment 2_3
Copyright 2023 Andry Canel
*/



#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SEATS 6

int seats[NUM_SEATS] = {0}; // Array to store seat availability (0 for empty, 1 for occupied)
int passenger_count = 0;

// Function to print boarding pass
void print_boarding_pass(int class_type, int seat)
{
    if (class_type == 1)
    {
        printf("Your seat is assigned to first class seat %d\n", seat);
    }
    else if (class_type == 2)
    {
        printf("Your seat is assigned to  economy seat %d\n", seat);
    }
    passenger_count++;
    //printf("the amount of passengers we have is now %d\n", passenger_count);
}
// Function to assign a seat to a passenger
void search_seat(int class_type)
{
    int seat;
    int available_seats[NUM_SEATS];
    int num_available_seats = 0;

    if (class_type == 1)
    {
        // First class
        for (seat = 0; seat < 3; seat++)
        {
            if (seats[seat] == 0)
            {
                available_seats[num_available_seats] = seat;
                num_available_seats++;
            }
        }
    }
    else if (class_type == 2)
    {
        // Economy class
        for (seat = 3; seat < NUM_SEATS; seat++)
        {
            if (seats[seat] == 0)
            {
                available_seats[num_available_seats] = seat;
                num_available_seats++;
            }
        }
    }

    if (num_available_seats > 0)
    {
        int random_seat_index = rand() % num_available_seats;
        int assigned_seat = available_seats[random_seat_index];
        seats[assigned_seat] = 1; // Mark seat as occupied

        print_boarding_pass(class_type, assigned_seat + 1);
    }
    else
    {
        // If no seat is available in the desired class
        if (class_type == 1)
        {
            printf("No seat available in first class. ");
        }
        else if (class_type == 2)
        {
            printf("No seat available in economy class. ");
        }

        // Ask if the passenger is willing to upgrade or downgrade
        int upgrade;
        printf("Do you want a seat in the other class? (1 for yes, 0 for no): ");
        scanf("%d", &upgrade);

        if (upgrade == 1)
        {
            // Assign a seat from the other class
            if (class_type == 1)
            {
                search_seat(2); // Assign economy seat
            }
            else if (class_type == 2)
            {
                search_seat(1); // Assign first class seat
            }
        }
        else
        {
            printf("Next flight leaves in 3 hours.\n");
        }
    }
}

int main()
{
    srand(time(NULL)); // Seed the random number generator

    int all_boarded = 0;

    while (!all_boarded)
    {
        int class_type;
        printf("Please type 1 for 'first class'\n");
        printf("Please type 2 for 'economy'\n");
        scanf("%d", &class_type);
        if (passenger_count == NUM_SEATS)
        {
            printf("All seats are filled up. Next flight leaves in 3 hours.\n");
        }
        else
        {
            search_seat(class_type);
        }

        printf("Does everyone boarded? (1 for yes, 0 for no): ");
        scanf("%d", &all_boarded);
    }

    return 0;
}
