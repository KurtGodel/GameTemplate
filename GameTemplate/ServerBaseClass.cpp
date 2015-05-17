//
//  ServerBaseClass.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/16/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerBaseClass.h"

ServerBaseClass::ServerBaseClass(TcpMessageContainer &tcpMessageContainer) {
    messageContainer = &tcpMessageContainer;
    serverUdpPort = 55002;
    udpSocket.bind(serverUdpPort);
    udpSocket.setBlocking(false);
}

ServerBaseClass::~ServerBaseClass() {
    udpSocket.unbind();
}

bool ServerBaseClass::baseClassUpdate() {
    bool shouldStop = checkForMessages();
    if(shouldStop) {
        return true;
    }
    update();
    return false;
}

bool ServerBaseClass::checkForMessages() {
    if(messageContainer->startClosing > 0) {
        messageContainer->startClosing++;
        return true;
    }
    
    // check udp socket for messages
    char buffer[1024];
    char *begin = buffer;
    char *end = begin + sizeof(buffer);
    std::fill(begin, end, 0);
    std::size_t received = 0;
    sf::IpAddress sender;
    unsigned short port;
    udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
    std::string message(buffer);
    if(message != "") {
        receivedUdpMessage(message, sender, port);
    }
    
    // check tcp socket for message
    std::vector<std::string> messagesToProcess;
    std::vector<sf::TcpSocket*> socketsToProcess;
    messageContainer->lock.lock();
    if(messageContainer->messagesFromClients.size() > 0) {
        while(messageContainer->messagesFromClients.size() > 0) {
            messagesToProcess.push_back(messageContainer->messagesFromClients[0]);
            messageContainer->messagesFromClients.erase(messageContainer->messagesFromClients.begin(), messageContainer->messagesFromClients.begin()+1);
            socketsToProcess.push_back(messageContainer->socketsFromClients[0]);
            messageContainer->socketsFromClients.erase(messageContainer->socketsFromClients.begin(), messageContainer->socketsFromClients.begin()+1);
        }
    }
    messageContainer->lock.unlock();
    for(int i=0; i<messagesToProcess.size(); i++) {
        receivedTcpMessage(messagesToProcess[i], socketsToProcess[i]);
    }
    return false;
}

void ServerBaseClass::sendUdpMessage(std::string message, sf::IpAddress address, unsigned int port) {
    char m[message.size()];
    for(int i = 0; i < message.size(); i++) {
        m[i] = message[i];
    }
    udpSocket.send(m, message.size(), address, port);
}

void ServerBaseClass::sendTcpMessage(std::string message, sf::TcpSocket *socket) {
    char m[message.size()];
    for(int i = 0; i < message.size(); i++) {
        m[i] = message[i];
    }
    socket->send(m, message.size());
}

