/*
COP3223 Summer 2023 Assignment 3_2
Copyright 2023 Andry Canel
*/



#include <stdio.h>
#include <string.h>

// define the structure to store student information
typedef struct {
    char firstName[50];
    char lastName[50];
    int studentId;
    char grade;
} StudentRecord;

// initialize the array with student data
StudentRecord studentRecords[] = {
    {"John", "Johnson", 895645, 'A'},
    {"Jake", "Michaelson", 236598, 'A'},
    {"Sally", "Weber", 225584, 'C'},
    {"Tou", "Xiong", 364875, 'B'},
    {"Jacquelyn", "Jackson", 984587, 'D'},
    {"John", "White", 560258, 'C'}
};

// function to search by student ID
void search_id(int searchId) {
    for (int i = 0; i < 6; i++) {
        // If the student ID matches the search ID, print the student record
        if (studentRecords[i].studentId == searchId) {
            printf("Found record: %s %s, ID: %d, Grade: %c\n", studentRecords[i].firstName, studentRecords[i].lastName, studentRecords[i].studentId, studentRecords[i].grade);
        }
    }
}

// function to search by student's first name
void  search_firstname(char *searchFirstName) {
    for (int i = 0; i < 6; i++) {
        // if the first name matches the search name, print the student record
        if (strcmp(studentRecords[i].firstName, searchFirstName) == 0) {
            printf("Found record: %s %s, ID: %d, Grade: %c\n", studentRecords[i].firstName, studentRecords[i].lastName, studentRecords[i].studentId, studentRecords[i].grade);
        }
    }
}

// function to search by student's last name
void search_lastname(char *searchLastName) {
    for (int i = 0; i < 6; i++) {
        // if the last name matches the search name, print the student record
        if (strcmp(studentRecords[i].lastName, searchLastName) == 0) {
            printf("Found record: %s %s, ID: %d, Grade: %c\n", studentRecords[i].firstName, studentRecords[i].lastName, studentRecords[i].studentId, studentRecords[i].grade);
        }
    }
}

int main() {
    int searchOption;
    char searchName[50];
    int searchId;

    // prompt the user to select a search option
    printf("Enter search type (0 for first name, 1 for last name, 2 for ID): ");
    scanf("%d", &searchOption);

    // perform the search based on the selected option
    if (searchOption == 0) {
        printf("Enter the first name to search: ");
        scanf("%s", searchName);
         search_firstname(searchName);
    } else if (searchOption == 1) {
        printf("Enter the last name to search: ");
        scanf("%s", searchName);
        search_lastname(searchName);
    } else if (searchOption == 2) {
        printf("Enter the ID to search: ");
        scanf("%d", &searchId);
        search_id(searchId);
    } else {
        printf("Invalid search type!\n");
    }

    return 0;
}
