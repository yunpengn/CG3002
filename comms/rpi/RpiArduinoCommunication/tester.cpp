///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   tester.cpp
// * Author: Ang Zhi Yuan
// *
// * Created on 20 September, 2018, 4:33 PM
// */
//
//#include <cstdlib>
//#include <cstdio>
//#include "ArduinoCommunication.hpp"
//#include "DataPacketUtilities.hpp"
//#include <thread>
//
//using namespace std;
//
///*
// * 
// */
//
//void populatePacket(DataPacket * target, char * dataPtr) {
//    float * dataPointer = (float *) dataPtr;
//    target->voltage = *dataPointer++;
//    target->current = *dataPointer++;
//    target->bodyX = *dataPointer++;
//    target->bodyY = *dataPointer++;
//    target->bodyZ = *dataPointer++;
//    target->handAcclX = *dataPointer++;
//    target->handAcclY = *dataPointer++;
//    target->handAcclZ = *dataPointer++;
//    target->handGyroX = *dataPointer++;
//    target->handGyroY = *dataPointer++;
//    target->handGyroZ = *dataPointer++;
//    target->legAcclX = *dataPointer++;
//    target->legAcclY = *dataPointer++;
//    target->legAcclZ = *dataPointer++;
//    target->legGyroX = *dataPointer++;
//    target->legGyroY = *dataPointer++;
//    target->legGyroZ = *dataPointer++;
//}
//
//DataPacket * createTestPacket() {
//    DataPacket * result = malloc(sizeof(DataPacket));
//    float data[17];
//    srand (time(NULL));
//    for (int i=0;i < 17; i++)
//        data[i] = (float)rand()/(float)(RAND_MAX);
//    populatePacket(result, (char*) data);
//    return result;
//}
//
//const int numPoints = 500;
//const char HEADER[6] = "Header";
//const char crc[4] = "\0\0\0\0";
//
//DataPacket ** createTestFile(FILE * fp) {
//    DataPacket ** result = malloc(numPoints * sizeof(DataPacket*));
//    for (int i=0; i<numPoints; i++) {
//        result[i] = createTestPacket();
//        fwrite(HEADER, sizeof(char), sizeof(HEADER), fp);
//        fwrite(result[i], sizeof(float), 17, fp);
//        fwrite(crc, sizeof(char), 4, fp);
//    }
//}
//
//int main(int argc, char** argv) {
//    FILE * testFilePointer = fopen("testData", "r+b");
//    fflush(testFilePointer);
//    fseek(testFilePointer, 0, SEEK_SET);
//    createTestFile(testFilePointer);
//    uartFilestream = testFilePointer;
//    std::thread(receiver);
//    return 0;
//}
//
