#pragma once

class Event
{
private:
	char* dateAndTime;
	char* name;
	int eventId;
public:
	Event(char* dateAndTime, char* name, int eventId) {
		this->setDateAndTime(dateAndTime);
		this->setEventId(eventId);
		this->setName(name);
	}
	Event(){  
		this->eventId = 0;
	}
	char* getDateAndTime(char* dateAndTime) {
		return this->dateAndTime = dateAndTime;
	}
	char* getName(char* name) {
		return this->name = name;
	}
	int getEventId(int eventId) {
		return this->eventId = eventId;
	}
	void setDateAndTime(char* dateAndTime) {
		if (dateAndTime == nullptr || strlen(dateAndTime) == 0) {
			exit(0);
		}
		if (this->dateAndTime != nullptr) {
			delete[] this->dateAndTime;
		}
		this->dateAndTime = new char[strlen(dateAndTime) + 1];
		strcpy(this->dateAndTime, dateAndTime);
	}

	void setName(char* name) {
		if (name == nullptr || strlen(name) == 0) {
			exit(0);
		}
		if (this->name != nullptr) {
			delete[] this->name;
		}
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
	}
	void setEventId(int eventId) {
		this->eventId = eventId;
	}

	~Event() {
		delete[] this->name;
		delete[] this->dateAndTime;
	}
	
	void operator=(const Event& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}
		this->eventId = aux.eventId;
		if (this->dateAndTime) {
			delete[] this->dateAndTime;
			this->dateAndTime = nullptr;
		}
		if (aux.dateAndTime) {
			this->dateAndTime = new char[strlen(aux.dateAndTime) + 1];
			strcpy(this->dateAndTime, aux.dateAndTime);
		}

		if (this->name) {
			delete[] this->name;
			this->name = nullptr;
		}
		if (aux.name) {
			this->name = new char[strlen(aux.name) + 1];
			strcpy(this->name, aux.name);
		}

	}
	Event(const Event& aux1) {//this is a copy constructor
		if (aux1.name != nullptr) {
			this->name = new char[strlen(aux1.name) + 1];
			memcpy(this->name, aux1.name, strlen(aux1.name) + 1);
		}
		else
		{
			this->name = nullptr;
		}
		this->eventId = aux1.eventId;
		if (aux1.dateAndTime != nullptr) {
			this->dateAndTime = new char[strlen(aux1.dateAndTime) + 1];
			memcpy(this->dateAndTime, aux1.dateAndTime, strlen(aux1.dateAndTime) + 1);
		}
		else {
			this->dateAndTime = nullptr;
		}
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
	out << endl << "Event id: " << event.eventId;
	out << endl << "Event name: " << (event.name != nullptr ? string(event.name) : "No name");
	out << endl << "Date and time: " << (event.dateAndTime != nullptr ? string(event.dateAndTime) : "No date and time");
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
}