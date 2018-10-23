#ifndef __SENSOR_LIB_H
#define __SENSOR_LIB_H

#include "Wire.h"
#include "Arduino.h"

// I2C address for two digital sensor
#define DIGITAL_LEG_ADDR	0x68
#define DIGITAL_ARM_ADDR	0x69

// Calibration value for digital sensor
#define DIGITAL_ACCEL_SCALE	16384.0
#define DIGITAL_GYROS_SCALE 131.0

// Pin define for analog accelerometer
#define ANALOG_X			A0
#define ANALOG_Y			A1
#define ANALOG_Z			A2

// Calibration value for analog accelerometer
#define ANALOG_ZERO_XY 		1.65
#define ANALOG_ZERO_Z  		1.75
#define ANALOG_SCALE   		(1.0 / 0.33)
#define ANALOG_Vnorm   		(5.0 / 1023)

// Pin define for power sensors
#define CURRENT_IN  		A3
#define VOLTAGE_IN  		A4

class Sensor_lib {
	public:
		Sensor_lib();
		void initial_setup();
		void read_digital_leg_data(float *acx_f, float *acy_f, float *acz_f, float *gyx_f, float *gyy_f, float *gyz_f);
		void read_digital_arm_data(float *acx_f, float *acy_f, float *acz_f, float *gyx_f, float *gyy_f, float *gyz_f);
		void read_analog_accel_data(float *acx_f, float *acy_f, float *acz_f);
		void read_power_data(float *voltage, float *current);

	private:
		void setup_digital_leg();
		void setup_digital_arm();
		void read_digital_accel_data(int addr, float *acx_f, float *acy_f, float *acz_f, float *gyx_f, float *gyy_f, float *gyz_f);
};

#endif /* __SENSOR_LIB_H */
