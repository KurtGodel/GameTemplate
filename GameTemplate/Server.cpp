//
//  Server.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Server.h"

Server::Server(TcpHandlerCommunicator &tcpHandlerCommunicator, ClientServerCommunicator &clientServerCommunicator) : ServerBaseClass(tcpHandlerCommunicator, clientServerCommunicator) {
}

Server::~Server() {
}

void Server::run() {
    // sleep for 1 millisecond
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 1000000;
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
}

void Server::receivedTcpMessage(std::string message, sf::TcpSocket *socket) {
}

void Server::receivedUdpMessage(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient) {
}
