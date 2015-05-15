//
//  ClientBaseClass.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ClientBaseClass.h"

ClientBaseClass::ClientBaseClass() :udpSocket() {
    tcpSocket.setBlocking(false);
    udpSocket.setBlocking(false);
    connectToServer("137.22.169.68", 6670);
}

ClientBaseClass::~ClientBaseClass() {
    udpSocket.unbind();
}

void ClientBaseClass::sendUdpMessage(std::string message) {
    udpSocket.send(message.c_str(), message.length(), serverAddress, serverPort);
}

void ClientBaseClass::sendTcpMessage(std::string message) {
    tcpSocket.send(message.c_str(), message.size() + 1);
}

void ClientBaseClass::checkForReceivedSocketMessages() {
    // check TCP socket
    char tcpBuffer[1024];
    std::size_t tcpReceived = 0;
    tcpSocket.receive(tcpBuffer, sizeof(tcpBuffer), tcpReceived);
    std::cout << "The server said: " << tcpBuffer << std::endl;
    
    // check UDP socket
    char udpBuffer[1024];
    std::size_t udpReceived = 0;
    sf::IpAddress sender;
    unsigned short port;
    udpSocket.receive(udpBuffer, sizeof(udpBuffer), udpReceived, sender, port);
    std::cout << sender.toString() << " said: " << udpBuffer << std::endl;
}

void ClientBaseClass::connectToServer(sf::IpAddress addressOfServer, unsigned short portOfServer) {
    serverAddress = addressOfServer;
    serverPort = portOfServer;
    tcpSocket.connect(serverAddress, portOfServer);
    sendTcpMessage("alpha");
    sendUdpMessage("beta");
}