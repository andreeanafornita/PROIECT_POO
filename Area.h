#pragma once
#include "LocationInterface.h"
#include <string>
using namespace std;
class Area : virtual public LocationInterface {
private:
	string m_type;
	string m_entrance;
public:
	Area(string areaName, int noOfRows, int noOfSeatsPerRow, string type, string entrance): LocationInterface(areaName,noOfRows,noOfSeatsPerRow) {
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