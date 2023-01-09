#include<iostream>
#include<fstream>
#include<vector>
#include<filesystem>

#include "Location.h"
#include "Event.h"
#include "Ticket.h"

using namespace std;
namespace fs = std::filesystem;

const string locationsPathString = ".\\data\\locations";
const string eventsPathString = ".\\data\\events";
const string ticketsPathString = ".\\data\\tickets";

void displayMenuOptions() {
	cout << "MENIU:" << endl;
	cout << "1.See all events" << endl;
	cout << "2.Generate tickets" << endl;
	cout << "3.Check a location" << endl;
	cout << "4.Check ticket" << endl;
	cout << "5.Use ticket" << endl;
	cout << "6.Create an event" << endl;
	cout << "7.Create a location" << endl;
	cout << "8.See all locations" << endl;
	cout << "0.Exit" << endl;
}

Ticket getTicketFromID(vector<Ticket>& tickets, int id, bool& found) {
	found = false;
	for (Ticket& t : tickets) {
		if (t.getId() == id) {
			found = true;
			return t;
		}
	}
	if (!found) {
		std::cout << "Could not find any ticket with id " << id << endl;
	}
}

void useTicket(vector<Ticket>& tickets, int id) {
	for (Ticket& t : tickets) {
		if (t.getId() == id) {
			if (t.useTicket()) {
				cout << "Ticket has been used." << endl;
			}
			break;
		}
	}
}

Location checkLocation(vector<Location>& locations, string name, bool& found) {
	found = false;
	for (Location& loc : locations) {
		if (loc.getLocationName() == name) {
			found = true;
			return loc;
		}
	}
	//return a dummy location so no errors will appear
	return Location("dummy", 1);
}

Location checkLocation(vector<Location>& locations, int id, bool& found) {
	found = false;
	for (Location& loc : locations) {
		if (loc.getLocationId() == id) {
			found = true;
			return loc;
		}
	}
	//return a dummy location so no errors will appear
	return Location("dummy", 1);
}

bool checkDirectory(fs::path path) {
	if (fs::is_directory(path)) {
		cout << "Found directory at \"" << path.u8string() << "\". Reading contents..." << endl;
	}
	else {
		cout << "Did not find diretory at \"" << path.u8string() << "\". Creating it ..." << endl;
		if (!fs::create_directory(path)) {
			cout << "Could not create directory named \"" << path.u8string() << "\". Exiting..." << endl;
			return false;
		}
		else {
			cout << "Successfully created directory \"" << path.u8string() << "\"" << endl;
		}
	}
	return true;
}

void displayMenu(vector<Event>& events, vector<Location>& locations, vector<Ticket>& tickets, istream& iStream, bool commandFile) {
	int option;
	do {
		if (!commandFile) {
			displayMenuOptions();
		}
		string strOpt;
		getline(iStream, strOpt);
		if (commandFile && iStream.eof()) {
			return;
		}
		while (!tryParse(strOpt, option) && !commandFile) {
			std::cout << "Bad entry. Enter a NUMBER: ";
			getline(iStream, strOpt);
		}
		if (option == 1) {
			//see all events
			int count = 1;
			for (Event ev : events) {
				cout << endl << "EVENT #" << count++ << endl;
				std::cout << ev;
			}
		}
		else if (option == 2) {
			//generate tickets

			//print all available events
			cout << "All the events available:" << endl;
			bool ok = false;
			for (Event ev : events)
			{
				std::cout << "-" << ev.getName() << std::endl;
			}

			//get the wanted events' index
			int crtEvIndex;
			do {
				string name;
				std::cout << "Enter name of the event: ";
				getline(iStream, name);
				for (int i = 0 ; i < events.size(); i++)
				{
					if (events[i].getName() == name)
					{
						crtEvIndex = i;
						ok = true;
					}
				}
				if (!ok)
				{
					cout << "Could not find event " << name << endl;
				}

			} while (!ok);

			//ask for price of tickets
			string input;
			int price;
			std::cout << "Enter ticket price: ";
			getline(iStream, input);
			while (!tryParse(input, price) && !commandFile) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				getline(iStream, input);
			}

			//display available seats and ask how many tickets to create
			cout << "The selected event has " << events[crtEvIndex].getAvailableNoOfSeats() << " seats available!" << endl;
			int noTickets;
			do {
				std::cout << "Enter how many tickets to create: ";
				getline(iStream, input);
				while (!tryParse(input, noTickets) && !commandFile) {
					std::cout << "Bad entry. Enter a NUMBER: ";
					//iStream.clear();
					getline(iStream, input);
				}
				if (noTickets > events[crtEvIndex].getAvailableNoOfSeats()) {
					cout << "There are not that many available seats. Please enter a lower number!" << endl;
				}
				if (noTickets <= 0) {
					cout << "Cannot generate " << noTickets << " tickets. Please enter a positive number!" << endl;
				}
			} while (noTickets > events[crtEvIndex].getAvailableNoOfSeats() && noTickets <= 0);

			//update event and save it with the updated information
			events[crtEvIndex].removeAvailableSeats(noTickets);
			if (!Event::writeEvent(events[crtEvIndex], eventsPathString)) {
				cout << "Could not update number of available seats in event! Tickets have not been generated!" << endl;
				continue;
			}

			while (noTickets > 0)
			{
				Ticket t(events[crtEvIndex].getEventId(), price);
				Ticket::writeTicket(t, ticketsPathString);
				noTickets--;
			}
		}
		else if (option == 3) {
			//check a location

			//get location id or name
			string input;
			int id;
			std::cout << "Enter location id or name: ";
			getline(iStream, input);

			bool found;
			if (!tryParse(input, id)) {
				Location loc = checkLocation(locations, input, found);
				if (!found) {
					std::cout << "Could not find any location with name " << input << endl;
				}
				else {
					std::cout << loc;
				}
			}
			else {
				Location loc = checkLocation(locations, id, found);
				if (!found) {
					std::cout << "Could not find any location with id " << id << endl;
				}
				else {
					std::cout << loc;
				}
			}
		}
		else if (option == 4) {
			//check ticket

			//get ticket id
			string input;
			int id;
			std::cout << "Enter ticket id: " << endl;
			getline(iStream, input);

			while (!tryParse(input, id) && !commandFile) {
				std::cout << "Bad entry. Enter a NUMBER: " << endl;
				getline(iStream, input);
			}

			//check the ticket
			bool found;
			Ticket t = getTicketFromID(tickets, id, found);
			bool used = t.getIsUsed();
			if (found && used) {
				std::cout << "The ticket with ID " << id << " has been used!" << endl;
			}
			else if(found && !used) {
				std::cout << "The ticket with ID " << id << " has not been used!" << endl;
			}
			else {
				std::cout << "Could not find any ticket with id " << id << endl;
			}

		}
		else if (option == 5) {
			//use ticket

			//get ticket id
			string input;
			int id;
			std::cout << "Enter ticket id: " << endl;
			getline(iStream, input);

			while (!tryParse(input, id) && !commandFile) {
				std::cout << "Bad entry. Enter a NUMBER: " << endl;
				getline(iStream, input);
			}

			bool found;
			Ticket t = getTicketFromID(tickets, id, found);
			if (!found) {
				std::cout << "Could not find any ticket with id " << id << endl;
			}
			else {
				useTicket(tickets, id);
				t.useTicket();
				Ticket::writeTicket(t, ticketsPathString);
			}
		}
		else if (option == 6) {
			//create an event
			//date and time, name, Location(id/name), ID-auto-generated
			string dateAndTime, name;

			//get date and time
			std::cout << "Enter date and time of the event: ";
			getline(iStream, dateAndTime);
			//

			//get name
			std::cout << "Enter name of the event: ";
			getline(iStream, name);
			//

			//try to find location by id/name
			bool found;
			Location loc;
			do {
				//get location id or name
				string input;
				int id;
				std::cout << "Enter location id or name: ";
				getline(iStream, input);

				//try to find the location
				if (!tryParse(input, id)) {
					loc = checkLocation(locations, input, found);
					if (!found) {
						std::cout << "Could not find any location with name " << input << endl;
					}
				}
				else {
					Location loc = checkLocation(locations, id, found);
					if (!found) {
						std::cout << "Could not find any location with id " << id << endl;
					}
				}
			} while (!found);
			//

			//create the event
			Event ev(dateAndTime, name, loc);

			//generate an ID for the event
			ev.generateUniqueID(events);

			//write the event to file
			Event::writeEvent(ev, eventsPathString);

			events.push_back(ev);

		}
		else if (option == 7) {
			//create a location
			Location loc;

			//read the details about the location
			iStream >> loc;

			//initialize the ID
			loc.generateUniqueID(locations);

			//write the location to file
			Location::writeLocation(loc, locationsPathString);
			locations.push_back(loc);
		}
		else if (option == 8) {
		int count = 1;
			for (Location& loc : locations) {
				cout << endl << "LOCATION #" << count++ << endl;
				cout << loc;
			}
		}
		else if (option != 0) {
			std::cout << "Invalid choice" << endl;
		}
	} while (option != 0);
}

bool loadLocations(fs::path path, vector<Location>& locations) {
	for (const auto& dirEntry : fs::recursive_directory_iterator(path)) {
		string path = string(dirEntry.path().u8string());
		Location l;
		if (Location::readLocation(l, string(dirEntry.path().u8string()))) {
			//successfully read location - add it to the list
			locations.push_back(l);
		}
		else {
			//did not succesfully read location
		}
	}
	return true;
}

bool loadEvents(fs::path path, vector<Event>& events) {
	for (const auto& dirEntry : fs::recursive_directory_iterator(path)) {
		string path = string(dirEntry.path().u8string());
		Event e;
		if (Event::readEvent(e, string(dirEntry.path().u8string()))) {
			//successfully read event - add it to the list
			events.push_back(e);
		}
		else {
			//did not succesfully read event
		}
	}
	return true;
}

bool loadTickets(fs::path path, vector<Ticket>& tickets) {

	for (const auto& dirEntry : fs::recursive_directory_iterator(path)) {
		string path = string(dirEntry.path().u8string());
		Ticket t;
		if (Ticket::readTicket(t, string(dirEntry.path().u8string()))) {
			//successfully read ticket - add it to the list
			tickets.push_back(t);
		}
		else {
			//did not succesfully read ticket
		}
	}
	return true;
}

void loadData(vector<Location>& locations, vector<Event>& events, vector<Ticket>& tickets) {
	//check if a directory named data exists
	fs::path dataPath = string(".\\data");
	if (!checkDirectory(dataPath)) {
		exit(1);
	}
	//get all files in that directory
	fs::path ticketsPath = ticketsPathString;
	if (!checkDirectory(ticketsPath)) {
		exit(1);
	}
	fs::path eventsPath = eventsPathString;
	if (!checkDirectory(eventsPath)) {
		exit(1);
	}
	fs::path locationsPath = locationsPathString;
	if (!checkDirectory(locationsPath)) {
		exit(1);
	}

	loadLocations(locationsPath, locations);
	loadEvents(eventsPath, events);
	loadTickets(ticketsPath, tickets);
}

int main(int argc, char* argv[]) {
	vector<Event> events;
	vector<Location> locations;
	vector<Ticket> tickets;

	//load tickets
	loadData(locations, events, tickets);

	//read commands from file - if file is needed
	vector<int> commands;
	//in commands we store the options and all necessary arguments for each option
	if (argc == 2) {
		ifstream fin(argv[1]);
		//displayMenu(events, locations, tickets, fin);
		if (fin.is_open()) {
			displayMenu(events, locations, tickets, fin, true);
		}
		else {
			std::cout << "Invalid file passed as argument" << endl;
			displayMenu(events, locations, tickets, cin, false);
		}
		fin.close();
	}
	else {
		std::cout << "No file passed as argument. Here is the menu:" << endl;
		displayMenu(events, locations, tickets, cin, false);
		return 0;
	}

	return 0;
}