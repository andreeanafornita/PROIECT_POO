#pragma once
#include "LocationInterface.h"
#include<iostream>
#include<ctime>
#include<vector>
using namespace std;
//this is a class named Location, it has a name, number of rows, number of seats per row, total number of seats that cand be easily found by multiplicatind the number of rows with number of seats per row, it also has an id who is attributed privately so no one can access the id, and available number of seats so we can decide if we can sell tickets more

bool tryParse(std::string& input, int& output) {
	try {
		output = std::stoi(input);
	}
	catch (std::invalid_argument) {
		return false;
	}
	return true;
}

class Location: virtual public LocationInterface {
private:
	int locationId;

private:
	int generateID() override {
		int crtID = 0;
		//add all ASCII values of chars in name of venue
		for (char c : this->getLocationName()) {
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

		return crtID;
	}

public:
	Location(string locationName, int noOfRows, int noOfSeatsPerRow): LocationInterface(locationName, noOfRows, noOfSeatsPerRow) {// this is a constrcutor that can be made either this way, or by writing as we do at courses (exp:this->location=location) but i think is much more easier like that because in the setter I did a lot of things to include conditions of existence and also the getters 
		this->locationId = -1;
	}
	Location() {
		this->locationId = 0;//this is the default constructor
	}

	void generateUniqueID(const vector<Location>& locations) {
		bool isUnique = false;
		int crtID;

		while (!isUnique) {
			isUnique = true;
			crtID = generateID();
			for (const Location& location : locations) {
				if (location.getLocationId() == crtID) {
					isUnique = false;
				}
			}
		}
		this->locationId = crtID;
	}

	static void printLocation(Location location) {//this is a static method that has the target to print the location from class Location
		cout << location;
	}

	int getLocationId() const {
		return this->locationId;
	}

	void setLocationId(int locationId) {//this is a normal setter without any condition because the ID can be every integer 
		this->locationId = locationId;
	}

	void operator=(const Location& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}

		this->setAvailableNoOfSeats(aux.getAvailableNoOfSeats());
		this->locationId = aux.locationId;
		this->setNoOfRows(aux.getNoOfRows());
		this->setNoOfSeatsPerRow(aux.getNoOfSeatsPerRow());
		this->setTotalNoOfSeats(aux.getTotalNoOfSeats());
		this->setLocationName(aux.getLocationName());
	}

	Location(const Location& aux) {//this is a copy constructor
		this->setLocationName(aux.getLocationName());
		this->locationId = aux.locationId;
		this->setAvailableNoOfSeats(aux.getAvailableNoOfSeats());
		this->setNoOfRows(aux.getNoOfRows());
		this->setNoOfSeatsPerRow(aux.getNoOfSeatsPerRow());
		this->setTotalNoOfSeats(aux.getTotalNoOfSeats());
	}
	friend void operator<<(ostream& out, Location location);
	friend void operator>>(istream& in, Location& location);

	bool operator!() {//this is the "!" operator
		return this->getAvailableNoOfSeats() == 0;
	}

	bool operator==(const Location& l) const
	{
		if (this->locationId == l.locationId)
		{
			return true;
		}
		return false;
	}

};
void operator<<(ostream& out, Location location) {//this is the operator "<<"
	out << "----------" << endl;
	out << "Location name: " << (!location.getLocationName().empty() ? location.getLocationName() : "No name") << endl;
	out << "Location id: " << location.locationId << endl;
	out << "Number of rows are :  " << location.getNoOfRows() << endl;
	out << "Number of seats available are: " << location.getAvailableNoOfSeats() << endl;
	out << "The number of seats per row are: " << location.getNoOfSeatsPerRow() << endl;
	out << "The total number of seats are: " << location.getTotalNoOfSeats() << endl;
	out << "----------" << endl;
}

void operator>>(istream& in, Location& location) {//this is the operator">>"
	//get name
	string name;
	std::cout << "Enter location name: ";
	getline(in, name);
	//

	//get number of rows
	string input;
	int numRows;
	std::cout << "Enter number of rows: ";
	getline(in, input);

	while (!tryParse(input, numRows)) {
		std::cout << "Bad entry. Enter a NUMBER: ";
		cin.clear();
		getline(in, input);
	}
	//

	//get number of seats per row
	input.clear();
	int numSeatsPerRow;
	std::cout << "Enter number of seats per row: ";
	//cin.clear();
	getline(in, input);

	while (!tryParse(input, numSeatsPerRow)) {
		std::cout << "Bad entry. Enter a NUMBER: ";
		cin.clear();
		getline(in, input);
	}
	//
	Location loc(name, numRows, numSeatsPerRow);
	location = loc;
}

bool operator==(Location& location1, Location& location2) {//this is the operator "=="
	return location1.getLocationId() == location2.getLocationId();
}
