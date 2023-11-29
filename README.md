# Railway Reservation System Documentation

## Overview

The Railway Reservation System is a console-based C++ program that simulates the reservation and cancellation of train tickets. It manages the availability of Sleeper Class tickets, Reserved Against Cancellation (RAC) tickets, and Waiting List (WL) tickets. The system allows users to book tickets, cancel tickets, and view the status of booked and available tickets.

## Code Structure

### Constants

- `SLEEPER_SEATS`: The total number of Sleeper Class seats available.
- `RAC_SEATS`: The total number of Reserved Against Cancellation seats available.
- `WAITING_LIST_SEATS`: The total number of Waiting List seats available.

### Data Structures

1. **Passenger Structure (`struct Passenger`):**

   - Represents details of a passenger, including name, age, gender, berth preference, and seat number.

2. **Ticket Structure (`struct Ticket`):**

   - Represents a ticket, including a unique ticket ID and associated passenger details.

3. **Reservation System Class (`class ReservationSystem`):**
   - Manages the reservation system, including ticket booking, cancellation, and status tracking.
   - Contains queues for different types of seats (lower berth, upper berth, middle berth, RAC, and Waiting List).
   - Provides methods to book a ticket, cancel a ticket, print booked tickets, and print available tickets.

### Methods

1. **`ReservationSystem::bookTicket()`:**

   - Allows the user to input passenger details and books a ticket based on availability.
   - Handles scenarios such as senior citizens, preferred berth availability, RAC allocation, and Waiting List allocation.

2. **`ReservationSystem::cancelTicket(int ticketID)`:**

   - Cancels a booked ticket based on the provided ticket ID.
   - Adjusts the status of RAC and Waiting List tickets if needed.

3. **`ReservationSystem::printBookedTickets()`:**

   - Displays details of all booked tickets, including ticket ID, passenger name, age, gender, berth, and status (Confirmed, RAC, or Waiting List).

4. **`ReservationSystem::printAvailability()`:**

   - Displays the availability of Sleeper Class tickets, RAC tickets, and Waiting List tickets.

5. **`main()`:**
   - The main function that serves as the user interface.
   - Displays a menu for users to choose options like booking a ticket, canceling a ticket, viewing booked tickets, viewing available tickets, and exiting the program.

## Usage

1. **Booking a Ticket (`case 1`):**

   - User provides passenger details.
   - The system allocates a seat based on availability, berth preference, and passenger criteria.

2. **Canceling a Ticket (`case 2`):**

   - User provides the ticket ID to cancel a booked ticket.
   - The system adjusts the status of RAC and Waiting List tickets if needed.

3. **Printing Booked Tickets (`case 3`):**

   - Displays details of all booked tickets, including status (Confirmed, RAC, or Waiting List).

4. **Printing Available Tickets (`case 4`):**

   - Displays the current availability of Sleeper Class tickets, RAC tickets, and Waiting List tickets.

5. **Exiting the Program (`case 0`):**
   - Ends the execution of the program.

## Conclusion

The Railway Reservation System provides a simple and interactive way for users to book and manage train tickets. It handles various scenarios such as seat preferences, senior citizens, and dynamic adjustments for RAC and Waiting List tickets. Users can easily navigate through the menu to perform desired actions within the reservation system.
