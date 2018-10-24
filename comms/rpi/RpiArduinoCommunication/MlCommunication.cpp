/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MlCommunication.cpp
 * Author: Ang Zhi Yuan
 *
 * Created on 20 September, 2018, 2:27 PM
 */

#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <chrono>
#include "DataHandler.hpp"

const int max_length = 1;

using namespace std;

int serverSocket;

void init_mlCommunication() {
    sockaddr_in server;
     
    //Create socket
    serverSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (serverSocket == -1)
    {
        cerr << "Could not create socket" << endl;
        exit(-1);
    }
    printf("Socket created\n");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 3002 );
     
    //Bind
    if( bind(serverSocket,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        cerr << "bind failed. Error" << endl;
        exit(1);
    }
    printf("Bind done\n");
     
    //Listen
    listen(serverSocket , 3);
}

void logToFile(float * valueArray, int numValues) {
    static FILE * debugFp = fopen("sent_data.csv", "w");
    using namespace std::chrono;
    long currTimeMillis =  duration_cast<milliseconds>(steady_clock::now() - sharedBuffer.startTime).count();
    if (numValues<1)
        return;
    fprintf(debugFp, "%ld", currTimeMillis);
    for (int i=0; i<numValues; i++) {
        fprintf(debugFp, ",%f", valueArray[i]);
    }
    fprintf(debugFp, "\n");
}

void serviceClient() {
    printf("Waiting for incoming connections... \n");
     
    //accept connection from an incoming client
    sockaddr_in clientAddr;
    int clienAddrLen;
    int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, (socklen_t*)&clienAddrLen);
    if (clientSocket < 0) {
        cerr << "Accept failed" << endl;
        exit(1);
    }
    printf("Connection accepted\n");
    char command;
    int receivedSize = recv(clientSocket, &command, 1, 0);
    while(receivedSize > 0) {
        if (command=='m') {
            float dataToSend[60];
            //cout<< "Received request, collecting data... ";
            sharedBuffer.getMeanVariance(dataToSend);
            sharedBuffer.getMaxMin(dataToSend+30);
            //cout<< "Data collected! Sending... ";
            send(clientSocket, dataToSend, sizeof(dataToSend), 0);
            logToFile(dataToSend, 60);
            //cout << "Data sent!" <<endl;
        } else if (command=='p') {
            float dataToSend[3];
            sharedBuffer.getPowerData(dataToSend);
            send(clientSocket, dataToSend, sizeof(dataToSend), 0);
            printf("Sent energy: %f, voltage: %f, current: %f\n", dataToSend[0],
                    dataToSend[1], dataToSend[2]);
        }
        else {
             cout << "Invalid command received: " << command << endl;
        }
        receivedSize = recv(clientSocket, &command, 1, 0);
    }
    
}


