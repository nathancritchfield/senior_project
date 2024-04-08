/*
 * VESC.h
 *
 *  Created on: Mar 23, 2024
 *      Author: nate_
 */

#ifndef VESC_H_
#define VESC_H_

#include <stdint.h>
#include "datatypes.h"

/** Struct to store the telemetry data returned by the VESC */
struct dataPackage {
	float avgMotorCurrent;
	float avgInputCurrent;
	float dutyCycleNow;
	float rpm;
	float inpVoltage;
	float ampHours;
	float ampHoursCharged;
	float wattHours;
	float wattHoursCharged;
	long tachometer;
	long tachometerAbs;
	float tempMosfet;
	float tempMotor;
	float pidPos;
	uint8_t id;
	mc_fault_code error;
};

/** Struct to hold the nunchuck values to send over UART */
struct nunchuckPackage {
	int	valueX;
	int	valueY;
	bool upperButton; // valUpperButton
	bool lowerButton; // valLowerButton
};

struct FWversionPackage {
	uint8_t major;
	uint8_t minor;
};

/** Variable to hold measurements returned from VESC */
extern struct dataPackage VESCdata;

/** Variable to hold nunchuck values */
extern struct nunchuckPackage VESCnunchuck;

/** Variable to hold firmware version */
extern struct FWversionPackage VESCfw_version;


/*
 * Functions
 */
int VESCGetFWVersion(uint8_t CAN_ID);
int VESCGetValues(uint8_t CAN_ID);
void VESCSetCurrent(float current, uint8_t CAN_ID);

#endif /* VESC_H_ */
