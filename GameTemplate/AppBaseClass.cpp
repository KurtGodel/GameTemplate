//
//  AppBaseClass.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "AppBaseClass.h"

AppBaseClass::AppBaseClass(ClientCommunicator &clientCommunicator) {
    communicator = &clientCommunicator;
}

AppBaseClass::~AppBaseClass() {
    //
}

void AppBaseClass::connectToServer(sf::IpAddress ipAddressOfServer, unsigned short tcpPortOfServer) {
    communicator->lock.lock();
    communicator->connectToServerIp.push_back(ipAddressOfServer);
    communicator->connectToServerTcpPort.push_back(tcpPortOfServer);
    communicator->lock.unlock();
}

void AppBaseClass::checkNetworkForMessages() {
    std::vector<std::string> messages;
    communicator->lock.lock();
    for(int i=0; i<communicator->tcpMessagesFromServer.size(); i++) {
        messages.push_back(communicator->tcpMessagesFromServer[i]);
    }
    communicator->tcpMessagesFromServer.clear();
    communicator->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        receivedTcpMessage(messages[i]);
    }
    messages.clear();
    
    
    communicator->lock.lock();
    for(int i=0; i<communicator->udpMessagesFromServer.size(); i++) {
        messages.push_back(communicator->udpMessagesFromServer[i]);
    }
    communicator->udpMessagesFromServer.clear();
    communicator->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        receivedUdpMessage(messages[i]);
    }
    messages.clear();
}

void AppBaseClass::sendUdp(std::string message) {
    communicator->lock.lock();
    communicator->udpMessagesToServer.push_back(message);
    communicator->lock.unlock();
}

void AppBaseClass::sendTcp(std::string message) {
    communicator->lock.lock();
    communicator->tcpMessagesToServer.push_back(message);
    communicator->lock.unlock();
}
