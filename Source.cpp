#include<iostream>
#include<fstream>
#include<vector>
#include<filesystem>

#include "Location.h"
#include "Event.h"
#include "Ticket.h"

using namespace std;
namespace fs = std::filesystem;

void displayMenuOptions() {
	cout << "MENIU:" << endl;
	cout << "1.See all events" << endl;
	cout << "2.Generate tickets" << endl;
	cout << "3.Check a location" << endl;
	cout << "4.Check ticket" << endl;
	cout << "5.Use ticket" << endl;
	cout << "6.Create an event" << endl;
	cout << "7.Create a location" << endl;
	cout << "0.Exit" << endl;
}

bool tryParse(std::string& input, int& output) {
	try {
		output = std::stoi(input);
	}
	catch (std::invalid_argument) {
		return false;
	}
	return true;
}

bool useTicket(vector<Ticket>& tickets, int id) {
	for (Ticket& t : tickets) {
		if (t.getId() == id) {
			t.setIsUsed(true);
			return true;
			break;
		}
	}

	return false;
}

bool checkTicket(vector<Ticket>& tickets, int id) {
	bool found = false;
	for (Ticket& t : tickets) {
		if (t.getId() == id) {
			return t.getIsUsed();
			found = true;
			break;
		}
	}
	if (!found) {
		std::cout << "Could not find any ticket with id " << id << endl;
	}
}

bool checkLocation(vector<Location>& locations, string name) {
	
	for (Location& loc : locations) {
		if (loc.getlocationName() == name) {
			cout << loc;
			return true;
		}
	}

	return false;
}

bool checkLocation(vector<Location>& locations, int id) {
	for (Location& loc : locations) {
		if (loc.getLocationId() == id) {
			cout << loc;
			return true;
		}
	}

	return false;
}

void displayMenu(vector<Event>& events, vector<Location>& locations, vector<Ticket>& tickets) {
	int option;

	char locn[] = "Stadion";
	char* locName = new char[strlen(locn) + 1];
	locName = locn;
	Location loc(22, locName, 4000, 20);

	char evd[] = "10-10-2022 10:30";
	char evn[] = "Festival";
	char* evDate = new char[strlen(evd) + 1];
	evDate = evd;
	char* evName = new char[strlen(evn) + 1];
	evName = evn;
	Event ev(evDate, evName, loc, 200);


	Ticket tWrite(ev, 40.0, false, 22);
	tickets.push_back(tWrite);
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

	do {
		displayMenuOptions();
		string strOpt;
		std::getline(std::cin, strOpt);
		option = std::stoi(strOpt);
		if (option == 1) {
			//see all events
			for (Event ev : events) {
				std::cout << ev;
			}
		}
		else if (option == 2) {
			//generate tickets
			//TODO
		}
		else if (option == 3) {
			//check a location
			
			//get location id or name
			string input;
			int id;
			std::cout << "Enter location id or name: ";
			cin.clear();
			getline(std::cin, input);

			if (!tryParse(input, id)) {
				if (!checkLocation(locations, input)) {
					std::cout << "Could not find any location with name " << input << endl;
				}
			}
			else {
				if (!checkLocation(locations, id)) {
					std::cout << "Could not find any location with id " << id << endl;
				}
			}
		}
		else if (option == 4) {
			//check ticket

			//get ticket id
			string input;
			int id;
			std::cout << "Enter ticket id: ";
			cin.clear();
			getline(std::cin, input);

			while (!tryParse(input, id)) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				cin.clear();
				getline(std::cin, input);
			}
			
			//check the ticket
			if (checkTicket(tickets, id)) {
				std::cout << "The ticket with ID " << id << " has been used!" << endl;
			}
			else {
				std::cout << "The ticket with ID " << id << " has not used!" << endl;
			}

		}
		else if (option == 5) {
			//use ticket
			
			//get ticket id
			string input;
			int id;
			std::cout << "Enter ticket id: ";
			cin.clear();
			getline(std::cin, input);

			while (!tryParse(input, id)) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				cin.clear();
				getline(std::cin, input);
			}

			if (!useTicket(tickets, id)) {
				std::cout << "Could not find any ticket with id " << id << endl;
			}
		}
		else if (option == 6) {
			//create an event
			//date and time, name, Location(id/name), ID-auto-generated
			string dateAndTime, name;
			
			//get date and time
			std::cout << "Enter date and time of the event: ";
			cin.clear();
			getline(std::cin, dateAndTime);
			//

			//get name
			std::cout << "Enter name of the event: ";
			cin.clear();
			getline(std::cin, name);
			//
			
			//get location id or name
			string input;
			int id;
			std::cout << "Enter location id or name: ";
			cin.clear();
			getline(std::cin, input);

			if (!tryParse(input, id)) {
				if (!checkLocation(locations, input)) {
					std::cout << "Could not find any location with name " << input << endl;
					continue;
				}
			}
			else {
				if (!checkLocation(locations, id)) {
					std::cout << "Could not find any location with id " << id << endl;
					continue;
				}
			}
			//

			//todo: create event and add it to events vector

		}
		else if (option == 7) {
			//create a location
			
			//get name
			string name;
			std::cout << "Enter location name: ";
			cin.clear();
			getline(std::cin, name);
			//
			
			//get number of rows
			string input;
			int numRows;
			std::cout << "Enter number of rows: ";
			cin.clear();
			getline(std::cin, input);

			while (!tryParse(input, numRows)) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				cin.clear();
				getline(std::cin, input);
			}
			//

			//get number of seats per row
			input.clear();
			int numSeatsPerRow;
			std::cout << "Enter number of seats per row: ";
			cin.clear();
			getline(std::cin, input);

			while (!tryParse(input, numSeatsPerRow)) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				cin.clear();
				getline(std::cin, input);
			}
			//

			//todo: create the location and add it to vector
		}
		else if (option != 0) {
			std::cout << "Invalid choice" << endl;
		}
	} while (option != 0);
}

bool loadTickets(vector<Event>& events, vector<Location>& locations, vector<Ticket>& tickets) {
	//check if a directory named tickets exists
	fs::path dirPath = string(".\\tickets");

	if (fs::is_directory(dirPath)) {
		cout << "Found directory named \"tickets\". Reading tickets..." << endl;
	}
	else {
		cout << "Did not find diretory named \"tickets\". Creating it ..." << endl;
		if (!fs::create_directory(dirPath)) {
			cout << "Could not create directory named \"tickets\". Exiting..." << endl;
			exit(1);
		}
		else {
			cout << "Successfully created directory \"tickets\"" << endl;
		}
		return false;
	}

	//get all files in that directory
	for (const auto& dirEntry : fs::recursive_directory_iterator(dirPath)) {
		string path = string(dirEntry.path().u8string());
		//std::cout << string(dirEntry.path().u8string()) << endl;
		Ticket t;
		if (Ticket::readTicket(t, string(dirEntry.path().u8string()))) {
			//successfully read ticket - add it to the list
			tickets.push_back(t);
			//load event in vector of events - if it does not already exist
			if (find(events.begin(), events.end(), t.getEvent()) != events.end()) {
				events.push_back(t.getEvent());
			}
			//load location in vector of locations - if it does not already exist
			if (find(locations.begin(), locations.end(), t.getEvent().getLocation()) != locations.end()) {
				locations.push_back(t.getEvent().getLocation());
			}
		}
		else {
			//did not succesfully read ticket
		}
	}
	return true;
}

int main(int argc, char* argv[]) {
	vector<Event> events;
	vector<Location> locations;
	vector<Ticket> tickets;

	displayMenu(events, locations, tickets);

	//load tickets
	if (loadTickets(events, locations, tickets)) {
		cout << "Successfully loaded " << tickets.size() << " tickets and " << events.size() << " events" << endl;
	}
	else {
		cout << "Could not load tickets";
	}

	//read commands from file - if file is needed
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
			displayMenu(events, locations, tickets);
		}
		fin.close();
	}
	else {
		std::cout << "No file passed as argument. Here is the menu:" << endl;
		displayMenu(events, locations, tickets);
		return 0;
	}

	//TESTING
	//for (auto command : commands) {
	//	cout << command << " ";
	//}

	return 0;
}