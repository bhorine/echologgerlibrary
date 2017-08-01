#include <iostream>
#include <cstdint>

#include "CommControl.h"

using namespace elcc;

int main(int argc, char* argv[])
{
  CommControl comm_cntrl;

  int fd = comm_cntrl.open_port();

  int connect_state = 0;
  comm_cntrl.configure_port(fd, connect_state);
  connect_state = 1;


  comm_cntrl.autobaud(fd);



  return 0;
}
