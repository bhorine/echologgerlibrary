/*
 * CommControl.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

//#include "Command.h"
#include <cstdint>

#include "CommControl.h"


namespace elcc {

CommControl::CommControl() {
	// TODO Auto-generated constructor stub

}

CommControl::~CommControl() {
	// TODO Auto-generated destructor stub
}

int CommControl::open_port(char* port)
{
	int fd; // file descriptor for serial port
        
	fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
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
        std::cout << "Wait 10 seconds before starting autobaud..." << std::flush;
	sleep(START_DELAY);
        std::cout << "done." << std::endl;
	unsigned char autobaud_character[] = { '@' };
	std::cout << "Sending autobaud character..." << std::flush;
	write(fd, autobaud_character, 1); // Send the autobaud character

	// Look for "#SYNC<LF>"
	char response[6];
	for (int i=0; i<6; i++) {
	  read(fd, response + i, 1);
          std::cout << std::hex << response[i] << std::flush;
        }
        std::cout << std::endl;
	if (strcmp("#SYNC\n", response) != 0) {
		perror("CommControl::autobaud: Failed to sync");
		std::cout << "Response is: " << response << std::endl;
		return -1;
	}
	std::cout << "Got response (expecting #SYNC<LF>): " << response << std::endl;
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

int CommControl::connect(char* port) {
	int fd;
	std::cout << "Ready to open port" << std::endl;
	fd = open_port(port);

	if (fd > 0)
	{
		std::cout << "Ready to configure port" << std::endl;
		fd = configure_port(fd, 0);
		std::cout << "Ready to autobaud" << std::endl;
		fd = autobaud(fd);
	}

	return (fd);
}

/*int CommControl::setScanParameters() {
  int retval = 0;
  Command cmd;
  if ( cmd.SetScan(packet, buf_len, sectorScanHeading,
	sectorWidth,
	rotationDirection,
	steppingMode,
	steppingTime) == 0 ) {
    int bytes_written = write(fd, packet, buf_len);
    if (bytes_written != buf_len) {
      retval = -2;
    } else {
      retval = 0;
    }
  } else {
    retval = -1;
  }    
  return retval;
}

int CommControl::setCommonParameters(double sectorScanHeading,
		double sectorWidth,
		int rotationDirection,
		int steppingMode,
		int steppingTime) {
  int retval = 0;
  Command cmd;
  uint8_t packet[88];
  int buf_len = 88;
  if ( cmd.SetCommon(packet, buf_len, commandid++,
	chirp_tone,
	pulse_length,
	ping_interval,
	num_samples,
	gain ) == 0 ) {
    int bytes_written = write(fd, packet, buf_len);
    if (bytes_written != buf_len) {
      retval = -2;
    } else {
      retval = 0;
    }
  } else {
    retval = -1;
  }    
  return retval;
}

int CommControl::readData() {
  Command cmd;
  cmd.Start(packet, buf_len);
  int bytes_written = write(fd, packet, buf_len);
  
  return 0;
}*/
} /* namespace elcc */
