
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#define MAX_PATH_LEN 255

int main(int argc, char* argv[]) 
{
	char fname[MAX_PATH_LEN];
	if (argc < 2)
	{
	  printf("Usage: createtestdata file_name");
	  exit(-1);
	}
	strncpy(fname, argv[1], MAX_PATH_LEN);
	int fd = open(fname, O_WRONLY);
	if (fd < 0) 
	{
	  printf("Error: Unable to open %s\n", fname);
	  exit(-1);
	}
	uint8_t out_byte;
	uint32_t magic = 1096040772;
	uint32_t data_offset = 28;
	uint32_t data_size = 1;
	uint32_t samples_num = 1024;
	uint32_t device_id = 1;
	uint32_t angle = 14400;
	uint32_t command_id = 6;

	/* Output magic */
	out_byte = 0xff & (magic >> 3*8);
	write(fd, &out_byte, 1);
	printf("0x%02X", out_byte);
	out_byte = 0xff & (magic >> 2*8);
	write(fd, &out_byte, 1);
	printf("%02X", out_byte);
	out_byte = 0xff & (magic >> 1*8);
	write(fd, &out_byte, 1);
	printf("%02X", out_byte);
	out_byte = 0xff & magic;
	write(fd, &out_byte, 1);
	printf("%02X\n", out_byte);

	/* Output data offset */
	out_byte = 0xff & (data_offset >> 3*8);
	write(fd, &out_byte, 1);
	printf("0x%02X", out_byte);
	out_byte = 0xff & (data_offset >> 2*8);
	write(fd, &out_byte, 1);
	printf("%02X", out_byte);
	out_byte = 0xff & (data_offset >> 1*8);
	write(fd, &out_byte, 1);
	printf("%02X", out_byte);
	out_byte = 0xff & data_offset;
	write(fd, &out_byte, 1);
	printf("%02X\n", out_byte);

	/* output data size */
	out_byte = 0;
	write(fd, &out_byte, 1);
	write(fd, &out_byte, 1);
	write(fd, &out_byte, 1);
	out_byte = 1;
	write(fd, &out_byte, 1);

	/* output samplesnum */
	out_byte = 0xff & (samples_num >> 3*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (samples_num >> 2*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (samples_num >> 1*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & samples_num;
	write(fd, &out_byte, 1);

	/* output device id */
	out_byte = 0xff & (device_id >> 3*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (device_id >> 2*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (device_id >> 1*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & device_id;
	write(fd, &out_byte, 1);

	/* output angle */
	out_byte = 0xff & (angle >> 3*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (angle >> 2*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (angle >> 1*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & angle;
	write(fd, &out_byte, 1);

	/* output command id */
	out_byte = 0xff & (command_id >> 3*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (command_id >> 2*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (command_id >> 1*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & command_id;
	write(fd, &out_byte, 1);

	/* Output some data */
	for (uint32_t i=0; i<samples_num; i++)
	{
	  out_byte = 0xff & i;
	  write(fd, &out_byte, 1);
	}

	/* Output footer */
	uint32_t time_stamp_value = 1234567;
	out_byte = 0xff & (time_stamp_value >> 3*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (time_stamp_value>> 2*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (time_stamp_value >> 1*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & time_stamp_value;
	write(fd, &out_byte, 1);

	uint32_t footer_magic = 809782853;
	out_byte = 0xff & (footer_magic >> 3*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (footer_magic >> 2*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (footer_magic >> 1*8);
	write(fd, &out_byte, 1);
	out_byte = 0xff & (footer_magic >> 0);
	write(fd, &out_byte, 1);
	
	/* close the file */
	close(fd);
  return 0;
}
