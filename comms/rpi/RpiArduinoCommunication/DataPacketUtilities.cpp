/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "DataPacketUtilities.hpp"
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <chrono>

using namespace std::chrono;

FILE * debugFp;
steady_clock::time_point startTime;

inline int max(int a, int b) {
    if (a>b) return a;
    else return b;
}

void logToFile(FILE * fp, DataPacket * packet) {
    milliseconds millis = steady_clock::now() - startTime;
    fprintf(fp, "%ld, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", millis,
            packet->voltage, packet->current, packet->bodyX, packet->bodyY, 
            packet->bodyZ, packet->handAcclX, packet->handAcclY, packet->handAcclZ, 
            packet->handGyroX, packet->handGyroY, packet->handGyroZ, packet->legAcclX, 
            packet->legAcclY, packet->legAcclZ, packet->legGyroX, packet->legGyroY, 
            packet->legGyroZ);
}

void addPacket(DataBuffer * buffer, DataPacket * packet) {
    DataPacket * oldPacket = buffer->dataPacketPtrArray[buffer->endIndex];
    logToFile(debugFp, packet);
    if (oldPacket != NULL)
        free(oldPacket);
    buffer->dataPacketPtrArray[buffer->endIndex] = packet;
    
    //Set start index to correct location
    int numValid = buffer->endIndex - buffer->startIndex;
    if (numValid<0)
        numValid += buffer->bufferSize;
    int numToInvalidate = max(numValid-50, 0);
    int newStartIndex = buffer->startIndex + numToInvalidate;
    if (newStartIndex>=buffer->bufferSize)
        newStartIndex-=buffer->bufferSize;
    buffer->startIndex = newStartIndex;
}

void initUtils() {
    debugFp = fopen("dataDump.csv", "w");
    fprintf(debugFp, "%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n",
            "Time", "Voltage", "Current", "BodyX", "BodyY", "BodyZ", "handAcclX", "handAcclY",
            "handAcclZ", "legGyroX", "legGyroY", "legGyroZ", "legAcclX", "legAcclY",
            "legAcclZ", "legGyroX", "legGyroY", "legGyroZ");
    startTime = steady_clock::now();
}

void closeFile() {
    fclose(debugFp);
}
