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
    tcpSocket.setBlocking(false);
}

ClientBaseClass::~ClientBaseClass() {
    udpSocket.unbind();
}

bool ClientBaseClass::connectToServer(sf::IpAddress ipAdressOfServer, unsigned short udpPortOfClient, unsigned short udpPortOfServer, unsigned short tcpPortOfServer) {
    serverIP = ipAdressOfServer;
    serverUdpPort = udpPortOfServer;
    clientUdpPort = udpPortOfClient;
    udpSocket.bind(clientUdpPort);
    
    tcpSocket.connect(ipAdressOfServer, tcpPortOfServer);
    
    return true;
}

void ClientBaseClass::sendUdpMessage(std::string message) {
    if(serverIP != "" && serverUdpPort != 0 && clientUdpPort != 0) {
        udpSocket.send(message.c_str(), message.length(), serverIP, serverUdpPort);
    }
}

void ClientBaseClass::checkForReceivedSocketMessages() {
    if(serverIP != "" && serverUdpPort != 0 && clientUdpPort != 0) {
        // check UDP socket
        char udpBuffer[1024];
        std::size_t udpReceived = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(udpBuffer, sizeof(udpBuffer), udpReceived, sender, port);
        std::string udpMessage(udpBuffer);
        if(udpMessage != "") {
            receivedUdpMessage(udpMessage);
        }
        
        // check for TCP socket
        char buffer[1024];
        std::size_t received = 0;
        tcpSocket.receive(buffer, sizeof(buffer), received);
        std::string tcpMessage(buffer);
        receivedTcpMessage(tcpMessage);
    }
}
