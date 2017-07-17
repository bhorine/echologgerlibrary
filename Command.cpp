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

int Command::Start() {
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 6;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  common_packet[3] = 1;
  common_packet[4] = 1;

  return 1;
}

int Command::StopLength() {
  return 5*8;
}

int Command::Stop(uint8_t *packet, buffer_length) {
  int32_t *common_packet;
  common_packet = (int32_t*)packet;
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 7;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  common_packet[3] = 1;
  common_packet[4] = 1;

  return 1;
}

int Command::SetScan() {
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 1;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  
  return 1;
}

int Command::SetCommon(char* packet) {
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 0;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  return 1;
}

int Command::Check() {
	return 0;
}
// Add check sequence to packet. Packet must already be allocated.
uint8_t Command::AddCheck(char* packet, int packet_length, int buffer_length)
{
	// Calculate the check sequence and add it to the packet
	//
	for (int i=0; i<packet_length; i++) {
		//check += *(packet++);
	}
}
} /* namespace elcc */
