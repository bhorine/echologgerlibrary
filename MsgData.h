#pragma once

namespace elcc {
class MsgData {
// static constants
	public:
		static const unsigned int DATA_OFFSET = 7;
		static const unsigned int SAMPLESNUM = 15;
		static const unsigned int ANGLE = 23;
		static const unsigned int COMMANDID = 27;
		static const unsigned int HEADER_LENGTH = 7;

// member variables
public:

  uint8_t* m_rx_pkt_ptr;
  uint16_t* data_received;
  uint32_t m_data_offset;
  uint32_t m_samplesnum;
  uint32_t commandid;
  uint16_t* length;
  uint16_t* rx_pkt;



// public methods
public:
  MsgData(uint8_t* received_packet_ptr);
  void ParseHeader();
  uint32_t GetDataLength();
  void GetData(uint16_t* data_received, uint32_t received_buf_size);
  double GetAngle();
  uint16_t Uncompand8to12(uint8_t b);
};
}
