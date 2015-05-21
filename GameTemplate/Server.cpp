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
    // sleep for 1 second
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 0;
    nanosleep(&tim , &tim2);
}

void Server::receivedTcpMessage(std::string message, sf::TcpSocket *socket) {
    if(socket == nullptr) {
        // local client sent the message
    }
    else {
        // remote client sent the message
        if(message == "Give UDP Socket") {
            // give new client UDP port number
            std::string newMessage = "Server UDP Port\n"+std::to_string(getMyUdpPort());
            sendTcp(newMessage, socket);
        }
        else {
            
        }
    }
}

void Server::receivedUdpMessage(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient) {
}
