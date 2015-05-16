//
//  ClientBaseClass.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ClientBaseClass.h"

/*
 Example Implementation
 
 // Before you do this, you must initalize the derived class
 connectToServer("137.22.169.68");
 sendUdpMessage("Hi! I'm the client.");
 checkForReceivedSocketMessages();
*/

ClientBaseClass::ClientBaseClass() :udpSocket() {
    udpSocket.setBlocking(false);
}

ClientBaseClass::~ClientBaseClass() {
    udpSocket.unbind();
}

void ClientBaseClass::connectToServer(sf::IpAddress ipAdressOfServer, unsigned short portOfClient, unsigned short portOfServer) {
    serverIP = ipAdressOfServer;
    serverPort = portOfServer;
    clientPort = portOfClient;
    udpSocket.bind(clientPort);
}

void ClientBaseClass::sendUdpMessage(std::string message) {
    if(serverIP != "" && serverPort != 0 && clientPort != 0) {
        udpSocket.send(message.c_str(), message.length(), serverIP, serverPort);
    }
}

void ClientBaseClass::checkForReceivedSocketMessages() {
    // check UDP socket
    if(serverIP != "" && serverPort != 0 && clientPort != 0) {
        char udpBuffer[1024];
        std::size_t udpReceived = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(udpBuffer, sizeof(udpBuffer), udpReceived, sender, port);
        std::string str(udpBuffer);
        receivedUdpMessage(str);
    }
}
