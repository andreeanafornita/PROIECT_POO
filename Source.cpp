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

int main(int argc, char *argv[]) {

	//before this read all tickets created before from binary file
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
		std::cout << "HERE";
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
		cout << "MENIU:"<<endl;
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