#include <EEPROM.h>
#include <Arduino_FreeRTOS.h>
#include <task.h>
#include "Sensor_lib.h"
#define STACK_SIZE 200
Sensor_lib sensors = Sensor_lib();

float AcX = 0.5,AcY = 1.5,AcZ = 2.5,GyX = 3.5,GyY = 4.5,GyZ = 5.5,voltage = -1.5,current = -2.5;
float legAcX = 6.5, legAcY = 7.5, legAcZ = 8.5, legGyX = 9.5, legGyY = 10.5, legGyZ = 11.5;

void inline sendFloat(float f){
  Serial1.write((byte*)&f, sizeof(f));
  Serial.print(f);
}

char HEADER[6] = "Header";
char crc[4] = "\0\0\0\0";

void sensorTask(void *p) 
{ 
  Serial.println("In Sensor Task");   
  boolean flag = 0;
  unsigned long iterationNum = 0;
  
  while(1){
    if (iterationNum%100==0) {
      Serial.print("Started loop iteration ");
      Serial.print(++iterationNum);
      Serial.print("\n");
    }
    iterationNum++;
    if(Serial1.available() > 0){
      char x = Serial1.read();
      if(x == 's'){
        Serial.print("Start signal caught\n");
        flag = 1;
      } else if(x == 'q'){
        Serial.print("Stop signal caught\n");
        flag = 0;
      }
    }

    if(flag){
      Serial1.write(HEADER, 6);
      //Serial.println("Starting to read from sensors\n");
      
      //sensors.read_power_data(&voltage.floatingPoint, &current.floatingPoint);
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

      sensors.read_digital_leg_data(&legAcX,&legAcY,&legAcZ,&legGyX,&legGyY,&legGyZ);
      sendFloat(legAcX);
      sendFloat(legAcY);
      sendFloat(legAcZ);      
      sendFloat(legGyX);
      sendFloat(legGyY);
      sendFloat(legGyZ);

      Serial1.write(crc, sizeof(crc));
      Serial.print("\n");
    }
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() 
{
  // put your setup code here, to run once:
  Serial1.begin(2000000); 
  Serial.begin(9600); // opens serial port, sets data rate to 9600
  //sensors.initial_setup();
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
