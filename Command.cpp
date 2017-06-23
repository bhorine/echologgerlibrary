/*
 * Command.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#include "Command.h"

namespace elcc {

Command::Command() {
	// TODO Auto-generated constructor stub

}

Command::~Command() {
	// TODO Auto-generated destructor stub
}

int Command::Check() {
	return 0;
}
// Add check sequence to packet. Packet must already be allocated.
void Command::AddCheck(char* packet, int packet_length, int buffer_length)
{
	// Calculate the check sequence and add it to the packet
	//
	for (int i=0; i<packet_length; i++) {
		//check += *(packet++);
	}
}
} /* namespace elcc */
