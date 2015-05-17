//
//  Server.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Server.h"

Server::Server(TcpMessageContainer &tcpMessageContainer) : ServerBaseClass(tcpMessageContainer) {
}

Server::~Server() {
}

void Server::update() {
    // DO STUFF HERE
    
    // sleep for 1 millisecond
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000;
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
}

void Server::receivedUdpMessage(std::string message, sf::IpAddress address, unsigned short port) {
}

void Server::receivedTcpMessage(std::string message, sf::TcpSocket *socket) {
}