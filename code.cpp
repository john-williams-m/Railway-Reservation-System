#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int SLEEPER_SEATS = 6;
int RAC_SEATS = 1;
int WAITING_LIST_SEATS = 1;

struct Passenger
{
    string name;
    int age;
    char gender;
    string berthPreference;
    int seatNumber;
};
struct Ticket
{
    int ticketId;
    Passenger passenger;
};

class ReservationSystem
{
    vector<Ticket> tickets;
    int ticketID;
    queue<int> lowerBerthSeats;
    queue<int> upperBerthSeats;
    queue<int> middleBerthSeats;
    queue<int> racSeats;
    queue<int> waitingListSeats;

public:
    ReservationSystem() : ticketID(1)
    {
        int i = 1;
        while (i <= SLEEPER_SEATS)
        {
            lowerBerthSeats.push(i++);
            middleBerthSeats.push(i++);
            upperBerthSeats.push(i++);
        }
        for (int i = 1; i <= RAC_SEATS; i++)
        {
            racSeats.push(i);
        }
        for (int i = 1; i <= WAITING_LIST_SEATS; i++)
        {
            waitingListSeats.push(i);
        }
    }
    void bookTicket();
    void cancelTicket(int ticketID);
    void printAvailability();
    void printBookedTickets();
};

void ReservationSystem::cancelTicket(int ticketID)
{
    if (tickets.size() == 0)
    {
        cout << "No tickets found!" << endl;
        return;
    }
    vector<Ticket>::iterator it = tickets.begin();
    for (; it != tickets.end(); it++)
    {
        if (it->ticketId == ticketID)
        {
            break;
        }
    }

    if (it != tickets.end())
    {
        string berth = it->passenger.berthPreference;
        int seatNumber = it->passenger.seatNumber;
        tickets.erase(it);
        cout << "Ticket cancelled successfully!" << endl;

        // Finding next RAC ticket and changing it to Confirm ticket

        vector<Ticket>::iterator nextAvailableRAC = tickets.begin();
        for (; nextAvailableRAC != tickets.end(); nextAvailableRAC++)
        {
            if (nextAvailableRAC->passenger.berthPreference == "RAC")
            {
                int racSeatNumber = nextAvailableRAC->passenger.seatNumber;
                racSeats.push(racSeatNumber);
                nextAvailableRAC->passenger.berthPreference = berth;
                nextAvailableRAC->passenger.seatNumber = seatNumber;

                // Finding next Waiting List ticket and changing it to RAC ticket

                vector<Ticket>::iterator nextAvailableWaitingList = tickets.begin();
                for (; nextAvailableWaitingList != tickets.end(); nextAvailableWaitingList++)
                {
                    if (nextAvailableWaitingList->passenger.berthPreference == "WL")
                    {
                        int waitingListNumber = nextAvailableWaitingList->passenger.seatNumber;
                        waitingListSeats.push(waitingListNumber);
                        nextAvailableWaitingList->passenger.seatNumber = racSeats.front();
                        racSeats.pop();
                        nextAvailableWaitingList->passenger.berthPreference = "RAC";
                        break;
                    }
                }
                break;
            }
        }
        if (nextAvailableRAC == tickets.end())
        {
            berth == "LB" ? lowerBerthSeats.push(seatNumber) : (berth == "MB" ? middleBerthSeats.push(seatNumber) : upperBerthSeats.push(seatNumber));
        }
    }
    else
    {
        cout << "Ticked ID not found" << endl;
    }
}

void ReservationSystem::bookTicket()
{
    if (tickets.size() == SLEEPER_SEATS + RAC_SEATS + WAITING_LIST_SEATS)
    {
        cout << "No tickets available" << endl;
        return;
    }
    Passenger passenger;
    cout << "Enter passenger details:" << endl;
    cout << "Name:";
    cin.ignore();
    getline(cin, passenger.name);
    cout << "Age:";
    cin >> passenger.age;
    cout << "Gender (M/F): ";
    cin >> passenger.gender;
    cout << "Berth Preference (LB/MB/UB): ";
    cin >> passenger.berthPreference;

    if (passenger.age < 5)
    {
        cout << "No need of ticket reservation for age below than 5" << endl;
    }
    else
    {
        if (passenger.age > 60)
        {
            passenger.berthPreference = "LB";
            if (!lowerBerthSeats.empty())
            {
                passenger.seatNumber = lowerBerthSeats.front();
                lowerBerthSeats.pop();
            }
            else
            {
                cout << "Lower berth for senior citizen not available!" << endl;
            }
            cout << "Your berth preference changed to LB" << endl;
        }

        if (!lowerBerthSeats.empty() || !middleBerthSeats.empty() || !upperBerthSeats.empty())
        {
            if (passenger.berthPreference == "LB" && !lowerBerthSeats.empty())
            {
                passenger.seatNumber = lowerBerthSeats.front();
                lowerBerthSeats.pop();
            }
            else if (passenger.berthPreference == "MB" && !middleBerthSeats.empty())
            {
                passenger.seatNumber = middleBerthSeats.front();
                middleBerthSeats.pop();
            }
            else if (passenger.berthPreference == "UB" && !upperBerthSeats.empty())
            {
                passenger.seatNumber = upperBerthSeats.front();
                upperBerthSeats.pop();
            }

            // if preferred berth is not available - then it will allocate the available berth

            else if (!lowerBerthSeats.empty())
            {
                cout << "Berth preference changed to LB" << endl;
                passenger.berthPreference = "LB";
                passenger.seatNumber = lowerBerthSeats.front();
                lowerBerthSeats.pop();
            }
            else if (!middleBerthSeats.empty())
            {
                cout << "Berth preference changed to MB" << endl;
                passenger.berthPreference = "MB";
                passenger.seatNumber = middleBerthSeats.front();
                middleBerthSeats.pop();
            }
            else if (!upperBerthSeats.empty())
            {
                cout << "Berth preference changed to UB" << endl;
                passenger.berthPreference = "UB";
                passenger.seatNumber = upperBerthSeats.front();
                upperBerthSeats.pop();
            }
            Ticket t = {ticketID++, passenger};
            tickets.push_back(t);
            cout << "Ticket booked successfully, Your berth is confirmed. Ticket ID: " << ticketID - 1 << endl;
        }
        else if (!racSeats.empty())
        {
            passenger.seatNumber = racSeats.front();
            passenger.berthPreference = "RAC";
            racSeats.pop();
            Ticket t = {ticketID++, passenger};
            tickets.push_back(t);
            cout << "Ticket booked successfully, Your ticket is in RAC. Ticket ID:" << ticketID - 1 << endl;
        }
        else if (!waitingListSeats.empty())
        {
            passenger.seatNumber = waitingListSeats.front();
            passenger.berthPreference = "WL";
            waitingListSeats.pop();
            Ticket t = {ticketID++, passenger};
            tickets.push_back(t);
            cout << "Ticket booked successfully, Your ticket is in Waiting List. Ticket ID:" << ticketID - 1 << endl;
        }
    }
}

void ReservationSystem::printBookedTickets()
{
    for (Ticket &t : tickets)
    {
        cout << "Ticket ID:" << t.ticketId << ", Name:" << t.passenger.name << ", Age:" << t.passenger.age << ", Gender:" << t.passenger.gender << ", Berth:" << t.passenger.seatNumber << t.passenger.berthPreference << ", Status:";
        cout << (t.passenger.berthPreference == "RAC" ? "RAC" : (t.passenger.berthPreference == "WL" ? "WL" : "Confirmed")) << endl;
    }
}

void ReservationSystem::printAvailability()
{
    cout << "Available Sleeper Tickets:- "
         << "Lower Berth:" << lowerBerthSeats.size() << ", Middle Berth:" << middleBerthSeats.size() << ", Upper Berth:" << upperBerthSeats.size() << endl;
    cout << "Available RAC Tickets:" << racSeats.size() << endl;
    cout << "Available Waiting List Tickets:" << waitingListSeats.size() << endl;
    cout << endl;
}

using namespace std;
int main()
{
    ReservationSystem system;
    bool userWish(true);
    int choice;
    do
    {
        cout << "\nRailway Reservation System Menu:\n";
        cout << "1. Book Ticket\n";
        cout << "2. Cancel Ticket\n";
        cout << "3. Print Booked Tickets\n";
        cout << "4. Print Available Tickets\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            system.bookTicket();
            break;
        case 2:
            int ID;
            cout << "Enter Ticket ID:";
            cin >> ID;
            system.cancelTicket(ID);
            break;
        case 3:
            system.printBookedTickets();
            break;
        case 4:
            system.printAvailability();
            break;
        case 0:
            cout << "Exiting program. Thank you!";
            break;
        default:
            break;
        }
    } while (choice != 0);
}