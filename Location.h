#pragma once
#include<iostream>
using namespace std;


class Location {
private:
	char* locationName;
	int noOfRows;
	int noOfSeatsPerRow;
	int totalNoOfSeats = 0;
	int locationId;
	int availableNoOfSeats;

public:
	Location(int locationId,char* locationName, int noOfRows, int noOfSeatsPerRow) {
		this->setLocationId(locationId);
		this->setLocationName(locationName);
		this->setNoOfRows(noOfRows);
		this->setNoOfSeatsPerRow(noOfSeatsPerRow);
		this->calculateTotalNoOfSeats();
		this->calculateAvailableNoOfSeats();
	}
	Location() {
		this->locationId = 0;
}

	int getNoOfRows() {
		return this->noOfRows;
	}
	char* getlocationName() {
		return this->locationName;
	}
	int getNoOfSeatsPerRow() {
		return this->noOfSeatsPerRow;
	}
	int getTotalNoOfSeats() {
		return this->totalNoOfSeats;
	}
	int getLocationId() {
		return this->locationId;
	}
	int getAvailableNoOfSeats() {
		return this->availableNoOfSeats;
	}

	static void printLocation(Location location) {
		cout << location;
	}
	void setNoOfRows(int noOfRows) {
		if (noOfRows > 0) {
			this->noOfRows = noOfRows;
		}
		else
		{
			cout << "no of rows needs to be greater than 0";
			exit(0);
		}
	}
	void setLocationName(char* locationName) {
		if (locationName == nullptr || strlen(locationName) == 0) {
			exit(0);
		}
		if (this->locationName != nullptr) {
			delete[] this->locationName;
		}
		this->locationName = new char[strlen(locationName) + 1];
		strcpy(this->locationName, locationName);

	}
	void setNoOfSeatsPerRow(int noOfSeatsPerRow) {
		if (noOfSeatsPerRow < 1) {
			cout << "number of seats must be greater or equal than 1";
			exit(0);
		}
		else {
			this->noOfSeatsPerRow = noOfSeatsPerRow;
		}
	}
	void calculateTotalNoOfSeats() {
		if (this->noOfSeatsPerRow > 0 && this->noOfRows > 0 ) {
			this->totalNoOfSeats = noOfSeatsPerRow * noOfRows;
		}

	}
	void setTotalNoOfSeats(int totalNoOfSeats) {
		if (totalNoOfSeats > 0) {
			this->totalNoOfSeats = totalNoOfSeats;
		}
		else {
			cout << "Total number of seats might be greater than 0";
			exit(0);
		}
	}
	void setAvailableNoOfSeats(int availableNoOfSeats) {
		if (availableNoOfSeats > 0) {
			this->availableNoOfSeats = availableNoOfSeats;
		}
		else {
			cout << "Available number of seats might be greater than 0";
		}
	}
	void setLocationId(int locationId) {
		this->locationId = locationId;
	}
	void calculateAvailableNoOfSeats() {
		this->availableNoOfSeats = this->totalNoOfSeats;
	}
	~Location() {
		delete[] this->locationName;
	}
	bool checkAvailability() {
		return this->availableNoOfSeats != 0;
	}
	void removeAvailableSeat(int seats) {
		if (this->availableNoOfSeats < seats) {
			cout << "There are less available seats than specified";
			exit(0);
		}
		this->availableNoOfSeats = this->availableNoOfSeats - seats;
	}

	void operator=(const Location& aux) {
		if (this == &aux) {
			return;
		}
		this->availableNoOfSeats = aux.availableNoOfSeats;
		this->locationId = aux.locationId;
		this->noOfRows = aux.noOfRows;
		this->noOfSeatsPerRow = aux.noOfSeatsPerRow;
		this->totalNoOfSeats = aux.totalNoOfSeats;
		if (this->locationName ) {
			delete[] this->locationName;
			this->locationName = nullptr;
		}
		if (aux.locationName) {
			this->locationName = new char[strlen(aux.locationName) + 1];
			strcpy(this->locationName, aux.locationName);
		}
	}

	Location(const Location& aux1) {
		if (aux1.locationName != nullptr) {
			this->locationName = new char[strlen(aux1.locationName) + 1];
			memcpy(this->locationName, aux1.locationName, strlen(aux1.locationName) + 1);
		}
		else
		{
			this->locationName = nullptr;
		}
		this->locationId = aux1.locationId;
		this->availableNoOfSeats = aux1.availableNoOfSeats;
		this->noOfRows = aux1.noOfRows;
		this->noOfSeatsPerRow = aux1.noOfSeatsPerRow;
		this->totalNoOfSeats = aux1.totalNoOfSeats;
	}
	friend void operator<<(ostream& out, Location location);
	friend void operator>>(istream& in, Location& location);

	bool operator!() {
		return this->availableNoOfSeats == 0;
	}
		

};
void operator<<(ostream& out, Location location) {
	out << endl << "Location id: " << location.locationId;
	out << endl << "Number of rows are :  "<< location.noOfRows;
	out << endl << "Number of seats available are: " << location.availableNoOfSeats;
	out << endl << "The number of seats per row are: " << location.noOfSeatsPerRow;
	out << endl << "The total number of seats are: " << location.totalNoOfSeats;

	out << endl << "Location name: "<<(location.locationName != nullptr ? string(location.locationName) : "No name");
}

void operator>>(istream& in, Location& location) {
	cout << endl << "Location ID: ";
	in >> location.locationId;
	cout << endl << "Name: ";
	char buffer[100];
	in >> buffer;
	location.setLocationName(buffer);
	cout << endl << "Number of rows are: ";
	int noOfRows = 0;
	in >>noOfRows;
	location.setNoOfRows(noOfRows);
	cout << endl << "Number of seats per rows are: ";
	int noOfSeatsPerRow = 0;
	in >> noOfSeatsPerRow;
	location.setNoOfSeatsPerRow(noOfSeatsPerRow);
	location.calculateTotalNoOfSeats();
	location.calculateAvailableNoOfSeats();

}

bool operator==(Location& location1, Location& location2) {
	return location1.getLocationId() == location2.getLocationId();
}



