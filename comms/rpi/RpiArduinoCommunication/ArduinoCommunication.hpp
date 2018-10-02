/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArduinoCommunication.hpp
 * Author: Ang Zhi Yuan
 *
 * Created on 20 September, 2018, 4:20 PM
 */

#ifndef ARDUINOCOMMUNICATION_HPP
#define ARDUINOCOMMUNICATION_HPP

#include "DataPacketUtilities.hpp"

void initComms();
int setupUart();
void receiver();
void sendChar(char c);
void signalStop();
void closeComms();

#endif /* ARDUINOCOMMUNICATION_HPP */

