#pragma once
#include<iostream>
using namespace std;
//this is a class named Location, it has a name, number of rows, number of seats per row, total number of seats that cand be easily found by multiplicatind the number of rows with number of seats per row, it also has an id who is attributed privately so no one can access the id, and available number of seats so we can decide if we can sell tickets more

class Location {
private:
	char* locationName;
	int noOfRows;
	int noOfSeatsPerRow;
	int totalNoOfSeats = 0;
	int locationId;
	int availableNoOfSeats;

public:
	Location(int locationId, char* locationName, int noOfRows, int noOfSeatsPerRow) {// this is a constrcutor that can be made either this way, or by writing as we do at courses (exp:this->location=location) but i think is much more easier like that because in the setter I did a lot of things to include conditions of existence and also the getters 
		this->setLocationId(locationId);
		this->setLocationName(locationName);
		this->setNoOfRows(noOfRows);
		this->setNoOfSeatsPerRow(noOfSeatsPerRow);
		this->calculateTotalNoOfSeats();
		this->calculateAvailableNoOfSeats();
	}
	Location() {
		this->locationId = 0;//this is the default constructor
	}

	~Location() {//this is a destrcutor for our dyanmically alocated vector
		delete[] this->locationName;
	}

	int getNoOfRows() {//this is the getter for number of rows, those getters must be done in order to work with the variables later, in fact they return the variable, that's why we use the word "return"
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

	static void printLocation(Location location) {//this is a static method that has the target to print the location from class Location
		cout << location;
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
	void setLocationName(char* locationName) {//this is also a setter that is computed by a vector of char allocated dynamic, this setter has the target to verifiy if it exists a location name in the array of characters, if exists, we also delete the old char and after that we create a new memory space and we copy by strcpy the old locationName in the new locationName
		if (locationName == nullptr || strlen(locationName) == 0) {
			exit(1);
		}
		if (this->locationName != nullptr) {
			delete[] this->locationName;
		}
		this->locationName = new char[strlen(locationName) + 1];
		strcpy(this->locationName, locationName);

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
	void calculateTotalNoOfSeats() {//this is a method that helps us to calculate the total number of seats by simply multiplying number of seats per row with number of rows
		if (this->noOfSeatsPerRow > 0 && this->noOfRows > 0) {
			this->totalNoOfSeats = noOfSeatsPerRow * noOfRows;
		}

	}
	void setTotalNoOfSeats(int totalNoOfSeats) {//this is a setter for total number of seats. we also put here a condition for numbers because it can't be less or equal to 0, because it means it doesn't exists, so if it doesn't exists, we put a warning message to inform the user
		if (totalNoOfSeats > 0) {
			this->totalNoOfSeats = totalNoOfSeats;
		}
		else {
			cout << "Total number of seats might be greater than 0";
			exit(1);
		}
	}
	void setAvailableNoOfSeats(int availableNoOfSeats) {// this is also a setter that check if the available number of seats is greater than 0, becuase as I said before, if it is less than 0 it means it doesn't exists so the code will exit and will appear a warning message
		if (availableNoOfSeats > 0) {
			this->availableNoOfSeats = availableNoOfSeats;
		}
		else {
			cout << "Available number of seats might be greater than 0";
		}
	}
	void setLocationId(int locationId) {//this is a normal setter without any condition because the ID can be every integer 
		this->locationId = locationId;
	}
	void calculateAvailableNoOfSeats() {//this is a method that can help us to find out the seats that are no more occupied
		this->availableNoOfSeats = this->totalNoOfSeats;
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

	void operator=(const Location& aux) {//this is an operator type "="
		if (this == &aux) {
			return;
		}
		this->availableNoOfSeats = aux.availableNoOfSeats;
		this->locationId = aux.locationId;
		this->noOfRows = aux.noOfRows;
		this->noOfSeatsPerRow = aux.noOfSeatsPerRow;
		this->totalNoOfSeats = aux.totalNoOfSeats;
		if (this->locationName) {
			delete[] this->locationName;
			this->locationName = nullptr;
		}
		if (aux.locationName) {
			this->locationName = new char[strlen(aux.locationName) + 1];
			strcpy(this->locationName, aux.locationName);
		}
	}

	Location(const Location& aux1) {//this is a copy constructor
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

	bool operator!() {//this is the "!" operator
		return this->availableNoOfSeats == 0;
	}


};
void operator<<(ostream& out, Location location) {//this is the operator "<<"
	out << endl << "Location id: " << location.locationId;
	out << endl << "Number of rows are :  " << location.noOfRows;
	out << endl << "Number of seats available are: " << location.availableNoOfSeats;
	out << endl << "The number of seats per row are: " << location.noOfSeatsPerRow;
	out << endl << "The total number of seats are: " << location.totalNoOfSeats;

	out << endl << "Location name: " << (location.locationName != nullptr ? string(location.locationName) : "No name");
}

void operator>>(istream& in, Location& location) {//this is the operator">>"
	cout << endl << "Location ID: ";
	in >> location.locationId;
	cout << endl << "Name: ";
	char buffer[100];
	in >> buffer;
	location.setLocationName(buffer);
	cout << endl << "Number of rows are: ";
	int noOfRows = 0;
	in >> noOfRows;
	location.setNoOfRows(noOfRows);
	cout << endl << "Number of seats per rows are: ";
	int noOfSeatsPerRow = 0;
	in >> noOfSeatsPerRow;
	location.setNoOfSeatsPerRow(noOfSeatsPerRow);
	location.calculateTotalNoOfSeats();
	location.calculateAvailableNoOfSeats();

}

bool operator==(Location& location1, Location& location2) {//this is the operator "=="
	return location1.getLocationId() == location2.getLocationId();
}



