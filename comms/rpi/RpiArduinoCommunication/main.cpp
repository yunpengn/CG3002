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
#include "DataHandler.hpp"
#include "ArduinoCommunication.hpp"
#include "MlCommunication.hpp"

using namespace std;

DataBuffer sharedBuffer(string(), 1000);

/*
 * 
 */
int main(int argc, char** argv) {
    initComms();
    init_mlCommunication();
    thread receiveThread (receiver);
    thread serverThread(serviceClient);
    sendChar('s');
    serverThread.join();
    signalStop();
    receiveThread.join();
    sendChar('q');
    return 0;
}

