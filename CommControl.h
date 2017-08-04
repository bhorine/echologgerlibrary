/*
 * CommControl.h
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#ifndef COMMCONTROL_H_
#define COMMCONTROL_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <iostream>

#define STARTSPEED "<230400\r>"
#define STARTSPEEDSETTING B115200
#define CONNECTSPEED "<2000000\n>"
#define CONNECTSPEEDSETTING B2000000


namespace elcc {
  const unsigned int START_DELAY = 10; // Delay 10 seconds after applying power to the sonar before trying to communicate with it.

class CommControl {
public:

	CommControl();
	virtual ~CommControl();
	int connect(char* port);
	//void write();
	//void read();
	int setScanParameters();
	int setCommonParamters();
	int readData();
   

//private:
//	char* m_port;
	int open_port(char* port);
	int configure_port(int fd, int connect_mode);
	int autobaud(int fd);

};

} /* namespace elcc */
#endif /* COMMCONTROL_H_ */
