#include "Sensor_lib.h"

Sensor_lib::Sensor_lib() {
}

void Sensor_lib::setup_digital_leg() {
    Wire.beginTransmission(DIGITAL_LEG_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 registe
    Wire.write(0);    // set to zero (wakes up the MPU-6050), config clock to 8MHz
    Wire.endTransmission(true);

    // setup Gyroscope range to 2000 degree/s
    Wire.beginTransmission(DIGITAL_LEG_ADDR);
    Wire.write(0x1B);
    Wire.write(0x18);
    Wire.endTransmission(true);

    // setup Accelerometer range to 8g
    Wire.beginTransmission(DIGITAL_LEG_ADDR);
    Wire.write(0x1C);
    Wire.write(0x10);
    Wire.endTransmission(true);
}

void Sensor_lib::setup_digital_arm() {
    Wire.beginTransmission(DIGITAL_ARM_ADDR);
    Wire.write(0x6B); // PWR_MGMT_1 registe
    Wire.write(0);    // set to zero (wakes up the MPU-6050), config clock to 8MHz
    Wire.endTransmission(true);

    // setup Gyroscope range to 2000 degree/s
    Wire.beginTransmission(DIGITAL_ARM_ADDR);
    Wire.write(0x1B);
    Wire.write(0x18);
    Wire.endTransmission(true);

    // setup Accelerometer range to 8g
    Wire.beginTransmission(DIGITAL_ARM_ADDR);
    Wire.write(0x1C);
    Wire.write(0x10);
    Wire.endTransmission(true);
}

void Sensor_lib::read_digital_accel_data(int addr, float *acx_f, float *acy_f, float *acz_f,
		float *gyx_f, float *gyy_f, float *gyz_f) {
	int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

	  Wire.beginTransmission(addr);
    Wire.write(0x3B);   // starting with register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(addr,14,true);    // request a total of 14 registers
    AcX = Wire.read()<<8 | Wire.read();         // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
    AcY = Wire.read()<<8 | Wire.read();         // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
    AcZ = Wire.read()<<8 | Wire.read();         // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
    Wire.read();         					// skip TEMP
    Wire.read();         					// skip TEMP
    GyX = Wire.read()<<8 | Wire.read();         // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
    GyY = Wire.read()<<8 | Wire.read();         // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
    GyZ = Wire.read()<<8 | Wire.read();         // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

    *acx_f = (float)AcX / DIGITAL_ACCEL_SCALE;
    *acy_f = (float)AcY / DIGITAL_ACCEL_SCALE;
    *acz_f = (float)AcZ / DIGITAL_ACCEL_SCALE;

    *gyx_f = (float)GyX / DIGITAL_GYROS_SCALE;
    *gyy_f = (float)GyY / DIGITAL_GYROS_SCALE;
    *gyz_f = (float)GyZ / DIGITAL_GYROS_SCALE;
}


void Sensor_lib::initial_setup() {
  Wire.begin();
	setup_digital_leg();
	setup_digital_arm();
}

void Sensor_lib::read_digital_leg_data(float *acx_f, float *acy_f, float *acz_f,
		float *gyx_f, float *gyy_f, float *gyz_f) {
	read_digital_accel_data(DIGITAL_LEG_ADDR, acx_f, acy_f, acz_f, gyx_f, gyy_f, gyz_f);
}

void Sensor_lib::read_digital_arm_data(float *acx_f, float *acy_f, float *acz_f,
		float *gyx_f, float *gyy_f, float *gyz_f) {
	read_digital_accel_data(DIGITAL_ARM_ADDR, acx_f, acy_f, acz_f, gyx_f, gyy_f, gyz_f);
}

void Sensor_lib::read_analog_accel_data(float *acx_f, float *acy_f, float *acz_f) {
	*acx_f = (analogRead(ANALOG_X) * ANALOG_Vnorm - ANALOG_ZERO_XY) * ANALOG_SCALE;
	*acy_f = (analogRead(ANALOG_Y) * ANALOG_Vnorm - ANALOG_ZERO_XY) * ANALOG_SCALE;
	*acz_f = (analogRead(ANALOG_Z) * ANALOG_Vnorm - ANALOG_ZERO_Z)  * ANALOG_SCALE;
}

void Sensor_lib::read_power_data(float *voltage, float *current) {
	int raw_current = analogRead(CURRENT_IN);
    int raw_voltage = analogRead(VOLTAGE_IN);

    *current = raw_current * (5.0 / 1023.0); //* 1000.0 / (0.1 * 10000.0);
    *voltage = raw_voltage * (5.0 / 1023.0) * (81.58 + 81.28) / 81.28; // TODO calibration value need to be changed.
}
