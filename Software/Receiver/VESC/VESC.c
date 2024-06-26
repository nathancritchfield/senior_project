/*
 * VESC.c
 *
 *  Created on: Mar 23, 2024
 *      Author: nate_
 */
#include "VESC.h"
#include "usart.h"
#include <string.h>
#include "datatypes.h"
#include "buffer.h"

/** Variable to hold measurements returned from VESC */
struct dataPackage VESCdata;

/** Variable to hold nunchuck values */
struct nunchuckPackage VESCnunchuck;

/** Variable to hold firmware version */
struct FWversionPackage VESCfw_version;



// CRC Table
const unsigned short crc16_tab[] = { 0x0000, 0x1021, 0x2042, 0x3063, 0x4084,
		0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad,
		0xe1ce, 0xf1ef, 0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7,
		0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
		0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a,
		0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 0x3653, 0x2672,
		0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719,
		0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5, 0x6886, 0x78a7,
		0x0840, 0x1861, 0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948,
		0x9969, 0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50,
		0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b,
		0xab1a, 0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
		0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97,
		0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe,
		0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca,
		0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3,
		0x5004, 0x4025, 0x7046, 0x6067, 0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d,
		0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214,
		0x6277, 0x7256, 0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c,
		0xc50d, 0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
		0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3,
		0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 0xd94c, 0xc96d,
		0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806,
		0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e,
		0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1,
		0x1ad0, 0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b,
		0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0,
		0x0cc1, 0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
		0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 };

unsigned short crc16(unsigned char *buf, unsigned int len) {
	unsigned int i;
	unsigned short cksum = 0;
	for (i = 0; i < len; i++) {
		cksum = crc16_tab[(((cksum >> 8) ^ *buf++) & 0xFF)] ^ (cksum << 8);
	}
	return cksum;
}

int VESCProcessPacket(uint8_t * message) {

	COMM_PACKET_ID packetId;
	int32_t index = 0;

	packetId = (COMM_PACKET_ID)message[0];
	message++; // Removes the packetId from the actual message (payload)

	switch (packetId){
		case COMM_FW_VERSION: // Structure defined here: https://github.com/vedderb/bldc/blob/43c3bbaf91f5052a35b75c2ff17b5fe99fad94d1/commands.c#L164

			VESCfw_version.major = message[index++];
			VESCfw_version.minor = message[index++];
			return true;
		case COMM_GET_VALUES: // Structure defined here: https://github.com/vedderb/bldc/blob/43c3bbaf91f5052a35b75c2ff17b5fe99fad94d1/commands.c#L164

			VESCdata.tempMosfet 		= buffer_get_float16(message, 10.0, &index); 	// 2 bytes - mc_interface_temp_fet_filtered()
			VESCdata.tempMotor 			= buffer_get_float16(message, 10.0, &index); 	// 2 bytes - mc_interface_temp_motor_filtered()
			VESCdata.avgMotorCurrent 	= buffer_get_float32(message, 100.0, &index); // 4 bytes - mc_interface_read_reset_avg_motor_current()
			VESCdata.avgInputCurrent 	= buffer_get_float32(message, 100.0, &index); // 4 bytes - mc_interface_read_reset_avg_input_current()
			index += 4; // Skip 4 bytes - mc_interface_read_reset_avg_id()
			index += 4; // Skip 4 bytes - mc_interface_read_reset_avg_iq()
			VESCdata.dutyCycleNow 		= buffer_get_float16(message, 1000.0, &index); 	// 2 bytes - mc_interface_get_duty_cycle_now()
			VESCdata.rpm 				= buffer_get_float32(message, 1.0, &index);		// 4 bytes - mc_interface_get_rpm()
			VESCdata.inpVoltage 		= buffer_get_float16(message, 10.0, &index);		// 2 bytes - GET_INPUT_VOLTAGE()
			VESCdata.ampHours 			= buffer_get_float32(message, 10000.0, &index);	// 4 bytes - mc_interface_get_amp_hours(false)
			VESCdata.ampHoursCharged 	= buffer_get_float32(message, 10000.0, &index);	// 4 bytes - mc_interface_get_amp_hours_charged(false)
			VESCdata.wattHours			= buffer_get_float32(message, 10000.0, &index);	// 4 bytes - mc_interface_get_watt_hours(false)
			VESCdata.wattHoursCharged	= buffer_get_float32(message, 10000.0, &index);	// 4 bytes - mc_interface_get_watt_hours_charged(false)
			VESCdata.tachometer 		= buffer_get_int32(message, &index);				// 4 bytes - mc_interface_get_tachometer_value(false)
			VESCdata.tachometerAbs 		= buffer_get_int32(message, &index);				// 4 bytes - mc_interface_get_tachometer_abs_value(false)
			VESCdata.error 				= (mc_fault_code)message[index++];								// 1 byte  - mc_interface_get_fault()
			VESCdata.pidPos				= buffer_get_float32(message, 1000000.0, &index);	// 4 bytes - mc_interface_get_pid_pos_now()
			VESCdata.id					= message[index++];								// 1 byte  - app_get_configuration()->controller_id

			return true;

		break;

		/* case COMM_GET_VALUES_SELECTIVE:

			uint32_t mask = 0xFFFFFFFF; */

		default:
			return false;
		break;
	}
}

int VESCSendMessage(uint8_t *payload, int payloadSize){
	int count = 0;
	uint8_t messageSend[256];
	uint16_t crcPayload = crc16(payload, payloadSize);

	if(payloadSize <= 256){
		messageSend[count++] = 2;
		messageSend[count++] = payloadSize;
	}
	else{
		messageSend[count++] = 3;
		messageSend[count++] = (uint8_t)(payloadSize >> 8);
		messageSend[count++] = (uint8_t)(payloadSize & 0xFF);
	}

	memcpy(messageSend + count, payload, payloadSize);
	count += payloadSize;

	messageSend[count++] = (uint8_t)(crcPayload >> 8);
	messageSend[count++] = (uint8_t)(crcPayload & 0xFF);
	messageSend[count++] = 3;

	HAL_UART_Transmit(&huart1, messageSend, count, HAL_MAX_DELAY);

	return count;
}

int VESCReceiveMessage(uint8_t *payloadReceived){
	uint8_t messageStart[2] = {0};
	uint8_t messageReceived[256] = {0};

	uint16_t crcMessage = 0;
	uint16_t crcPayload = 0;
	uint8_t lenMes = 0;

	HAL_UART_Receive(&huart1, messageStart, 2, HAL_MAX_DELAY);

	//Handle message less than 255 bytes. Messages larger than 255 bytes are not handleable
	if(messageStart[0] == 2){
		HAL_UART_Receive(&huart1, messageReceived, messageStart[1] + 3, HAL_MAX_DELAY); //+3 for CRC and End
	}

	lenMes = messageStart[1] + 3;

	//Rebuild crc
	crcMessage = messageReceived[lenMes - 3] << 8;
	crcMessage &= 0xFF00;
	crcMessage += messageReceived[lenMes - 2];

	//Extract payload
	memcpy(payloadReceived, messageReceived, messageStart[1]);

	crcPayload = crc16(payloadReceived, messageStart[1]);

	if(crcPayload == crcMessage){
		return messageStart[1];
	}
	else{
		return 0;
	}
}



int VESCGetFWVersion(uint8_t CAN_ID){
	int32_t index = 0;
	int payloadSize = (CAN_ID == 0 ? 1 : 3);
	uint8_t payload[3];

	uint8_t message[256];
	int messageLength;

	if (CAN_ID != 0) {
		payload[index++] = COMM_FORWARD_CAN;
		payload[index++] = CAN_ID;
	}
	payload[index++] = COMM_FW_VERSION;
	VESCSendMessage(payload, payloadSize);

	messageLength = VESCReceiveMessage(message);
	if(messageLength > 0){
		return VESCProcessPacket(message);
	}
	else {
		return 0;
	}
}

int VESCGetValues(uint8_t CAN_ID){

	int32_t index = 0;
	int payloadSize = (CAN_ID == 0 ? 1 : 3);
	uint8_t payload[3];
	if (CAN_ID != 0) {
		payload[index++] = COMM_FORWARD_CAN;
		payload[index++] = CAN_ID;
	}
	payload[index++] = COMM_GET_VALUES;

	VESCSendMessage(payload, payloadSize);

	uint8_t message[256];
	int messageLength = VESCReceiveMessage(message);

	if (messageLength > 55) {
		return VESCProcessPacket(message);
	}
	return 0;
}

void VESCSetCurrent(float current, uint8_t CAN_ID){
	int32_t index = 0;
	int payloadSize = (CAN_ID == 0 ? 5 : 7);
	uint8_t payload[7];
	if (CAN_ID != 0) {
		payload[index++] = COMM_FORWARD_CAN;
		payload[index++] = CAN_ID;
	}
	payload[index++] = COMM_SET_CURRENT;
	buffer_append_int32(payload, (int32_t)(current * 1000), &index);
	VESCSendMessage(payload, payloadSize);
}
