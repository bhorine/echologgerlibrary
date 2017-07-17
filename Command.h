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
private:
	const uint32_t ping_interval[2][12][6] = 
		    { { { 23,  23,  23,  23,  23,  23},
			{ 36,  36,  36,  36,  36,  36},
			{ 43,  43,  43,  43,  43,  43},
			{ 68,  68,  68,  68,  68,  68},
			{ 81,  81,  81,  81,  81,  81},
			{100, 100, 100, 100, 100, 100},
			{132, 132, 132, 132, 132, 132},
			{196, 196, 196, 196, 196, 196},
			{259, 259, 259, 259, 259, 259},
			{387, 387, 387, 387, 387, 387},
			{578, 578, 578, 578, 578, 578},
			{764, 764, 764, 764, 764, 764} }, 
		      { {  4,   6,   7,   9,  14,  24},
			{  6,   7,   8,  11,  15,  25},
			{  7,   8,   9,  11,  16,  26}, 
			{  9,  10,  11,  14,  19,  28},
			{ 11,  12,  13,  15,  20,  30},
			{ 13,  14,  15,  17,  22,  32},
			{ 17,  17,  18,  21,  25,  35},
			{ 25,  25,  25,  27,  32,  42},
			{ 33,  33,  33,  34,  39,  48},
			{ 49,  49,  49,  49,  52,  62},
			{ 73,  73,  73,  73,  73,  82},
			{ 96,  96,  96,  96,  96, 101} } };
};

} /* namespace elcc */
#endif /* COMMAND_H_ */
