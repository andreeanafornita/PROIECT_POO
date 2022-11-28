#pragma once
#include "Location.h"
class Ticket
{
private:
	bool VIP = 0;
	int lawn;
	int tribune;
	Location location;//locatia din clasa Location
	static int sequence;
	const int id;
	Ticket(bool VIP, int lawn, int tribune, int boxes): id(sequence) {
		this->VIP = VIP;
		this->lawn = lawn;
		this->tribune = tribune;
		++Ticket::sequence;//crestem sequence cu 1
	}



};



