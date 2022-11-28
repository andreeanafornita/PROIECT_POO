#pragma once
#include "Location.h"
#include"Event.h"
class Ticket
{
private:
	Event event;
	float price;
	bool isUsed = false;
	Location location;//locatia din clasa Location
	static int sequence;
	const int id;
	Ticket(bool VIP, int lawn, int tribune, int boxes): id(sequence) {
		
		++Ticket::sequence;//crestem sequence cu 1
	}

public:
	static void useTicket(Ticket ticket) {
		ticket.isUsed = true;
	}

	static bool checkTicket(Ticket ticket) {
		return ticket.isUsed;
	}
};



