#pragma once
#include <iostream>
#include <string>

using namespace std;

class LocationInterface {
public:
	LocationInterface(string locationName, int noOfRows, int noOfSeatsPerRow) {// this is a constrcutor that can be made either this way, or by writing as we do at courses (exp:this->location=location) but i think is much more easier like that because in the setter I did a lot of things to include conditions of existence and also the getters 
		this->setLocationName(locationName);
		this->setNoOfRows(noOfRows);
		this->setNoOfSeatsPerRow(noOfSeatsPerRow);
		this->calculateTotalNoOfSeats();
		this->availableNoOfSeats = totalNoOfSeats;
	}
	LocationInterface() {}

	int getNoOfRows() const {//this is the getter for number of rows, those getters must be done in order to work with the variables later, in fact they return the variable, that's why we use the word "return"
		return this->noOfRows;
	}
	string getLocationName() const {
		return this->locationName;
	}
	int getNoOfSeatsPerRow() const{
		return this->noOfSeatsPerRow;
	}
	int getTotalNoOfSeats() const{
		return this->totalNoOfSeats;
	}
	int getAvailableNoOfSeats() const {
		return this->availableNoOfSeats;
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
	void setLocationName(string locationName) {//this is also a setter that is computed by a vector of char allocated dynamic, this setter has the target to verifiy if it exists a location name in the array of characters, if exists, we also delete the old char and after that we create a new memory space and we copy by strcpy the old locationName in the new locationName
		if (locationName.empty() || locationName.length() == 0) {
			exit(1);
		}
		this->locationName = locationName;
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

private:
	virtual int generateID() = 0;

private:
	string locationName;
	int noOfRows;
	int noOfSeatsPerRow;
	int totalNoOfSeats;
	int availableNoOfSeats;
};
