#include<iostream>
#include<fstream>
#include<vector>
#include "Location.h"
#include "Event.h"
#include "Ticket.h"

using namespace std;

void displayMenu() {
	cout << "MENIU:" << endl;
	cout << "1.See the events" << endl;
	cout << "2.Buy tickets" << endl;
	cout << "3.Check the locations" << endl;
	cout << "4.Check ticket" << endl;
}

void readTickets() {
	//TESTING
	char evd[] = "10-10-2022 10:30";
	char evn[] = "Festival";
	char* evDate = new char[strlen(evd) + 1];
	evDate = evd;
	char* evName = new char[strlen(evn) + 1];
	evName = evn;
	Event ev(evDate, evName, 200);

	char locn[] = "Stadion";
	char* locName = new char[strlen(locn) + 1];
	locName = locn;
	Location loc(22, locName, 4000, 20);

	Ticket tWrite(ev, 40.0, false, loc, 22);
	fstream wf("ticket.dat", ios::out | ios::binary);
	if (!wf) {
		cout << "Cannot open file!" << endl;
		return;
	}
	wf.write((char*)&tWrite, sizeof(Ticket));
	wf.close();
	if (!wf.good()) {
		cout << "Error occurred at writing time!" << endl;
		return;
	}
	Ticket t;
	Ticket::readTicket(t, "ticket.dat");
	//
}

int main(int argc, char* argv[]) {
	vector<Location> locations;
	vector<Event> events;
	vector<Ticket> tickets;

	//read tickets

	readTickets();

	vector<int> commands;
	//in commands we store the option and all necessary arguments for each option
	if (argc == 2) {
		ifstream fin(argv[1]);

		if (fin.is_open()) {
			int command;
			while (fin >> command) {
				commands.push_back(command);
			}
		}
		else {
			std::cout << "Invalid file passed as argument" << endl;
			displayMenu();
		}
		fin.close();
	}
	else {
		std::cout << "No file passed as argument. Here is the menu:" << endl;
		return 0;
	}

	//TESTING
	//for (auto command : commands) {
	//	cout << command << " ";
	//}

	//cout << endl;
	//

	////Location location1;
	////cin >> location1;
	////cout << location1;
	////cout << endl;
	////Location::printLocation(location1);
	////cout << endl;
	////cout << "You have entered the location details succesfully";//we setted and called succesfully class location
	////Event event1;
	////cin >> event1;
	////cout << event1;
	////cout << endl;
	////Event::printEvent(event1);
	////cout << endl;
	////cout << "You have entered the event details succesfully";//we setted and called succesfully class event
	////Ticket ticket1;
	////cin >> ticket1;
	////cout << ticket1;
	////cout << endl;
	////Ticket::printTicket(ticket1);
	////cout << endl;
	////cout << "You have entered the ticket details succesfully";//we setted cand called succesfully class ticket


	//Hardcoded meniu when there are not tickets available for all the events
	while (true) {
		int choice;
		cout << "MENIU:" << endl;
		cout << "1.Let's see the events" << endl;
		cout << "2.Buy tickets" << endl;
		cout << "3.Check the locations" << endl;
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Upcoming events: " << endl;
			cout << "1.Untold" << endl;
			cout << "2.Neversea" << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				cout << "Untold: " << endl;
				cout << "Tickets sold out" << endl;

			case 2:
				cout << "Neversea: " << endl;
				cout << "Tickets sold out" << endl;

			}

		case 2:
			cout << "Tickets sold out: " << endl;


		case 3:
			cout << "Locations: " << endl;
			cout << "1. Cluj" << endl;
			cout << "2. Constanta" << endl;
			cin >> choice;
			switch (choice) {
			case 1:
				cout << "Cluj events: " << endl;
				cout << "Untold: tickets sold out" << endl;


			case 2:
				cout << "Constanta events: " << endl;
				cout << "Neversea: tickets sold out" << endl;

			}

		}



	}

	return 0;
}