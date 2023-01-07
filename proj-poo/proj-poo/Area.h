#pragma once
#include "Location.h"
#include <string>
using namespace std;
class Area : virtual public Location {
private:
	string m_type;
	string m_entrance;
public:
	Area(int locationId, string locationName, int noOfRows, int noOfSeatsPerRow, string type, string entrance): Location(locationId,locationName,noOfRows,noOfSeatsPerRow) {
		this->locationId = locationId;
		this->locationName = locationName;;
		this->noOfRows = noOfRows;
		this->noOfSeatsPerRow = noOfSeatsPerRow;
		this->m_type = type;
		this->m_entrance = entrance;
	}
	string getZoneType()const
	{
		return m_type;
	}
	string getZoneEntrance() const
	{
		return m_entrance;
	}
	void setZoneType(string type)
	{
		m_type = type;
	}
	void setZoneEntrance(string entrance)
	{
		m_entrance = entrance;
	}
};