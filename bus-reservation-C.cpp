// bus-reservation-C.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Bus reservation program from GeeksForGeeks
// Website link: https://www.geeksforgeeks.org/bus-reservation-system-in-c/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define BUFFER 50

struct Bus {
    int busNumber;
    char start[50];
    char destination[50];
    int totalSeats;
    int availableSeats;
    float fare;
};

struct Passenger {
    char name[50];
    int age;
    int seatNumber;
    int busNumber;
};

struct User {
    char username[50];
    char password[50];
};

void displayMainMenu();
void displayUserMenu();
int loginUser(struct User users[], int userTotal, char username[], char password[]);
void bookTicket(struct Bus buses[], int busTotal, struct Passenger passengers[], int* passengersBooked);
void cancelTicket(struct Bus buses[], int busTotal, struct Passenger passengers[], int* passengersBooked, int loginId);
void checkBusStatus(struct Bus buses[], int busTotal);
int loginUser(struct User users[], int userTotal, char username[], char password[]);


int main()
{
    int loginId = -1;

    struct User users[5] = {
        { "user1", "password1" }, { "user2", "password2" },
        { "user3", "password3" }, { "user4", "password4" },
        { "user5", "password5" },
    };

    int userTotal = sizeof(users) / sizeof(users[0]);

    struct Bus buses[3] = {
        { 101, "City A", "City B", 50, 50, 25.0 },
        { 102, "City C", "City D", 40, 40, 20.0 },
        { 103, "City E", "City F", 30, 30, 15.0 },
    };

    int busTotal = sizeof(buses) / sizeof(buses[0]);

    struct Passenger passengers[120];

    int passengersBooked = 0;

    while (1) {
        if (loginId == -1) {
            displayMainMenu();
            int option;
            scanf_s("%d", &option);
            switch (option) {
            case 1:
                char username[BUFFER];
                char password[BUFFER];
                printf("Enter Username: \n");
                scanf_s("%s", username, BUFFER);
                printf("Enter Password: \n");
                scanf_s("%s", password, BUFFER);

                loginId = loginUser(users, userTotal, username, password);

                if (loginId == -1) {
                    printf("Incorrect Login Details, please try again\n");
                }
                else {
                    printf("Login Successful: %s\n", username);
                }
                break;
            case 2:
                printf("Terminating program...\n");
                return 0;
                break;
            default:
                printf("Incorrect Input, please try again\n");
                break;
            }
        }
        else {
            displayUserMenu();
            int loggedOption;
            scanf_s("%d", &loggedOption);

            switch (loggedOption) {
            case 1:
                bookTicket(buses, busTotal, passengers, &passengersBooked);
                break;
            case 2:
                cancelTicket(buses, busTotal, passengers, &passengersBooked, loginId);
                break;
            case 3:
                checkBusStatus(buses, busTotal);
                break;
            case 4:
                printf("Logging out...\n");
                loginId = -1;
                break;
            default:
                printf("Invalid Input, please try again\n");
                break;
            }
            

        }
    }

    return 0;
    
}

void displayMainMenu() {
    printf("Bus Reservation Home\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("Enter your choice: ");
}

void displayUserMenu() {
    printf("Bus Reservation User Menu\n");
    printf("1. Book a Ticket\n");
    printf("2. Cancel a Ticket\n");
    printf("3. Check Bus Status\n");
    printf("4. Logout\n");
    printf("Enter your choice: ");
}

int loginUser(struct User users[], int userTotal, char username[], char password[]) {
    for (int i = 0; i < userTotal; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

void bookTicket(struct Bus buses[], int busTotal, struct Passenger passengers[], int* passengersBooked) {
    printf("----------\n");
    for (int i = 0; i < busTotal; i++) {
        printf("Bus %d, %s to %s | Seats Left: %d\n", buses[i].busNumber, buses[i].start, buses[i].destination, buses[i].availableSeats);
    }
    printf("----------\n");
    printf("Please select a bus number: ");
    int busSelect;
    scanf_s("%d", &busSelect);

    for (int i = 0; i < busTotal; i++) {
        if (busSelect == buses[i].busNumber) {
            if (buses[i].availableSeats > 0) {
                printf("Please enter your first name: ");
                scanf_s("%s", passengers[*passengersBooked].name, BUFFER);
                printf("Please enter age: ");
                scanf_s("%d", &passengers[*passengersBooked].age);
                passengers[*passengersBooked].seatNumber = (buses[i].totalSeats - buses[i].availableSeats) + 1;
                passengers[*passengersBooked].busNumber = busSelect;
                buses[i].availableSeats--;

                printf("Ticket for %s booked\n", passengers[*passengersBooked].name);
                (*passengersBooked)++;
                return;
            }
            else {
                printf("Bus is booked to max capacity\n");
                return;
            }
        }
    }
    printf("Bus number %d not found", busSelect);
}

void cancelTicket(struct Bus buses[], int busTotal, struct Passenger passengers[], int* passengersBooked, int loginId) {
    printf("Please enter your first name: ");
    char name[BUFFER];
    scanf_s("%s", name, BUFFER);

    int found = 0;
    for (int i = 0; i < *passengersBooked; i++) {
        if (strcmp(name, passengers[i].name) == 0) {
            int busSelect = -1;
            for (int j = 0; j < busTotal; j++) {
                if (buses[j].busNumber == passengers[j].busNumber) {
                    busSelect = j;
                    break;
                }
            }
            buses[busSelect].availableSeats++;

            for (int j = i; j < *passengersBooked - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            (*passengersBooked)--;

            printf("Ticket for %s cancelled\n", name);
            return;
        }
    }
    printf("No ticket for %s found\n", name);
}

void checkBusStatus(struct Bus buses[], int busTotal) {
    printf("----------\n");
    for (int i = 0; i < busTotal; i++) {
        printf("Bus %d, Journey: %s to %s, Seats left: %d, Fare: %f\n",
            buses[i].busNumber, buses[i].start, buses[i].destination, buses[i].availableSeats, buses[i].fare);
    }
    printf("----------\n");
}


