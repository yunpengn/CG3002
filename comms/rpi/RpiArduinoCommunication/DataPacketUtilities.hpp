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

struct DataPacket{
    float voltage;
    float current;
    float bodyX, bodyY, bodyZ;
    float handAcclX, handAcclY, handAcclZ;
    float handGyroX, handGyroY, handGyroZ;
    float legAcclX, legAcclY, legAcclZ;
    float legGyroX, legGyroY, legGyroZ;
};

struct DataBuffer{
    DataPacket ** dataPacketPtrArray;
    int bufferSize;
    int startIndex;
    int endIndex; //exclusive of last packet
};

void addPacket(DataBuffer * buffer, DataPacket * packet);
void closeFile();
void initUtils();

#endif /* DATAPACKETFORMAT_HPP */

