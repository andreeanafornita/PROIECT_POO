#include<iostream>
#include "Location.h"
#include "Event.h"
#include "Ticket.h"
using namespace std;
int main() {

	Location location1;
	cin >> location1;
	cout << location1;
	cout << endl;
	Location::printLocation(location1);
	cout << endl;
	cout << "You have entered the location details succesfully";
	Event event1;
	cin >> event1;
	cout << event1;
	cout << endl;
	Event::printEvent(event1);
	cout << endl;
	cout << "You have entered the event details succesfully";
	Ticket ticket1;
	cin >> ticket1;
	cout << ticket1;
	cout << endl;
	Ticket::printTicket(ticket1);
	cout << endl;
	cout << "You have entered the ticket details succesfully";

	return 0;
}