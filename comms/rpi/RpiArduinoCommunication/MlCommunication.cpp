///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
///* 
// * File:   MlCommunication.cpp
// * Author: Ang Zhi Yuan
// *
// * Created on 20 September, 2018, 2:27 PM
// */
//
//#include <cstdlib>
//using namespace std;
//
////
//// blocking_tcp_echo_server.cpp
//// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
////
//// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
////
//// Distributed under the Boost Software License, Version 1.0. (See accompanying
//// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
////
//
//#include <cstdlib>
//#include <iostream>
//#include <boost/bind.hpp>
//#include <boost/smart_ptr.hpp>
//#include <boost/asio.hpp>
//#include <boost/thread/thread.hpp>
//#include "DataPacketUtilities.hpp"
//
//using boost::asio::ip::tcp;
//
//const int max_length = 1;
//
//typedef boost::shared_ptr<tcp::socket> socket_ptr;
//
//int getMlData(char * dataBuffer) {
//    return 0;
//}
//
//void session(socket_ptr sock) {
//    try {
//        while (1) {
//            char rx_data[max_length];
//
//            boost::system::error_code error;
//            size_t length = sock->read_some(boost::asio::buffer(rx_data), error);
//            if (error == boost::asio::error::eof)
//                break; // Connection closed cleanly by peer.
//            else if (error)
//                throw boost::system::system_error(error); // Some other error.
//
//            char tx_data[1024];
//            int dataLength = 0;
//            switch(rx_data[0]) {
//                case 'd':
//                    dataLength = getMlData(tx_data);
//                    break;
//            }
//            boost::asio::write(*sock, boost::asio::buffer(tx_data, length));
//        }
//    } catch (std::exception& e) {
//        std::cerr << "Exception in thread: " << e.what() << "\n";
//    }
//}
//
//void server(boost::asio::io_service& io_service, short port) {
//    tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
//    for (;;) {
//        socket_ptr sock(new tcp::socket(io_service));
//        a.accept(*sock);
//        boost::thread t(boost::bind(session, sock));
//    }
//}
//
//int main(int argc, char* argv[]) {
//    try {
//        if (argc != 2) {
//            std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
//            return 1;
//        }
//
//        boost::asio::io_service io_service;
//
//        using namespace std; // For atoi.
//        server(io_service, atoi(argv[1]));
//    } catch (std::exception& e) {
//        std::cerr << "Exception: " << e.what() << "\n";
//    }
//
//    return 0;
//}
//