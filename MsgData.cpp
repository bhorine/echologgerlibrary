

#include "MsgData.h"
#include <cstring> // for memcpy

namespace elcc {
MsgData::MsgData(uint8* received_packet_ptr) //should this be void? because the next two are void
{
	   m_rx_pkt_ptr = received_packet_ptr;
}

void MsgData::ParseHeader(uint32* rx_pkt, uint16* length)
{
	memcpy(header, rx_pkt, HEADER_LENGTH);
	data_offset = *((uint32*)m_rx_pkt_ptr + DATAOFFSET);
	samplesnum = *((uint32*)m_rx_pkt_ptr + SAMPLESNUM);

}

void MsgData::GetData(uint32* data_received, uint32* rx_pkt)
{
	angle = getAngle();
	for (unsigned int i=data_offset; i<samplesnum + data_offset; i++)
	{
		data_received[i] = uncompand8to12(rx_pkt[i]);
	}
}

double MsgData::getAngle() {
  uint32 raw_angle = (uint32)(*(header + ANGLE));
  double angle = ((double)raw_angle)*360.0/28800.0;
  return angle;
}

unsigned short MsgData::uncompand8to12(unsigned char b) 
{ 
  unsigned short ret = (unsigned short) b ; 
  
  ret = ( (b >> 5) == 7 ) ? ( (ret & 0x1F) << 6 ) | (1 << 11) | (1 << 5) : 
	  ( (b >> 5) == 6 ) ? ( (ret & 0x1F) << 5 ) | (1 << 10) | (1 << 4) : 
	  ( (b >> 5) == 5 ) ? ( (ret & 0x1F) << 4 ) | (1 << 9) | (1 << 3) :
	  ( (b >> 5) == 4 ) ? ( (ret & 0x1F) << 3 ) | (1 << 8) | (1 << 2) : 
	  ( (b >> 5) == 3 ) ? ( (ret & 0x1F) << 2 ) | (1 << 7) | (1 << 1) : 
	  ( (b >> 5) == 2 ) ? ( (ret & 0x1F) << 1 ) | (1 << 6) | (1 << 0) : 
	  ( (b >> 5) == 1 ) ? ( (ret & 0x1F) << 0 ) | (1 << 5) : 
	  ( (ret & 0x1F) << 0 ) ; 
  
  return ret ; 
}
}
