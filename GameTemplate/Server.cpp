//
//  Server.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Server.h"

/*
Server::Server() {
}

Server::~Server() {
    udpSocket.unbind();
}

void Server::update() {
    if(interface->shouldServerBeRunning) {
        while(checkForUdpMessages()) {};
    }
}

bool Server::checkForUdpMessages() {
    if(udpSocket.receive(udpData, UDP_DATA_LENGTH, udpLengthReceived, udpAddress, udpPort) != sf::Socket::NotReady) {
        std::string messageFromClient = "";
        for(int i = 0; i < udpLengthReceived; i++) {
            messageFromClient += udpData[i];
        }
        processUdpMessage(messageFromClient, udpAddress, udpPort);
        return true;
    }
    return false;
}

void Server::sendUdpMessages(std::string message, sf::IpAddress address, unsigned int port) {
    char m[message.size()];
    for(int i = 0; i < message.size(); i++) {
        m[i] = message[i];
    }
    udpSocket.send(m, message.size(), address, port);
}
*/
