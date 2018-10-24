/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "DataHandler.hpp"
#include <stdlib.h>
#include <math.h>
#include <cstdio>
#include <string>
#include <chrono>
#include <float.h>

void logToFile(FILE * fp, long timeMillis, DataPacket * packet);

using namespace std;

static const string DEFAULT_FILE_NAME = "dataDump.csv";

DataBuffer::DataBuffer(string fileName, long windowDurationMillis) {
    if (fileName.length() == 0)
        fileName = DEFAULT_FILE_NAME;
    logFile = fopen(fileName.c_str(), "w");
    fprintf(logFile, "%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
            "Time", "Energy", "Voltage", "Current", "BodyX", "BodyY", "BodyZ", "handAcclX", "handAcclY",
            "handAcclZ", "handGyroX", "handGyroY", "handGyroZ", "legAcclX", "legAcclY",
            "legAcclZ", "legGyroX", "legGyroY", "legGyroZ");
    startTime = chrono::steady_clock::now();
    this->windowDurationMillis = windowDurationMillis;
}

void DataBuffer::addTotal(const DataPacket &packet) {
    movingTotal[0] += packet.bodyX; movingTotalSq[0] += pow(packet.bodyX,2);
    movingTotal[1] += packet.bodyY; movingTotalSq[1] += pow(packet.bodyY,2);
    movingTotal[2] += packet.bodyZ; movingTotalSq[2] += pow(packet.bodyZ,2);
    movingTotal[3] += packet.handAcclX; movingTotalSq[3] += pow(packet.handAcclX,2);
    movingTotal[4] += packet.handAcclY; movingTotalSq[4] += pow(packet.handAcclY,2);
    movingTotal[5] += packet.handAcclZ; movingTotalSq[5] += pow(packet.handAcclZ,2);
    movingTotal[6] += packet.handGyroX; movingTotalSq[6] += pow(packet.handGyroX,2);
    movingTotal[7] += packet.handGyroY; movingTotalSq[7] += pow(packet.handGyroY,2);
    movingTotal[8] += packet.handGyroZ; movingTotalSq[8] += pow(packet.handGyroZ,2);
    movingTotal[9] += packet.legAcclX; movingTotalSq[9] += pow(packet.legAcclX,2);
    movingTotal[10] += packet.legAcclY; movingTotalSq[10] += pow(packet.legAcclY,2);
    movingTotal[11] += packet.legAcclZ; movingTotalSq[11] += pow(packet.legAcclZ,2);
    movingTotal[12] += packet.legGyroX; movingTotalSq[12] += pow(packet.legGyroX,2);
    movingTotal[13] += packet.legGyroY; movingTotalSq[13] += pow(packet.legGyroY,2);
    movingTotal[14] += packet.legGyroZ; movingTotalSq[14] += pow(packet.legGyroZ,2);
}

void DataBuffer::subtractTotal(const DataPacket &packet) {
    movingTotal[0] -= packet.bodyX; movingTotalSq[0] -= pow(packet.bodyX,2);
    movingTotal[1] -= packet.bodyY; movingTotalSq[1] -= pow(packet.bodyY,2);
    movingTotal[2] -= packet.bodyZ; movingTotalSq[2] -= pow(packet.bodyZ,2);
    movingTotal[3] -= packet.handAcclX; movingTotalSq[3] -= pow(packet.handAcclX,2);
    movingTotal[4] -= packet.handAcclY; movingTotalSq[4] -= pow(packet.handAcclY,2);
    movingTotal[5] -= packet.handAcclZ; movingTotalSq[5] -= pow(packet.handAcclZ,2);
    movingTotal[6] -= packet.handGyroX; movingTotalSq[6] -= pow(packet.handGyroX,2);
    movingTotal[7] -= packet.handGyroY; movingTotalSq[7] -= pow(packet.handGyroY,2);
    movingTotal[8] -= packet.handGyroZ; movingTotalSq[8] -= pow(packet.handGyroZ,2);
    movingTotal[9] -= packet.legAcclX; movingTotalSq[9] -= pow(packet.legAcclX,2);
    movingTotal[10] -= packet.legAcclY; movingTotalSq[10] -= pow(packet.legAcclY,2);
    movingTotal[11] -= packet.legAcclZ; movingTotalSq[11] -= pow(packet.legAcclZ,2);
    movingTotal[12] -= packet.legGyroX; movingTotalSq[12] -= pow(packet.legGyroX,2);
    movingTotal[13] -= packet.legGyroY; movingTotalSq[13] -= pow(packet.legGyroY,2);
    movingTotal[14] -= packet.legGyroZ; movingTotalSq[14] -= pow(packet.legGyroZ,2);
}

void populatePacket(DataPacket * target, void * dataPtr) {
    float * dataPointer = (float *) dataPtr;
    target->energy = *dataPointer++;
    target->voltage = *dataPointer++;
    target->current = *dataPointer++;
    target->bodyX = *dataPointer++;
    target->bodyY = *dataPointer++;
    target->bodyZ = *dataPointer++;
    target->handAcclX = *dataPointer++;
    target->handAcclY = *dataPointer++;
    target->handAcclZ = *dataPointer++;
    target->handGyroX = *dataPointer++;
    target->handGyroY = *dataPointer++;
    target->handGyroZ = *dataPointer++;
    target->legAcclX = *dataPointer++;
    target->legAcclY = *dataPointer++;
    target->legAcclZ = *dataPointer++;
    target->legGyroX = *dataPointer++;
    target->legGyroY = *dataPointer++;
    target->legGyroZ = *dataPointer++;
}

void DataBuffer::addPacket(void * rawData) {
    //Create DataPacket based on raw data
    using namespace std::chrono;
    PacketWithTime packet;
    long currTimeMillis =  duration_cast<milliseconds>(steady_clock::now() - startTime).count();
    populatePacket(&(packet.data), rawData);
    packet.timeMillis = currTimeMillis;
    packetBuffer.push_back(packet);
    addTotal(packet.data);
    long earliestValidTimeMillis = max(currTimeMillis - windowDurationMillis, (unsigned long)0);
    while(packetBuffer.front().timeMillis < earliestValidTimeMillis) {
        subtractTotal(packetBuffer.front().data);
        packetBuffer.pop_front();
    }
    logToFile(logFile, currTimeMillis, &(packet.data));
}

void DataBuffer::getMeanVariance(float * resultArray) {
    int numPoints = packetBuffer.size();
    for (int i=0; i<15; i++) {
        resultArray[i] = movingTotal[i]/numPoints;
    }
    for (int i=0; i<15; i++) {
        resultArray[i+15] = (movingTotalSq[i]/numPoints) - pow(resultArray[i], 2);
    }
}

void DataBuffer::getMaxMin(float * resultArray) {
    //deque<PacketWithTime> localCopy = ((const deque<PacketWithTime>)packetBuffer);
    for (int i=0; i<15; i++)
        resultArray[i] = FLT_MIN;
    for (int i=15;i<30;i++)
        resultArray[i] = FLT_MAX;
    for(int i=0; i<packetBuffer.size(); i++) {
        DataPacket packet = packetBuffer[i].data;
        if (resultArray[0]<packet.bodyX) resultArray[0] = packet.bodyX;
        if (resultArray[1]<packet.bodyY) resultArray[1] = packet.bodyY;
        if (resultArray[2]<packet.bodyZ) resultArray[2] = packet.bodyZ;
        if (resultArray[3]<packet.handAcclX) resultArray[3] = packet.handAcclX;
        if (resultArray[4]<packet.handAcclY) resultArray[4] = packet.handAcclY;
        if (resultArray[5]<packet.handAcclZ) resultArray[5] = packet.handAcclZ;
        if (resultArray[6]<packet.handGyroX) resultArray[6] = packet.handGyroX;
        if (resultArray[7]<packet.handGyroY) resultArray[7] = packet.handGyroY;
        if (resultArray[8]<packet.handGyroZ) resultArray[8] = packet.handGyroZ;
        if (resultArray[9]<packet.legAcclX) resultArray[9] = packet.legAcclX;
        if (resultArray[10]<packet.legAcclY) resultArray[10] = packet.legAcclY;
        if (resultArray[11]<packet.legAcclZ) resultArray[11] = packet.legAcclZ;
        if (resultArray[12]<packet.legGyroX) resultArray[12] = packet.legGyroX;
        if (resultArray[13]<packet.legGyroY) resultArray[13] = packet.legGyroY;
        if (resultArray[14]<packet.legGyroZ) resultArray[14] = packet.legGyroZ;
        if (resultArray[15]>packet.bodyX) resultArray[15] = packet.bodyX;
        if (resultArray[16]>packet.bodyY) resultArray[16] = packet.bodyY;
        if (resultArray[17]>packet.bodyZ) resultArray[17] = packet.bodyZ;
        if (resultArray[18]>packet.handAcclX) resultArray[18] = packet.handAcclX;
        if (resultArray[19]>packet.handAcclY) resultArray[19] = packet.handAcclY;
        if (resultArray[20]>packet.handAcclZ) resultArray[20] = packet.handAcclZ;
        if (resultArray[21]>packet.handGyroX) resultArray[21] = packet.handGyroX;
        if (resultArray[22]>packet.handGyroY) resultArray[22] = packet.handGyroY;
        if (resultArray[23]>packet.handGyroZ) resultArray[23] = packet.handGyroZ;
        if (resultArray[24]>packet.legAcclX) resultArray[24] = packet.legAcclX;
        if (resultArray[25]>packet.legAcclY) resultArray[25] = packet.legAcclY;
        if (resultArray[26]>packet.legAcclZ) resultArray[26] = packet.legAcclZ;
        if (resultArray[27]>packet.legGyroX) resultArray[27] = packet.legGyroX;
        if (resultArray[28]>packet.legGyroY) resultArray[28] = packet.legGyroY;
        if (resultArray[29]>packet.legGyroZ) resultArray[29] = packet.legGyroZ;
    }
}
/*
 * Puts the following values into the result Array: {Energy, Voltage, Current}
 */
void DataBuffer::getPowerData(float* resultArray) {
    DataPacket latestPacket = packetBuffer.back().data;
    resultArray[0] = latestPacket.energy;
    resultArray[1] = latestPacket.voltage;
    resultArray[2] = latestPacket.current;
    return;
}

void logToFile(FILE * fp, long timeMillis, DataPacket * packet) {
    static long lastCheckpoint = 0;
    fprintf(fp, "%ld, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", timeMillis,
            packet->energy, packet->voltage, packet->current, packet->bodyX, packet->bodyY, 
            packet->bodyZ, packet->handAcclX, packet->handAcclY, packet->handAcclZ, 
            packet->handGyroX, packet->handGyroY, packet->handGyroZ, packet->legAcclX, 
            packet->legAcclY, packet->legAcclZ, packet->legGyroX, packet->legGyroY, 
            packet->legGyroZ);
    if (timeMillis/1000 > lastCheckpoint) {
        lastCheckpoint = timeMillis/1000;
        printf("Recorded %ld seconds\n", lastCheckpoint);
    }
}
