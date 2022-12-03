#pragma once
#include "Location.h"
#include"Event.h"//we should introduce on libraries those two, location and event because we want to include them in class "ticket"
class Ticket
{
private:
	Event event;
	float price;
	bool isUsed;
	Location location;//locatia din clasa Location
	 int id;

public:
	Ticket(Event event, float price, bool isUsed, Location location){//this is a constructor for class ticket, it may be implemented like this, with setters, or in a classic way:"this->variable=variable"
		this->setEvent(event);
		this->setPrice(price);
		this->setIsUsed(isUsed);
		this->setLocation(location);
		this->setId(id);
	}
	Ticket(){//this is the default constructor, uith initializer for the boolean variable in false
		this->isUsed = false;
	}

	Event getEvent() {//those 5 getters are initialized particulary for each variable with different types
		return this->event;
	}
	float getPrice() {
		return this->price;
	}
	bool getIsUsed() {
		return this->isUsed;
	}
	Location getLocation() {
		return this->location;
	}
	int getId() {
		return this->id;
	}
	void setEvent(Event event) {//after we create getters, we must create setters for the variables who are coming  with conditions for existence 
		this->event = event;
	}
	float setPrice(float price) {
		if (price == 0) {
			cout << "The price can't be negative ";//if the number introduced isn't introduced correctly, it will appear a warnings message
			exit(0);
		}
		else if (price == 0) {
			cout << "the price is 0, make sure if you want to give it for free ";
				this->price = price;
		}
	}
	bool setIsUsed(bool isUsed) {
		if (bool isUsed = false) {
			this->isUsed = isUsed = true;
		}
		else if (bool isUsed = true) {
			cout << "The ticket is aleready used";
				exit(0);
		}
	}
	Location setLocation(Location location) {//this is a setter for class location
		this->location = location;
	}
	int setId(int id) {
		this->id = id;
	}





	static void useTicket(Ticket ticket) {//this is a static method by which we can make a ticket from "not used" to "used"
		ticket.isUsed = true;
	}

	static bool checkTicket(Ticket ticket) {//this is a static method by which we can verify if a ticket is used or not
		return ticket.isUsed;
	}




	void operator=(const Ticket& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}
		this->event= aux.event;
		this->price = aux.price;
		this->isUsed = aux.isUsed;
		this->location = aux.location;
		this->id = aux.id;
	}

	Ticket(const Ticket& aux1) {//this is a copy constructor
		
		this->event = aux1.event;
		this->price = aux1.price;
		this->isUsed = aux1.isUsed;
		this->location = aux1.location;
		this->id = aux1.id;
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

void operator<<( ostream& out, Ticket ticket){//this is the output operator
	out << endl << "id: " << ticket.id;
	out << endl << "The event is: " << ticket.event; 
	out << endl << "price: " << ticket.price;
	out << endl << "is it used? : " << ticket.isUsed;
	out << endl << "location is : " << ticket.location;

	}
void operator>>(istream& in, Ticket& ticket) {//this is the input operator
	cout << endl << "id: ";
	in >> ticket.id;
	cout << endl << "event is: ";
	in >> ticket.event;
	cout << endl << "price: ";
	in >> ticket.price;
	cout << endl << "location is: ";
	in >> ticket.location;
	cout << endl << "is it used?";
	in >> ticket.isUsed;
	ticket.useTicket(ticket);
	ticket.checkTicket(ticket);
}





