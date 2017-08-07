/* Command.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#include <cmath>
#include <iostream>

#include "Command.h"

namespace elcc {

Command::Command(uint32_t baud_rate) {
  m_baud_rate = baud_rate;

}

Command::~Command() {
	// TODO Auto-generated destructor stub
}

uint32_t Command::StartLength() {
  return 5*4;
}

int Command::Start(uint8_t *  packet, uint32_t buffer_length) {
  uint32_t * common_packet;
  common_packet = (uint32_t*)packet;
  common_packet[0] = (uint32_t)CMD_MAGIC;
  common_packet[1] = 6;
  common_packet[2] = 0; 
  common_packet[3] = 1;
  common_packet[4] = 1;
  common_packet[2] = AddCheck(common_packet, StartLength(), buffer_length);

  return 1;
}

uint32_t Command::StopLength() {
  return 5*4;
}

int Command::Stop(uint8_t *packet, uint32_t buffer_length) {
  uint32_t *common_packet;
  common_packet = (uint32_t*)packet;
  common_packet[0] = (uint32_t)CMD_MAGIC;
  common_packet[1] = 7;
  common_packet[2] = 0;
  common_packet[3] = 1;
  common_packet[4] = 1;
  common_packet[2] = AddCheck(common_packet, StopLength(), buffer_length);

  return 1;
}

uint32_t Command::ScanLength() {
  return 7*4;
}

int Command::SetScan(uint8_t *packet, uint32_t packet_len, uint32_t buffer_length, 
	double sectorScanHeading, 
	double sectorWidth,
	int rotationDirection,
	int steppingMode,
	int steppingTime,
	uint32_t num_samples) {
  uint32_t * common_packet;
  common_packet = (uint32_t*)packet;
  common_packet[0] = (uint32_t)CMD_MAGIC;
  common_packet[1] = 1;
  common_packet[2] = 0;
  uint16_t sector_scan_heading = (uint16_t)round(sectorScanHeading*28800.0/360.0);
  uint16_t sector_width = (uint16_t)round(sectorWidth*28800.0/360.0);
  common_packet[3] = sector_scan_heading << 16 | sector_width;
 #define DOUBLE_TOLERANCE 0.0001 
  uint16_t stepping_mode = 1;
  if(std::abs(steppingMode - 0.1125) < DOUBLE_TOLERANCE) 
  {
    stepping_mode = 1; // There is an inconsistency in the spec. Values 0,1,2,4,8,16 but steps of 0.1125, 0.225, 0.45, 0.9, and 1.8
  } else {
    if (std::abs(steppingMode - 0.225) < DOUBLE_TOLERANCE)
    {
      stepping_mode = 2;
    } else {
      if (std::abs(steppingMode - 0.45) < DOUBLE_TOLERANCE)
      {
        stepping_mode = 4;
      } else {
	if (std::abs(steppingMode - 0.9) < DOUBLE_TOLERANCE)
        {
          stepping_mode = 8;
        } else {
          if (std::abs(steppingMode - 1.8) < DOUBLE_TOLERANCE)
          {
            stepping_mode = 16;
          } else {
            stepping_mode = 4;
          }
        }
      }
    }
  }
  common_packet[4] = rotationDirection << 16 | stepping_mode;
  common_packet[5] = getPingInterval(m_baud_rate, stepping_mode, num_samples); // TODO: get baud_rate and samples
  common_packet[6] = 0;
  common_packet[2] = AddCheck(common_packet, ScanLength(), buffer_length);
  
  return 1;
}

uint32_t Command::getPingInterval(uint32_t baud_rate, uint16_t stepping_mode, uint16_t samples)
{
  uint8_t col_index, row_index;
  // Brute force it...
  // Get column index
  switch (stepping_mode)
  {
  case 0: col_index = 0; break;
  case 1: col_index = 1; break;
  case 2: col_index = 2; break;
  case 4: col_index = 3; break;
  case 8: col_index = 4; break;
  case 16: col_index = 5; break;
  default: col_index = 6; break;
  }
  // Get row index
  switch (samples) 
  {
  case 240: row_index = 0; break;
  case 368: row_index = 1; break;
  case 448: row_index = 2; break;
  case 704: row_index = 3; break;
  case 848: row_index = 4; break;
  case 1040: row_index = 5; break;
  case 1376: row_index = 6; break;
  case 2048: row_index = 7; break;
  case 2704: row_index = 8; break;
  case 4048: row_index = 9; break;
  case 6048: row_index = 10; break;
  case 8000: row_index = 11; break;
  default: row_index = 0; break;
  }

  return ping_interval[(baud_rate == 115200)?0:1][row_index][col_index];
}

uint32_t Command::CommonLength() {
  return 22*4;
}

int Command::SetCommon(uint8_t* packet, uint32_t packet_len, uint32_t buffer_length, 
	uint32_t commandid,
	uint32_t chirp_tone,
	uint32_t pulse_length,
	uint32_t gain,
	uint32_t num_samples) {
  if ( chirp_tone > 2) {
    std::cerr << "ERROR: Command::SetCommon " << "Chirp Tone must be 0 (tone), 1 (chirp FM), or 2 (chirp AFM)!" << std::endl;
    return -2;
  }
  uint32_t * common_packet;
  common_packet = (uint32_t*)packet;
  common_packet[0] = (uint32_t)CMD_MAGIC;
  common_packet[1] = 0;
  common_packet[2] = 0;
  common_packet[3] = 1; // start node (fixed at 1)
  common_packet[4] = 0; // (data format (fixed at 0)
  common_packet[5] = commandid;
  common_packet[6] = 0; // central frequency (fixed at 0)
  common_packet[7] = 0; // Frequency Band (fixed at 0)
  common_packet[8] = chirp_tone;
  common_packet[9] = pulse_length;
  common_packet[10] = getPingInterval(m_baud_rate, m_stepping_mode, num_samples);
  common_packet[11] = num_samples;
  common_packet[12] = 100000; // Sample frequency (fixed at 100 kSPS)
  common_packet[13] = gain;
  common_packet[14] = 0; // tvg_slope (fixed at 0)
  common_packet[15] = 1; // tvg_mode (fixed at 1)
  common_packet[16] = 80; // tvg_time (fixed at 80)
  common_packet[17] = 0; // sync (fixed at 0)
  common_packet[18] = 0; // sync_timeout (fixed at 0)
  common_packet[19] = 0; // tx_power (fixed at 0);
  common_packet[20] = 0; // rms_tx_power (fixed at 0);
  common_packet[2] = AddCheck(common_packet, CommonLength(), buffer_length);
  packet = (uint8_t*)common_packet;
  return 0;
}

void Command::resetDefaults() {
	resetDeviceDefaults();
	resetScanDefaults();
}

void Command::resetDeviceDefaults() {
  m_start_node = 1;
  m_data_format = 0;
  m_commandid = 0;
  m_central_frequency = 0;
  m_frequency_band = 0;
  m_chirp_tone = 1;
  m_pulse_length = 10;
  m_ping_interval = 1;
  m_samples = 240;
  m_sample_frequency = 100000;
  m_gain = 0;
  m_tvg_slope = 0;
  m_tvg_mode = 1;
  m_tvg_time = 80;
  m_sync = 0;
  m_sync_timeout = 0;
  m_tx_power = 0;
  m_rms_tx_power = 0;
}

void Command::resetScanDefaults() {
  m_sector_heading = 14400;
  m_sector_width = 14400;
  m_rotation_parameters = ROTATE_CW;
  m_stepping_mode = 1;
  m_stepping_time = 1;
  m_stepping_angle = 0;
}

void Command::setSectorWidth(float sector_width) {
	m_sector_width = fromAngle(sector_width);
}

uint16_t Command::fromAngle(float angle) {
	return (uint16_t)(round(28800*angle/360));
}

float Command::toAngle(uint16_t iangle) {
	return (360.0*(float)(iangle)/28800.0);
}
int Command::Check() {
	return 0;
}

// Add check sequence to packet. Packet must already be allocated.
uint32_t Command::AddCheck(uint32_t* packet, uint32_t packet_length, uint32_t buffer_length)
{
	uint32_t check = 0;
	// Calculate the check sequence and add it to the packet
	//
	for (int i=0; i<packet_length; i++) {
		check += *(packet++);
	}
}
} /* namespace elcc */
