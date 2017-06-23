#pragma once
#include "eldatatypes.h"

namespace elcc {
class MsgData {
// static constants
	public:
		static const unsigned int DATAOFFSET = 4;
		static const unsigned int SAMPLESNUM = 12;
		static const unsigned int ANGLE = 20;
		static const unsigned int COMMANDID = 24;
		static const unsigned int HEADER_LENGTH = 7;

// member variables
public:

  byte* m_rx_pkt_ptr;
  uint32* data_received;
  uint32* header;
  uint32 data_offset;
  uint32 samplesnum;
  uint32 angle;
  uint32 commandid;
  uint16* length;
  uint8* received_packet_ptr;
  uint32* rx_pkt;



// public methods
public:
  MsgData(uint8* received_packet_ptr);
  void ParseHeader(uint32* rx_pkt, uint16* length);
  void GetData(uint32* data_received, uint32* rx_pkt);
  double getAngle();
  unsigned short uncompand8to12(unsigned char b);
};
}
