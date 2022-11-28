#pragma once
class Ticket
{
private:
	bool VIP = 0;
	int lawn;
	int tribune;
	int boxes;
	static int sequence;
	const int id;
	Ticket(bool VIP, int lawn, int tribune, int boxes): id(sequence) {
		this->VIP = VIP;
		this->lawn = lawn;
		this->tribune = tribune;
		this->boxes = boxes;
		++Ticket::sequence;
	}



};



