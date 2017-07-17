/*
 * CommControl.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#include "CommControl.h"



namespace elcc {

CommControl::CommControl() {
	// TODO Auto-generated constructor stub

}

CommControl::~CommControl() {
	// TODO Auto-generated destructor stub
}

int CommControl::open_port(void)
{
	int fd; // file descriptor for serial port
	fd = open(TTYCONN, O_RDWR | O_NOCTTY | O_NDELAY);
	if(fd == -1) // if open is unsuccessful
	{
		perror("CommControl::connect: Unable to open port\n");
		return fd;
	}
	else
	{
		fcntl(fd, F_SETFL, 0);
		printf("port is open\n");
	}
	return fd;
}

int CommControl::configure_port(int fd, int connect_state)
{
	struct termios port_settings;

	if (connect_state == 0) {
  		cfsetispeed(&port_settings, STARTSPEEDSETTING);
  		cfsetospeed(&port_settings, STARTSPEEDSETTING);
	} else {
		cfsetispeed(&port_settings, CONNECTSPEEDSETTING);
		cfsetospeed(&port_settings, CONNECTSPEEDSETTING);
	}

	port_settings.c_cflag &= ~PARENB;
	port_settings.c_cflag &= ~CSTOPB;
	port_settings.c_cflag &= ~CSIZE;
	port_settings.c_cflag |= CS8;

	tcsetattr(fd, TCSANOW, &port_settings);
	return fd;
}

int CommControl::autobaud(int fd)
{
	//Somewhere we should wait 10 seconds for startup
	sleep(10000);
	unsigned char autobaud_character[] = { '@' };
	write(fd, autobaud_character, 1); // Send the autobaud character

	// Look for "#SYNC<LF>"
	char response[6];
	read(fd, response, 6);
	if (strcmp("#SYNC\n", response) != 0) {
		perror("CommControl::autobaud: Failed to sync");
		return -1;
	}
	char speed[] = CONNECTSPEED ;
	write(fd, speed, 9);
	read(fd, response, 4);
	if (strcmp("#OK\n", response) != 0) {
		perror("CommControl::autobaud: No first #OK seen.");
		return -2;
	}
	configure_port(fd, 1);
	sleep(100);
	read(fd, response, 4);
	if (strcmp("#OK\n", response) != 0) {
		perror("CommControl::autobaud: No second #OK seen.");
		return -3;
	}

	return fd;
}

int CommControl::connect() {
	int fd;
	fd = open_port();

	if (fd > 0)
	{
		fd = configure_port(fd, 0);
		fd = autobaud(fd);
	}

	return (fd);
}


} /* namespace elcc */