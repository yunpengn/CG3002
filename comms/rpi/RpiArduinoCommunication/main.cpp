/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Ang Zhi Yuan
 *
 * Created on 16 September, 2018, 5:14 PM
 */

#include <cstdlib>
#include <string.h>
#include <thread>
#include <cstdio>
#include "DataPacketUtilities.hpp"
#include "ArduinoCommunication.hpp"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    initComms();
    initUtils();
    std::thread receiveThread (receiver);
    sendChar('s');
    char dummyChar;
    scanf("%c", &dummyChar);
    signalStop();
    receiveThread.join();
    sendChar('q');
    //closeComms();
    closeFile();
    return 0;
}

