#pragma once
#include "LocationInterface.h"
#include <string>
using namespace std;
class Area : virtual public LocationInterface {
private:
	int areaId;
	string type;
	string entrance;
	int noOfSeatsPerRow;
	int noOfRows;

private:
	int generateID() override {
		int crtID = 0;
		//add the current time - minimizes chances of duplicates
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
	Area(string areaName, int noOfRows, int noOfSeatsPerRow, string type, string entrance): LocationInterface(areaName, noOfRows * noOfSeatsPerRow) {
		this->type = type;
		this->entrance = entrance;
		this->areaId = -1;
	}

	Area() { 
		this->areaId = -1; 
	}

	void generateUniqueID(int locationID, vector<Area> areas) {
		bool isUnique = false;
		int crtID;

		while (!isUnique) {
			isUnique = true;
			crtID = generateID() + locationID;
			for (const auto& area : areas) {
				if (area.getAreaId() == crtID) {
					isUnique = false;
				}
			}
		}
		this->areaId = crtID;
	}

	string getZoneType()const
	{
		return this->type;
	}
	string getZoneEntrance() const
	{
		return this->entrance;
	}
	int getAreaId() const {
		return this->areaId;
	}
	int getNoOfRows() const {//this is the getter for number of rows, those getters must be done in order to work with the variables later, in fact they return the variable, that's why we use the word "return"
		return this->noOfRows;
	}
	int getNoOfSeatsPerRow() const {
		return this->noOfSeatsPerRow;
	}
	void setNoOfRows(int noOfRows) {//this is a setter which has a condition which says that the  number of rows can't be less than 0, because it means it doesn't exist, so if we put a number less than 0, will appear a warning message and the program will exit the code
		if (noOfRows > 0) {
			this->noOfRows = noOfRows;
		}
		else
		{
			cout << "no of rows needs to be greater than 0";
			exit(1);
		}
	}
	void setNoOfSeatsPerRow(int noOfSeatsPerRow) {//as we done in the number of rows, we put a condition on number of seats per row to avoid confusion, because it is logic that we can't have a number of seats per row less than 1, because if we have, it means it doesn't exist, so we also put here a warning message if the staff put the number wrongly, and after that warning message we exit the code. If the number is correct, we made a getter in order to get the number of seats per row in order to can work later with this variable
		if (noOfSeatsPerRow < 1) {
			cout << "number of seats must be greater or equal than 1";
			exit(1);
		}
		else {
			this->noOfSeatsPerRow = noOfSeatsPerRow;
		}
	}

	void setAreaId(int id) {
		this->areaId = id;
	}
	void setZoneType(string type)
	{
		this->type = type;
	}
	void setZoneEntrance(string entrance)
	{
		this->entrance = entrance;
	}

	static Area* getAreaFromID(int areaID, vector<Area>& areas) {
		for (Area& area : areas) {
			if (area.getAreaId() == areaID) {
				return &area;
			}
		}
		return nullptr;
	}

	static bool readArea(Area& area, string fileName) {
		ifstream fin(fileName, ios::out | ios::binary);
		if (!fin) {
			cout << "Cannot open " << fileName << " for reading!" << endl;
			return false;
		}
		fin.read((char*)&area, sizeof(Area));
		fin.close();
		if (!fin.good()) {
			cout << "Error occurred while reading " << fileName << "!" << endl;
			return false;
		}
		return true;
	}

	static bool writeArea(Area& area, string path) {
		string fileName = path + "\\area" + to_string(area.areaId) + ".dat";
		fstream wf(fileName, ios::out | ios::binary);
		if (!wf) {
			cout << "Cannot create file!" << endl;
			return false;
		}
		wf.write((char*)&area, sizeof(Area));
		wf.close();
		if (!wf.good()) {
			cout << "Error occurred when writing area with ID " << area.areaId << "!" << endl;
			return false;
		}
		return true;
	}

	void calculateTotalNoOfSeats(int noOfSeatsPerRow, int noOfRows) {//this is a method that helps us to calculate the total number of seats by simply multiplying number of seats per row with number of rows
		this->setTotalNoOfSeats(noOfSeatsPerRow * noOfRows);

	}
};

void operator>>(istream& in, Area& area) {
	//get name
	string name;
	std::cout << "Enter area name: ";
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

	//get area type
	string type;
	std::cout << "Enter area type: ";
	getline(in, type);
	//

	//get area entrance
	string entrance;
	std::cout << "Enter area entrance: ";
	getline(in, entrance);
	//

	Area a(name, numRows, numSeatsPerRow, type, entrance);
	area = a;
}
void operator<<(ostream& out, Area area) {
	out << "-----" << endl;
	out << "Area name: " << (!area.getLocationName().empty() ? area.getLocationName() : "No name") << endl;
	out << "Area id: " << area.getAreaId() << endl;
	out << "The total number of seats are: " << area.getTotalNoOfSeats() << endl;
	out << "Type of area: " << area.getZoneType() << endl;
	out << "Entrance: " << area.getZoneEntrance() << endl;
	out << "-----" << endl;
}