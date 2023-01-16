#pragma once
#include <fstream>
#include <string>
#include <random>
#include "Event.h"
#include "Area.h"

class Ticket
{
private:
	int eventID;
	int areaID;
	float price;
	bool isUsed;
	int id;

private:
	int generateID() {
		int crtID = 0;
		//add the event ID and the area ID
		crtID += this->eventID + this->areaID;
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

		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, INT_MAX/4);

		crtID += distr(eng);

		return abs(crtID);
	}

public:
	Ticket(int eventID, float price) {//this is a constructor for class ticket, it may be implemented like this, with setters, or in a classic way:"this->variable=variable"
		this->setEventId(eventID);
		this->setPrice(price);
		this->isUsed = false;
		this->setId(generateID());
	}
	Ticket() = default;
		
	static bool readTicket(Ticket& ticket, string fileName) {
		ifstream fin(fileName, ios::out | ios::binary);
		if (!fin) {
			cout << "Cannot open " << fileName << " for reading!" << endl;
			return false;
		}
		fin.read((char*)&ticket, sizeof(Ticket));
		fin.close();
		if (!fin.good()) {
			cout << "Error occurred while reading " << fileName << "!" << endl;
			return false;
		}
		return true;
	}

	static bool writeTicket(Ticket& ticket, string path) {
		string fileName = path + "\\ticket" + to_string(ticket.id) + ".dat";
		fstream wf(fileName, ios::out | ios::binary);
		if (!wf) {
			cout << "Cannot create file!" << endl;
			return false;
		}
		wf.write((char*)&ticket, sizeof(Ticket));
		wf.close();
		if (!wf.good()) {
			cout << "Error occurred when writing ticket with ID " << ticket.id << "!" << endl;
			return false;
		}
		return true;
	}

	int getEventId() {//those 5 getters are initialized particulary for each variable with different types
		return this->eventID;
	}
	float getPrice() {
		return this->price;
	}
	bool getIsUsed() {
		return this->isUsed;
	}
	int getId() {
		return this->id;
	}
	void setEventId(int eventID) {//after we create getters, we must create setters for the variables who are coming  with conditions for existence 
		this->eventID = eventID;
	}
	void setPrice(float price) {
		if (price < 0) {
			cout << "The price can't be negative ";//if the number introduced isn't introduced correctly, it will appear a warnings message
			exit(1);
		}
		else {
			if (price == 0) {
				cout << "the price is 0, make sure if you want to give it for free ";
			}
			this->price = price;
		}
	}
	void setId(int id) {
		this->id = id;
	}

	bool useTicket() {//this is a static method by which we can make a ticket from "not used" to "used"
		if (!this->isUsed) {
			this->isUsed = true;
			return true;
		}
		else {
			cout << "The ticket with ID " << this->id << " has already been used"<<endl;
			return false;
		}
	}

	bool checkTicket(Ticket ticket) {//this is a static method by which we can verify if a ticket is used or not
		return ticket.isUsed;
	}

	

	void operator=(const Ticket& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}
		this->eventID = aux.eventID;
		this->price = aux.price;
		this->isUsed = aux.isUsed;
		this->id = aux.id;
		this->areaID = areaID;
	}
	bool operator==(const Ticket& t) const
	{
		if (this->id == t.id && this->eventID == t.eventID)
		{
			return true;
		}
		return false;
	}
	Ticket(const Ticket& aux1) {//this is a copy constructor

		this->eventID = aux1.eventID;
		this->price = aux1.price;
		this->isUsed = aux1.isUsed;
		this->id = aux1.id;
		this->areaID = areaID;
	}
	friend void operator<<(ostream& out, Ticket ticket);
	friend void operator>>(istream& in, Ticket& ticket);

	bool operator!() {//this is the "!" operator
		return this->id == 0;
	}

	bool operator>(Ticket& ticket) {
		return this->id > ticket.id;
	}

	static void printTicket(Ticket ticket) {//this is a static method that has the target to print the location from class Location
		cout << ticket;
	}

};

void operator<<(ostream& out, Ticket ticket) {//this is the output operator
	out << "----------" << endl;
	out << "id: " << ticket.id << endl;
	out << "The eventID is: " << ticket.eventID;
	out << endl << "price: " << ticket.price << endl;
	out << "is it used? : " << ticket.isUsed << endl;
	out << "----------" << endl;
}
void operator>>(istream& in, Ticket& ticket) {//this is the input operator
	//not used
	cout << endl << "id: ";
	in >> ticket.id;
	cout << endl << "event is: ";
	in >> ticket.eventID;
	cout << endl << "price: ";
	in >> ticket.price;
	cout << endl << "is it used?";
	in >> ticket.isUsed;
	ticket.useTicket();
	ticket.checkTicket(ticket);
}
