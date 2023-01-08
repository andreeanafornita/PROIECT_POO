#pragma once
#include "Location.h"
#include <string.h>
class Event
{
private:
	string dateAndTime;
	string name;
	int eventId;
	Location location;
	int availableNoOfSeats;

private:
	int generateID() {
		int crtID = 0;
		//add all ASCII values of chars in name of event
		for (char c : this->name) {
			crtID += int(c);
		}
		//then add the current time
		//initialize time
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);
		//add year
		crtID += 1900 + ltm.tm_year;
		//add month
		crtID += 1 + ltm.tm_mon;
		//add day
		crtID += ltm.tm_mday;
		//add hour
		crtID += ltm.tm_hour;
		//add minute
		crtID += ltm.tm_min;
		//add second
		crtID += ltm.tm_sec;

		//finally add the location ID to it
		crtID += this->location.getLocationId();

		return crtID;
	}

public:
	Event(string dateAndTime, string name, Location location) {
		this->setDateAndTime(dateAndTime);
		this->setName(name);
		this->setLocation(location);
		this->availableNoOfSeats = this->location.getTotalNoOfSeats();
	}
	Event() {
		this->eventId = 0;
	}
	string getDateAndTime() {
		return this->dateAndTime;
	}
	string getName() {
		return this->name;
	}
	int getEventId() {
		return this->eventId;
	}
	Location getLocation() {
		return this->location;
	}
	int getAvailableNoOfSeats() const {
		return this->availableNoOfSeats;
	}
	void setDateAndTime(string dateAndTime) {
		if (dateAndTime.empty() || dateAndTime.length() == 0) {
			exit(1);
		}
		this->dateAndTime.clear();
		this->dateAndTime = dateAndTime;
	}

	void setName(string name) {
		if (name.empty() || name.length() == 0) {
			exit(1);
		}
		this->name.clear();
		this->name = name;
	}
	void setEventId(int eventId) {
		this->eventId = eventId;
	}
	void setLocation(Location location) {//this is a setter for class location
		this->location = location;
	}
	void setAvailableNoOfSeats(int availableNoOfSeats) {
		if (availableNoOfSeats > 0) {
			this->availableNoOfSeats = availableNoOfSeats;
		}
		else {
			cout << "Available number of seats might be greater than 0";
			exit(1);
		}
	}

	bool checkAvailability() {//this is also a method by which we can found out if there are or are no more available seats
		return this->availableNoOfSeats != 0;
	}
	void removeAvailableSeat(int seats) {//this is a setter who has a an integer variable "seats", who has the target to remove available seats if the client who wants a number of seats is less or equal than the available number of seats. if not, it will appear a warning message to the user
		if (this->availableNoOfSeats < seats) {
			cout << "There are less available seats than specified";
			exit(1);
		}
		this->availableNoOfSeats = this->availableNoOfSeats - seats;
	}
	/*~Event() {
	}*/

	void generateUniqueID(const vector<Event>& events) {
		bool isUnique = false;
		int crtID;

		while (!isUnique) {
			isUnique = true;
			crtID = generateID();
			for (const Event& ev : events) {
				if (ev.eventId == crtID) {
					isUnique = false;
				}
			}
		}
		this->eventId = crtID;
	}

	static Event* getEventFromID(int eventID, vector<Event>& events) {
		for (Event& ev : events) {
			if (ev.getEventId() == eventID) {
				return &ev;
			}
		}
		return nullptr;
	}

	static bool readEvent(Event& event, string fileName) {
		ifstream fin(fileName, ios::out | ios::binary);
		if (!fin) {
			cout << "Cannot open " << fileName << " for reading!" << endl;
			return false;
		}
		fin.read((char*)&event, sizeof(Event));
		fin.close();
		if (!fin.good()) {
			cout << "Error occurred while reading " << fileName << "!" << endl;
			return false;
		}
		return true;
	}

	static bool writeEvent(Event& ev, string path) {
		string fileName = path + "\\event" + to_string(ev.eventId) + ".dat";
		fstream wf(fileName, ios::out | ios::binary);
		if (!wf) {
			cout << "Cannot create file!" << endl;
			return false;
		}
		wf.write((char*)&ev, sizeof(Event));
		wf.close();
		if (!wf.good()) {
			cout << "Error occurred when writing event with ID " << ev.eventId << "!" << endl;
			return false;
		}
		return true;
	}

	void operator=(const Event& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}
		this->eventId = aux.eventId;
		this->dateAndTime = aux.dateAndTime;
		this->name = aux.name;
		this->location = aux.location;
	}
	bool operator==(const Event& e) const
	{
		if (this->eventId == e.eventId)
		{
			return true;
		}
		return false;
	}
	Event(const Event& aux1) {//this is a copy constructor
		this->name = aux1.name;
		this->eventId = aux1.eventId;
		this->dateAndTime = aux1.dateAndTime;
		this->location = aux1.location;
	}
	friend void operator<<(ostream& out, Event event);
	friend void operator>>(istream& in, Event& event);

	bool operator!() {//this is the "!" operator
		return this->getAvailableNoOfSeats() == 0;
	}

	bool operator>(Event& event) {
		return this->eventId > event.eventId;
	}
};

void operator<<(ostream& out, Event event) {//this is the operator "<<"
	out << "----------" << endl;
	out << endl << "Event id: " << event.eventId << endl;
	out << endl << "Event name: " << (!event.name.empty() ? string(event.name) : "No name") << endl;
	out << endl << "Date and time: " << (!event.dateAndTime.empty() ? string(event.dateAndTime) : "No date and time") << endl;
	out << endl << "Location is : " << event.location.getLocationName() << endl;
	out << "Number of seats available are: " << event.getAvailableNoOfSeats() << endl;
	out << "----------" << endl;
}
void operator>>(istream& in, Event& event) {//this is the operator">>"
	cout << endl << "Location ID: ";
	in >> event.eventId;
	cout << endl << "Name: ";
	char buffer[100];
	in >> buffer;
	event.setName(buffer);
	cout << endl << "Date and time: ";
	char buffer1[100];
	in >> buffer1;
	event.setDateAndTime(buffer1);
	in >> event.location;
}