#pragma once
#include "Location.h"
#include <string.h>
class Event
{
private:
	string dateAndTime;
	string name;
	int eventId;
	Location location;//locatia din clasa Location

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
	}
	Event() {
		this->eventId = 0;
	}
	string getDateAndTime(string dateAndTime) {
		return this->dateAndTime = dateAndTime;
	}
	string getName(string name) {
		return this->name = name;
	}
	int getEventId(int eventId) {
		return this->eventId = eventId;
	}
	Location getLocation() {
		return this->location;
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
		return this->eventId == 0;
	}
	bool operator>(Event& event) {
		return this->eventId > event.eventId;
	}

	static void printEvent(Event event) {//this is a static method that has the target to print the location from class Location
		cout << event;
	}

};

void operator<<(ostream& out, Event event) {//this is the operator "<<"
	out << "----------" << endl;
	out << endl << "Event id: " << event.eventId << endl;
	out << endl << "Event name: " << (!event.name.empty() ? string(event.name) : "No name") << endl;
	out << endl << "Date and time: " << (!event.dateAndTime.empty() ? string(event.dateAndTime) : "No date and time") << endl;
	out << endl << "Location is : " << event.location.getLocationName() << endl;
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