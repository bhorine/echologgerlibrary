/*
 * Command.h
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#ifndef COMMAND_H_
#define COMMAND_H_

namespace elcc {

class Command {
public:
	Command();
	virtual ~Command();
	int Check();
	void AddCheck(char* packet, int packet_length, int buffer_length);
};

} /* namespace elcc */
#endif /* COMMAND_H_ */
