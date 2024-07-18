Bus Reservation C Project
Project Idea from GeeksForGeeks: https://www.geeksforgeeks.org/bus-reservation-system-in-c/

loginUser(struct User users[], int userTotal, char username[], char password[]):
takes a scanf input for username and password and checks if those 2 values are in the users struct, if so the loop index is returned as the loginId, if not then -1 is returned to stay not logged in

bookTicket(struct Bus buses[], int busTotal, struct Passenger passengers[], int* passengersBooked):
asks user for the bus number to book (buses are printed) and if the bus has available seats will ask the user for their first name and age and put user and bus information into passengers[].
A message is displayed when the bus is full or cannot be found

cancelTicket(struct Bus buses[], int busTotal, struct Passenger passengers[], int* passengersBooked, int loginId):
Asks user for their first name and checks if it is in passengers[], if so then the information is removed from passengers[], passengersBooked decreased and available seats is increased. A message is displayed
if the name cannot be found

checkBusStatus(struct Bus buses[], int busTotal):
Prints all the buses[] fields in a readable manner
