#include "Sensor_lib.h"
Sensor_lib sensors = Sensor_lib();

float AcX,AcY,AcZ,GyX,GyY,GyZ;

void setup() {
  Serial.begin(9600);
  sensors.initial_setup();
}

void loop() {
  sensors.read_analog_accel_data(&AcX,&AcY,&AcZ,&GyX,&GyY,&GyZ);
  Serial.print("acc_x: "); Serial.print(AcX);
  Serial.print("   acc_y: "); Serial.print(AcY);
  Serial.print("   acc_z: "); Serial.print(AcZ);
  Serial.println("");
  
//  Serial.print("gyr_x: "); Serial.print(GyX);
//  Serial.print("   gyr_y: "); Serial.print(GyY);
//  Serial.print("   gyr_z: "); Serial.print(GyZ);
//  Serial.println("");

  delay(1000);
}
