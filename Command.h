/*
 * Command.h
 *
 *  Created on: Apr 4, 2017
 *      Author: bhorine
 */

#ifndef COMMAND_H_
#define COMMAND_H_

#include <cstdint>

#define CMD_MAGIC 1145982275
#define MAX_PACKET_LEN 100
#define ROTATE_CW 0
#define ROTATE_CCW 1
namespace elcc {

class Command {
public:
	Command(uint32_t baud_rate);
	virtual ~Command();
	int Check();
	uint32_t AddCheck(uint32_t* packet, uint32_t packet_length, uint32_t buffer_length);

	uint32_t StartLength();
	uint32_t StopLength();
	uint32_t ScanLength();
	uint32_t CommonLength();
	int Start(uint8_t* packet, uint32_t buffer_length);
	int Stop(uint8_t* packet, uint32_t buffer_length);
	int SetScan(uint8_t* packet, uint32_t packet_len, uint32_t buffer_length, 
		double sector_heading,
		double sector_width,
		int rotationDirection,
		int stepping_mode,
		int stepping_time,
		uint32_t num_samples);
		//stepping_angle);
        int SetCommon(uint8_t* packet, uint32_t packet_len, uint32_t bufferLength,
		uint32_t commandid,
		uint32_t chirp_tone,
		uint32_t pulse_length,
		uint32_t gain,
		uint32_t num_samples);
	void resetDefaults();
	void resetDeviceDefaults();
	void resetScanDefaults();
	void applySettings();
	void setSectorWidth(float sector_width);
	uint16_t fromAngle(float angle);
	float toAngle(uint16_t iangle);
	uint32_t getPingInterval(uint32_t baud_rate, uint16_t stepping_mode, uint16_t samples);
	int setCommon(char* packet);
private:
//        uint32_t common_packet[MAX_PACKET_LEN];
	const uint32_t ping_interval[2][12][6] = 
		    { { { 23,  23,  23,  23,  23,  23},
			{ 36,  36,  36,  36,  36,  36},
			{ 43,  43,  43,  43,  43,  43},
			{ 68,  68,  68,  68,  68,  68},
			{ 81,  81,  81,  81,  81,  81},
			{100, 100, 100, 100, 100, 100},
			{132, 132, 132, 132, 132, 132},
			{196, 196, 196, 196, 196, 196},
			{259, 259, 259, 259, 259, 259},
			{387, 387, 387, 387, 387, 387},
			{578, 578, 578, 578, 578, 578},
			{764, 764, 764, 764, 764, 764} }, 
		      { {  4,   6,   7,   9,  14,  24},
			{  6,   7,   8,  11,  15,  25},
			{  7,   8,   9,  11,  16,  26}, 
			{  9,  10,  11,  14,  19,  28},
			{ 11,  12,  13,  15,  20,  30},
			{ 13,  14,  15,  17,  22,  32},
			{ 17,  17,  18,  21,  25,  35},
			{ 25,  25,  25,  27,  32,  42},
			{ 33,  33,  33,  34,  39,  48},
			{ 49,  49,  49,  49,  52,  62},
			{ 73,  73,  73,  73,  73,  82},
			{ 96,  96,  96,  96,  96, 101} } };
	uint32_t m_baud_rate;
	uint32_t m_sector_heading;
	uint32_t m_sector_width;
	uint32_t m_rotation_parameters;
	uint32_t m_stepping_mode;
	uint32_t m_stepping_angle;
	uint32_t m_stepping_time;
	uint32_t m_start_node;
	uint32_t m_data_format;
	uint32_t m_commandid;
	uint32_t m_central_frequency;
	uint32_t m_frequency_band;
	uint32_t m_chirp_tone;
	uint32_t m_pulse_length;
	uint32_t m_ping_interval;
	uint32_t m_samples;
	uint32_t m_sample_frequency;
	uint32_t m_gain;
	uint32_t m_tvg_slope;
	uint32_t m_tvg_mode;
	uint32_t m_tvg_time;
	uint32_t m_sync;
	uint32_t m_sync_timeout;
	uint32_t m_tx_power;
	uint32_t m_rms_tx_power;
};

} /* namespace elcc */
#endif /* COMMAND_H_ */
