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

#define TTYCONN "/dev/ttyS0"
#define STARTSPEED "<230400\r>"
#define STARTSPEEDSETTING B230400
#define CONNECTSPEED "<2000000\n>"
#define CONNECTSPEEDSETTING B2000000


namespace elcc {

class CommControl {
public:

	CommControl();
	virtual ~CommControl();
	int connect();
	//void write();
	//void read();
private:
	int open_port(void);
	int configure_port(int fd, int connect_mode);
	int autobaud(int fd);

};

} /* namespace elcc */
#endif /* COMMCONTROL_H_ */
