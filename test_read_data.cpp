#include <iostream>	// std::cout
#include <fstream>	// std::ifstream
#include <cstdint>
#include <string.h>

#include "MsgData.h"

#define MAX_PATH_LEN 255
using namespace std;
using namespace elcc;

int main(int argc, char* argv[])
{
  char fname[MAX_PATH_LEN];
  if (argc < 2)
  {
    cerr << "Usage: test_read_data file_name" << endl;
    return(-1);
  }
  strncpy(fname, argv[1], MAX_PATH_LEN);
//  int fd = open(fname, O_RDONLY);
  ifstream fd(fname, ifstream::binary);
  if (fd == NULL)
  {
    cerr << "Unable to open data file " << fname << endl;
    return(-1);
  }
  uint32_t i = 0;
  // determine length of file
  fd.seekg(0, fd.end);
  int length = fd.tellg();
  fd.seekg(0, fd.beg);

  char * rx_frame = new char[length];
  cout << "Reading " << length << " characters... ";
  fd.read(rx_frame, length);
  if (fd.gcount() == length)
  {
    cout << fname << " read in full." << endl;
  } else
  {
    cout << "Error: only " << fd.gcount() << " could be read!" << endl;
  }
  fd.close();
  for (uint32_t k=0; k<28; k++)
  {
    cout << std::dec << k << " " << std::hex << (uint32_t)rx_frame[k] << endl;
  }
  cout << std::dec;
  MsgData msg_data((uint8_t*)rx_frame);
  msg_data.ParseHeader();
  uint32_t rx_data_size = msg_data.GetDataLength();
  uint16_t * rx_data = new uint16_t[rx_data_size];
  cout << "Angle is " << msg_data.GetAngle() << " degrees" << endl;
  msg_data.GetData(rx_data, rx_data_size);  
  cout << "Got data" << endl;
  for (uint32_t i=0; i<rx_data_size; i++)
  {
    cout << rx_data[i] << endl;
  }

  delete[] rx_data;
  return(0);
}
