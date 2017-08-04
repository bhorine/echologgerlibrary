#include <iostream>
#include <cstdint>

#include "CommControl.h"

using namespace elcc;

int main(int argc, char* argv[])
{
  CommControl comm_cntrl;

  if (argc < 2) {
    std::cout << "Usage: test_autobaud <device> where <device> is something like /dev/ttyUSB0" << std::endl;
    return (-1);
  }

  comm_cntrl.connect(argv[1]);

/*  int fd = comm_cntrl.open_port(argv[1]);

  int connect_state = 0;
  comm_cntrl.configure_port(fd, connect_state);
  connect_state = 1;


  comm_cntrl.autobaud(fd);
*/


  return 0;
}
