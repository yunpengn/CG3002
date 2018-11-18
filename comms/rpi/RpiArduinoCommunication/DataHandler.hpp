/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DataPacketFormat.hpp
 * Author: Ang Zhi Yuan
 *
 * Created on 20 September, 2018, 2:47 PM
 */

#ifndef DATAPACKETFORMAT_HPP
#define DATAPACKETFORMAT_HPP

#include <chrono>
#include <deque>
#include <string>
#include <mutex>

struct DataPacket{
    float energy;
    float voltage;
    float current;
    float bodyX, bodyY, bodyZ;
    float handAcclX, handAcclY, handAcclZ;
    float handGyroX, handGyroY, handGyroZ;
    float legAcclX, legAcclY, legAcclZ;
    float legGyroX, legGyroY, legGyroZ;
};

class DataBuffer {
    struct PacketWithTime {
        long timeMillis;
        DataPacket data;
    };
    
    std::deque<PacketWithTime> packetBuffer;
    std::mutex bufferMutex;
    unsigned long windowDurationMillis;
    FILE * logFile;
    float movingTotal[15] = {}, movingTotalSq[15] = {};
    void addTotal(const DataPacket &packet);
    void subtractTotal(const DataPacket &packet);
    
public:
    std::chrono::steady_clock::time_point startTime;
    DataBuffer(std::string fileName, long windowDurationMillis);
    void addPacket(void * rawData);
    void getMeanVariance(float * resultArray);
    void getMaxMin(float * resultArray);
    void getPowerData(float * resultArray);
};

extern DataBuffer sharedBuffer;

#endif /* DATAPACKETFORMAT_HPP */

