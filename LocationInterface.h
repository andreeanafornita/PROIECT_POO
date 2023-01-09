#pragma once
#include <iostream>
#include <string>

using namespace std;

bool tryParse(std::string& input, int& output) {
	try {
		output = std::stoi(input);
	}
	catch (std::invalid_argument) {
		return false;
	}
	return true;
}

class LocationInterface {
public:
	LocationInterface(string locationName, int totalNoOfSeats) {// this is a constrcutor that can be made either this way, or by writing as we do at courses (exp:this->location=location) but i think is much more easier like that because in the setter I did a lot of things to include conditions of existence and also the getters 
		this->setLocationName(locationName);
		this->setTotalNoOfSeats(totalNoOfSeats);
	}
	LocationInterface() {}

	virtual string getLocationName() const {
		return this->locationName;
	}
	virtual int getTotalNoOfSeats() const{
		return this->totalNoOfSeats;
	}
	virtual void setLocationName(string locationName) {//this is also a setter that is computed by a vector of char allocated dynamic, this setter has the target to verifiy if it exists a location name in the array of characters, if exists, we also delete the old char and after that we create a new memory space and we copy by strcpy the old locationName in the new locationName
		if (locationName.empty() || locationName.length() == 0 || locationName == "\n") {
			exit(1);
		}
		this->locationName = locationName;
	}
	virtual void setTotalNoOfSeats(int totalNoOfSeats) {//this is a setter for total number of seats. we also put here a condition for numbers because it can't be less or equal to 0, because it means it doesn't exists, so if it doesn't exists, we put a warning message to inform the user
		if (totalNoOfSeats > 0) {
			this->totalNoOfSeats = totalNoOfSeats;
		}
		else {
			cout << "Total number of seats might be greater than 0";
			exit(1);
		}
	}

private:
	virtual int generateID() = 0;

private:
	string locationName;
	int totalNoOfSeats;
};
