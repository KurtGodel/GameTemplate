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

ClientBaseClass::ClientBaseClass(TcpMessageContainer &tcpMessageContainer) :udpSocket() {
    messageContainer = &tcpMessageContainer;
    udpSocket.setBlocking(false);
    tcpSocket.setBlocking(false);
}

ClientBaseClass::~ClientBaseClass() {
    udpSocket.unbind();
}

bool ClientBaseClass::connectToServer(sf::IpAddress ipAdressOfServer, unsigned short udpPortOfServer, unsigned short tcpPortOfServer) {
    std::cout << "<" << ipAdressOfServer << ":" << udpPortOfServer << ":" << tcpPortOfServer << ">";
    
    serverIP = ipAdressOfServer;
    if(udpPortOfServer == 0) {
        serverUdpPort = messageContainer->serverUdpPort;
    }
    else {
        serverUdpPort = udpPortOfServer;
    }
    udpSocket.unbind();
    udpSocket.bind(sf::Socket::AnyPort);
    
    tcpSocket.disconnect();
    sf::Socket::Status status = tcpSocket.connect(ipAdressOfServer, tcpPortOfServer);
    
    // wait for the sockets to connect
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000;
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
    
    sendTcpMessage("New Client");
    sendUdpMessage("New Client");
    
    return true;
}

void ClientBaseClass::sendUdpMessage(std::string message) {
    if(serverIP != "" && serverUdpPort != 0) {
        udpSocket.send(message.c_str(), message.length(), serverIP, serverUdpPort);
    }
}

void ClientBaseClass::sendTcpMessage(std::string message) {
    if(serverIP != "" && serverUdpPort != 0) {
        tcpSocket.send(message.c_str(), message.length());
    }
}

void ClientBaseClass::checkForReceivedSocketMessages() {
    if(serverIP != "" && serverUdpPort != 0) {
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

unsigned short ClientBaseClass::getServerTcpPort() {
    return messageContainer->serverPort;
}

unsigned short ClientBaseClass::getServerUdpPort() {
    return messageContainer->serverUdpPort;
}