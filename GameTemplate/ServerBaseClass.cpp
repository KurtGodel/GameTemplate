//
//  ServerBaseClass.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/16/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerBaseClass.h"

ServerBaseClass::ServerBaseClass() {
    udpPort = 55002;
    udpSocket.bind(udpPort);
    udpSocket.setBlocking(false);
}

ServerBaseClass::~ServerBaseClass() {
    udpSocket.unbind();
}

void ServerBaseClass::baseClassUpdate() {
    checkForUdpMessages();
    update();
}

void ServerBaseClass::checkForUdpMessages() {
    char buffer[1024];
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
    std::string message(buffer);
    if(message != "") {
        receivedUdpMessage(message, sender, port);
    }
}

void ServerBaseClass::sendUdpMessage(std::string message, sf::IpAddress address, unsigned int port) {
    char m[message.size()];
    for(int i = 0; i < message.size(); i++) {
        m[i] = message[i];
    }
    udpSocket.send(m, message.size(), address, port);
}
