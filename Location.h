#pragma once
#include "LocationInterface.h"
#include "Area.h"
#include<iostream>
#include<ctime>
#include<vector>
using namespace std;
//this is a class named Location, it has a name, number of rows, number of seats per row, total number of seats that cand be easily found by multiplicatind the number of rows with number of seats per row, it also has an id who is attributed privately so no one can access the id, and available number of seats so we can decide if we can sell tickets more

class Location: virtual public LocationInterface {
private:
	int locationId;
	vector<Area> areas;

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
	Location(string locationName, int totalNoOfSeats) : LocationInterface(locationName, totalNoOfSeats) {
		this->locationId = -1;
	}
	Location(string locationName, int totalNoOfSeats, vector<Area> areas) : LocationInterface(locationName, totalNoOfSeats) {// this is a constrcutor that can be made either this way, or by writing as we do at courses (exp:this->location=location) but i think is much more easier like that because in the setter I did a lot of things to include conditions of existence and also the getters 
		this->locationId = -1;
		this->areas = areas;
	}
	Location() = default;

	void setLocationName(string locationName) {
		this->locationName = locationName; //override because the location name can be left empty
	}

	void setTotalNoOfSeats(int totalNoOfSeats) {
		if (totalNoOfSeats > 0) {
			this->totalNoOfSeats = totalNoOfSeats;
		}
		else {
			cout << "Total number of seats might be greater than 0";
			exit(1);
		}
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

	static bool readLocation(Location& location, ifstream& fin) {
		if (!fin) {
			cout << "Error while reading location for event!" << endl;
			return false;
		}
		string tmpLocationName;
		getline(fin, tmpLocationName);
		location.setLocationName(tmpLocationName);

		string tmpSeatsNo;
		getline(fin, tmpSeatsNo);
		location.setTotalNoOfSeats(stoi(tmpSeatsNo));

		string tmpLocationId;
		getline(fin, tmpLocationId);
		location.setLocationId(stoi(tmpLocationId));

		while (!fin.eof())
		{
			Area a;
			if (Area::readArea(a, fin)) {
				location.areas.push_back(a);
			}
		}
		return true;
	}

	static bool readLocation(Location& location, string fileName) {
		ifstream fin(fileName);
		if (!fin) {
			cout << "Cannot open " << fileName << " for reading!" << endl;
			return false;
		}
		string tmpLocationName;
		getline(fin, tmpLocationName);
		location.setLocationName(tmpLocationName);

		string tmpSeatsNo;
		getline(fin, tmpSeatsNo);
		location.setTotalNoOfSeats(stoi(tmpSeatsNo));

		string tmpLocationId;
		getline(fin, tmpLocationId);
		location.setLocationId(stoi(tmpLocationId));

		while (!fin.eof())
		{
			Area a;
			if (Area::readArea(a, fin)) {
				location.areas.push_back(a);
			}
		}
		fin.close();
		return true;
	}

	static bool writeLocation(Location& loc, ofstream& wf) {
		if (!wf) {
			cout << "Error while writing!" << endl;
			return false;
		}
		wf << loc.getLocationName() << endl;
		wf << loc.getTotalNoOfSeats() << endl;
		wf << loc.locationId << endl;

		for (Area& area : loc.areas) {
			Area::writeArea(area, wf);
		}

		if (!wf.good()) {
			cout << "Error occurred when writing location with ID " << loc.locationId << "!" << endl;
			return false;
		}
		return true;
	}

	static bool writeLocation(Location& loc, string path) {
		string fileName = path + "\\location" + to_string(loc.locationId) + ".dat";
		ofstream wf(fileName);
		if (!wf) {
			cout << "Cannot create file!" << endl;
			return false;
		}
		wf << loc.getLocationName() << endl;
		wf << loc.getTotalNoOfSeats() << endl;
		wf << loc.locationId << endl;

		for (Area& area : loc.areas) {
			Area::writeArea(area, wf);
		}

		wf.close();
		if (!wf.good()) {
			cout << "Error occurred when writing location with ID " << loc.locationId << "!" << endl;
			return false;
		}
		return true;
	}

	int getLocationId() const {
		return this->locationId;
	}

	vector<Area> getAreas() const {
		return this->areas;
	}

	void setAreas(vector<Area> areas) {
		this->areas = areas;
	}

	void setLocationId(int locationId) {//this is a normal setter without any condition because the ID can be every integer 
		this->locationId = locationId;
	}

	void operator=(const Location& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}

		this->locationName = aux.getLocationName();
		this->locationId = aux.locationId;
		this->totalNoOfSeats = aux.getTotalNoOfSeats();
		this->areas = aux.getAreas();
	}

	Location(const Location& aux) {//this is a copy constructor
		this->locationName = aux.getLocationName();
		this->locationId = aux.locationId;
		this->totalNoOfSeats = aux.getTotalNoOfSeats();
		this->areas = aux.getAreas();
	}
	friend void operator<<(ostream& out, Location location);
	friend void operator>>(istream& in, Location& location);

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
	out << endl << "----------" << endl;
	out << "Location name: " << (!location.getLocationName().empty() ? location.getLocationName() : "No name") << endl;
	out << "Location id: " << location.locationId << endl;
	out << "The total number of seats are: " << location.getTotalNoOfSeats() << endl;
	out << "--AREAS--" << endl;
	for (const Area& area : location.getAreas()) {
		out << area;
	}
	out << "----------" << endl;
}

void operator>>(istream& in, Location& location) {//this is the operator">>"
	//get name
	string name;
	std::cout << "Enter location name: ";
	getline(in, name);
	//

	//get number of seats
	string input;
	int numSeats;
	std::cout << "Enter the total number of seats: ";
	getline(in, input);

	while (!tryParse(input, numSeats)) {
		std::cout << "Bad entry. Enter a NUMBER: ";
		getline(in, input);
	}
	//

	Location loc(name, numSeats);

	//get all areas
	//create areas
	int option;
	int totalSeatsInAreas = 0;
	vector<Area> areas;
	do {
		//Ask player to create an area
		std::cout << "Do you want to create an area?" << endl << "1. Yes" << endl << "0. No" << endl;
		getline(in, input);
		while (!tryParse(input, option)) {
			std::cout << "Bad entry. Enter a NUMBER: ";
			getline(in, input);
		}
		if (option == 1) {
			Area a;
			in >> a;
			if (totalSeatsInAreas + a.getTotalNoOfSeats() > loc.getTotalNoOfSeats()) {
				std::cout << "There are too many seats in areas! Please enter a smaller number!" << endl;
				std::cout << "There are " << loc.getTotalNoOfSeats() - totalSeatsInAreas << " seats left in \"General\" (without a specific area assigned)" << endl;
			}
			else {
				totalSeatsInAreas += a.getTotalNoOfSeats();
				a.generateUniqueID(loc.getLocationId(), areas);
				areas.push_back(a);
			}
		}

	} while (option != 0);
	//if done, assign all seats left to "General" area
	if (totalSeatsInAreas < loc.getTotalNoOfSeats()) {
		//get number of rows
		string input;
		bool ok;
		int numRows;
		int numSeatsPerRow;

		do {
			ok = true;
			std::cout << "Enter number of rows for General area: ";
			getline(in, input);

			while (!tryParse(input, numRows)) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				getline(in, input);
			}
			//

			//get number of seats per row
			std::cout << "Enter number of seats per row for General area: ";
			getline(in, input);

			while (!tryParse(input, numSeatsPerRow)) {
				std::cout << "Bad entry. Enter a NUMBER: ";
				cin.clear();
				getline(in, input);
			}
			//
			if (numRows * numSeatsPerRow > loc.getTotalNoOfSeats() - totalSeatsInAreas) {
				std::cout << "There are not as many seats in this location! Please enter different numbers" << endl;
				ok = false;
			}
		} while (!ok);
		//get area entrance
		string entrance;
		std::cout << "Enter area entrance for General area: ";
		getline(in, entrance);
		//

		//create the area and add the leftover seats to the total number of seats
		Area a("General", numRows, numSeatsPerRow, "General access", entrance);
		totalSeatsInAreas += a.getTotalNoOfSeats();
		if (totalSeatsInAreas < loc.getTotalNoOfSeats()) {
			a.setTotalNoOfSeats(a.getTotalNoOfSeats() + (loc.getTotalNoOfSeats() - totalSeatsInAreas));
		}
		//generate ID
		a.generateUniqueID(loc.getLocationId(), areas);
		areas.push_back(a);
	}

	//
	loc.setAreas(areas);
	location = loc;
}

bool operator==(Location& location1, Location& location2) {//this is the operator "=="
	return location1.getLocationId() == location2.getLocationId();
}
