/*
 * Command.h
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#define CMD_MAGIC 1145982275
namespace elcc {

class Command {
public:
	Command();
	virtual ~Command();
	int Check();
	int32_t AddCheck(char* packet, int packet_length, int buffer_length);

	int start(uint8_t* packet, uint32_t buffer_length);
	int Stop(uint8_t* packet, uint32_t buffer_length);
	int SetScan(uint8_t* packet, uint32_t buffer_length, 
		sector_heading,
		sector_width,
		rotation,
		stepping_mode,
		stepping_time,
		stepping_angle);
        int SetCommon(uint8_t* packet, uint32_t bufferLength);
	
};

} /* namespace elcc */
#endif /* COMMAND_H_ */
