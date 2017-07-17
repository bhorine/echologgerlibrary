/* 
 *  MsgData.cpp 
 *    Parses the data coming from the EchoLogger sonar
 *
 */

#include <cstring> // for memcpy
#include <cstdint>
#include <iostream>

#include "MsgData.h"

namespace elcc {
using namespace std;

/* Constructor */
MsgData::MsgData(uint8_t* received_packet_ptr) 
{
	   m_rx_pkt_ptr = received_packet_ptr;
}

void MsgData::ParseHeader()
{
//	m_data_offset = *(uint32_t *)(m_rx_pkt_ptr + DATAOFFSET); // points to the location of the beginning of the data payload
	m_data_offset = m_rx_pkt_ptr[DATA_OFFSET];
	m_data_offset |= m_rx_pkt_ptr[DATA_OFFSET - 1] << 1*8;
	m_data_offset |= m_rx_pkt_ptr[DATA_OFFSET - 2] << 2*8;
	m_data_offset |= m_rx_pkt_ptr[DATA_OFFSET - 3] << 3*8;
	m_samplesnum = *(m_rx_pkt_ptr + SAMPLESNUM);  // Number of samples in the data payload
	m_samplesnum |= *(m_rx_pkt_ptr + SAMPLESNUM - 1) << 1*8;
	m_samplesnum |= *(m_rx_pkt_ptr + SAMPLESNUM - 2) << 2*8;
	m_samplesnum |= *(m_rx_pkt_ptr + SAMPLESNUM - 3) << 3*8;


}

uint32_t MsgData::GetDataLength()
{
  return m_samplesnum;
}

void MsgData::GetData(uint16_t* data_received, uint32_t received_buf_size)
{
	uint32_t max_sample = m_samplesnum;
	if (received_buf_size < m_samplesnum) {
		cerr << "Received buffer size is too small. Some data is missing." << endl;
		max_sample = received_buf_size;
	}
	//angle = GetAngle(); // This is the angle at which the data is collected
	cout << "Getting data from " << m_data_offset << " to " << max_sample + m_data_offset << endl;
	cout << std::dec;
	for (uint16_t i=m_data_offset; i<max_sample + m_data_offset; i++)
	{
	  cout << i << " " << +m_rx_pkt_ptr[i];
		data_received[i] = Uncompand8to12(m_rx_pkt_ptr[i]);
	  cout << " ...  " << +data_received[i] << endl;
	}
}

/* Extracts the angle at which the data was gathered */
double MsgData::GetAngle() {

//  uint32_t raw_angle = (uint32_t)(*(m_rx_pkt_ptr + ANGLE)); // Extract the angle from the header
  uint32_t raw_angle = 0;
  uint8_t angle_byte = 0;
  angle_byte = *(m_rx_pkt_ptr + ANGLE);
  cout << "Raw angle LSB " << (int)angle_byte << endl;
  raw_angle = angle_byte;
  angle_byte = *(m_rx_pkt_ptr + ANGLE - 1);
  cout << "Raw angle byte 1 " << (int)angle_byte << endl;
  raw_angle += angle_byte << 8;
  angle_byte = *(m_rx_pkt_ptr + ANGLE - 2);
  cout << "Raw angle byte 2 " << (int)angle_byte << endl;
  raw_angle += angle_byte << 16;
  angle_byte = *(m_rx_pkt_ptr + ANGLE - 3);
  cout << "Raw angle byte MSB " << (int)angle_byte << endl;
  raw_angle += angle_byte << 24;
  
cout << "Raw angle is " << raw_angle << endl;
  double angle = ((double)raw_angle)*360.0/28800.0; // Convert from raw to world units
  return angle;
}

/* Uncompand the data. Companding is used by the EchoLogger sonar to compress the data
 * based upon ignoring some dynamic range at large signal levels. This allows the data
 * to be transmitted in bytes instead of half-words. 
 */
uint16_t MsgData::Uncompand8to12(unsigned char b) 
{ 
  uint16_t ret = (uint16_t) b ; 
  
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
