#include "Sensor_lib.h"
Sensor_lib sensors = Sensor_lib();

#define TIME_INTERVAL 500 // ms

float AcX,AcY,AcZ,GyX,GyY,GyZ;
float current,voltage;
float energy = 0.0;

void setup() {
  Serial.begin(9600);
//  sensors.initial_setup();
}

void loop() {
//  sensors.read_analog_accel_data(&AcX,&AcY,&AcZ/*,&GyX,&GyY,&GyZ*/);
//  Serial.print("acc_x: "); Serial.print(AcX);
//  Serial.print("   acc_y: "); Serial.print(AcY);
//  Serial.print("   acc_z: "); Serial.print(AcZ);
//  Serial.println("");
  
//  Serial.print("gyr_x: "); Serial.print(GyX);
//  Serial.print("   gyr_y: "); Serial.print(GyY);
//  Serial.print("   gyr_z: "); Serial.print(GyZ);
//  Serial.println("");

    sensors.read_power_data(&voltage,&current);
    energy += current * voltage * TIME_INTERVAL / 1000.0;
    Serial.print("Current: "); Serial.print(current);
    Serial.print("A   Voltage: "); Serial.print(voltage);
    Serial.print("V   Power: "); Serial.print(current * voltage);
    Serial.print("W  Cumulative Energy: "); Serial.print(energy);
    Serial.print("J");
    Serial.println("");

  delay(TIME_INTERVAL);
}
