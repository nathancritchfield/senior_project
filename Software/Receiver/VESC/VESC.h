/*
 * VESC.h
 *
 *  Created on: Mar 23, 2024
 *      Author: nate_
 */

#ifndef VESC_H_
#define VESC_H_

#include <stdint.h>

/*
 * Functions
 */
unsigned short crc16(unsigned char *buf, unsigned int len);
int VESCReceiveMessage(uint8_t *payloadReceived);
int VESCSendMessage(uint8_t *payload, int payloadSize);

#endif /* VESC_H_ */
