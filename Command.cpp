/*
 * Command.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#include <math.h>

#include "Command.h"

namespace elcc {

Command::Command() {

}

Command::~Command() {
	// TODO Auto-generated destructor stub
}

int Command::Start() {
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 6;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  common_packet[3] = 1;
  common_packet[4] = 1;

  return 1;
}

int Command::StopLength() {
  return 5*8;
}

int Command::Stop(uint8_t *packet, buffer_length) {
  int32_t *common_packet;
  common_packet = (int32_t*)packet;
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 7;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  common_packet[3] = 1;
  common_packet[4] = 1;

  return 1;
}


int Command::SetScan(uint8_t *packet, buffer_length, 
	double sectorScanHeading, 
	double sectorWidth,
	int rotationDirection,
	int steppingMode,
	int steppingTime) {
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 1;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  uint16_t sector_scan_heading = (uint16_t)round(sectorScanHeading*28800.0/360.0);
  uint16_t sector_width = (uint16_t)round(sectorWidth*28800.0/360.0);
  common_packet[3] = sector_scan_heading << 16 | sector_width;
 #define DOUBLE_TOLERANCE 0.0001 
  uint16_t stepping_mode = 1;
  if(abs(steppingMode - 0.1125) < DOUBLE_TOLERANCE) 
  {
    stepping_mode = 1; // There is an inconsistency in the spec. Values 0,1,2,4,8,16 but steps of 0.1125, 0.225, 0.45, 0.9, and 1.8
  } else {
    if (abs(steppingMode - 0.225) < DOUBLE_TOLERANCE)
    {
      stepping_mode = 2;
    } else {
      if (abs(steppingMode - 0.45) < DOUBLE_TOLERANCE)
      {
        stepping_mode = 4;
      } else {
	if (abs(steppingMode - 0.9) < DOUBLE_TOLERANCE)
        {
          stepping_mode = 8;
        } else {
          if (abs(steppingMode - 1.8) < DOUBLE_TOLERANCE)
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
  common_packet[5] = GetPingInterval(baud_rate, stepping_mode, samples); // TODO: get baud_rate and samples
  common_packet[6] = 0;
  
  return 1;
}

uint32_t GetPingInterval(uint32_t baud_rate, uint16_t stepping_mode, uint16_t samples)
{
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
  switch (sample) 
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

int Command::SetCommon(char* packet) {
  common_packet[0] = CMD_MAGIC;
  common_packet[1] = 0;
  common_packet[2] = AddCheck(packet, packet_length, buffer_length);
  return 1;
}

void Command::ResetToDefaults() {
	ResetCommonSettings();
	ResetScanSettings();
}

void Command::ResetCommonSettings() {
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
  m_synch_timeout = 0;
  m_tx_power = 0;
  m_rms_tx_power = 0;
}

void Command::ResetScanSettings() {
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
	return (360.0*(float)(iangle)/28800.0;
}
int Command::Check() {
	return 0;
}

// Add check sequence to packet. Packet must already be allocated.
uint8_t Command::AddCheck(char* packet, int packet_length, int buffer_length)
{
	// Calculate the check sequence and add it to the packet
	//
	for (int i=0; i<packet_length; i++) {
		//check += *(packet++);
	}
}
} /* namespace elcc */
