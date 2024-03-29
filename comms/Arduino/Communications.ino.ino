#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "Sensor_lib.h"
#include <CRC32.h>

#define STACK_SIZE 200
Sensor_lib sensors = Sensor_lib();

float AcX, AcY, AcZ, GyX, GyY, GyZ, voltage, current;
float legAcX, legAcY, legAcZ, legGyX, legGyY, legGyZ;
float powerbefore = 0; 
float powerafter, zero;
float energy;
CRC32 crc;
int numBytes = 0;

void inline sendFloat(float f){
  Serial1.write((byte*)&f, sizeof(f));
  numBytes += sizeof(f);
  crc.update((byte*)&f, sizeof(f));
}

void inline sendU(uint32_t f){
  numBytes += sizeof(f);
  Serial1.write((byte*)&f, sizeof(f));
}

char HEADER[6] = "Header";
//char crc[4] = "\0\0\0\0";

void sensorTask(void *p) 
{ 
  Serial.println("In Sensor Task");   
  boolean flag = 0;
  int i = 0;
  float totalEnergy, prevTime, Time = 0;
  int count = 0;
  uint32_t checksum;
  
  unsigned long iterationNum = 0;
  
  while(1){
    
    /*
    if (iterationNum%1000==0) {
      Serial.print("Started loop iteration ");
      Serial.print(++iterationNum);
      Serial.print("\n");
    }
    */
    
    iterationNum++;
    if((Serial1.available() > 0)){
      char x = Serial1.read();
      if(x == 's'){
        //Serial.print("Start signal caught\n");
        flag = 1;
        totalEnergy = 0;
        powerbefore = 0;
        prevTime = millis();
      } else if(x == 'q'){
        //Serial.print("Stop signal caught\n");
        flag = 0;
      }
    }

    if(flag){
      numBytes = 0;
      crc.reset();
      Serial1.write(HEADER, 6);
      
      sensors.read_power_data(&voltage,&current);
      Time = millis();
      powerafter = voltage * current;
      if(powerbefore == 0.0){
      energy = ( powerafter * (Time - prevTime) / 1000.0);
      } else {
      energy = ((powerbefore + powerafter) / 2.0) * (Time - prevTime)/ 1000.0;
      }
      //Serial.println(voltage); Serial.println(current); Serial.println(Time); Serial.println(prevTime); Serial.println(energy);
      totalEnergy += energy;
      powerbefore = powerafter;
      prevTime = Time;
      
      //Serial.print(Time); Serial.print(" "); Serial.print(prevTime); Serial.print(" "); Serial.print(energy); Serial.print(" "); Serial.println(totalEnergy);
      sendFloat(totalEnergy);
      sendFloat(voltage);
      sendFloat(current);
      
      sensors.read_analog_accel_data(&AcX,&AcY,&AcZ);
      sendFloat(AcX);
      sendFloat(AcY);
      sendFloat(AcZ);
      
      sensors.read_digital_arm_data(&AcX,&AcY,&AcZ,&GyX,&GyY,&GyZ);
      sendFloat(AcX);
      sendFloat(AcY);
      sendFloat(AcZ);      
      sendFloat(GyX);
      sendFloat(GyY);
      sendFloat(GyZ);

      /*
      Serial.print(AcX, 4); Serial.print(" "); Serial.print(AcY, 4); Serial.print(" "); Serial.print(AcZ, 4); Serial.print(" ");
      Serial.print(GyX, 4); Serial.print(" "); Serial.print(GyY, 4); Serial.print(" "); Serial.println(GyZ, 4);
      */
      
      sensors.read_digital_leg_data(&legAcX,&legAcY,&legAcZ,&legGyX,&legGyY,&legGyZ);
      sendFloat(legAcX);
      sendFloat(legAcY);
      sendFloat(legAcZ);      
      sendFloat(legGyX);
      sendFloat(legGyY);
      sendFloat(legGyZ);

      /*
      Serial.print(AcX, 4); Serial.print(" "); Serial.print(AcY, 4); Serial.print(" "); Serial.print(AcZ, 4); Serial.print(" ");
      Serial.print(GyX, 4); Serial.print(" "); Serial.print(GyY, 4); Serial.print(" "); Serial.println(GyZ, 4);
      */
      
      checksum = crc.finalize();
      sendU(checksum);
      //Serial.println(checksum, HEX); Serial.println(numBytes);
    }
    //vTaskDelay(1 / portTICK_PERIOD_MS); //Block for 1 ms
  }
}


void setup() 
{
  // put your setup code here, to run once:
  Serial1.begin(2000000); 
  Serial.begin(9600); // opens serial port, sets data rate to 9600
  sensors.initial_setup();
  xTaskCreate(sensorTask, //Pointer to the task entry function
              "sensorTask", //Task name
              STACK_SIZE, //Stack size
              NULL, //Pointer that will be used as parameter
              1, //Task priority
              NULL); //Used to pass back a handle by which the created task can be referenced.
}

void loop() 
{
  // put your main code here, to run repeatedly: 
}
