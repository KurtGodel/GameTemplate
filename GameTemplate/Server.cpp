//
//  Server.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Server.h"

/*
 Just remember to initalize the ServerBaseClass
*/
Server::Server(TcpMessageContainer &tcpMessageContainer) : ServerBaseClass(tcpMessageContainer) {
}

/*
 This function is called almost immediatley after it completes, so make sure to sleep some time to prevent 100% CPU usage.
*/
void Server::update() {
    // sleep for 1 millisecond
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000000;
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
}

/*
 This method is called every time the server receives a UDP message from a client. This is the only way to get a client's port. Besides receivedTcpMessage(), this is the onlyw ay to get a client's IP address.
*/
void Server::receivedUdpMessage(std::string message, sf::IpAddress address, unsigned short port) {
    std::cout << "SR{UDP:" << message << "}\n";
}

/*
 This method is called every time the server receives a TCP message from a client. This is the only way to get a client's socket. Besides receivedUdpMessages(), this is the only way to get a client's IP address.
*/
void Server::receivedTcpMessage(std::string message, sf::TcpSocket *socket) {
    std::cout << "SR{TCP:" << message << "}\n";
}