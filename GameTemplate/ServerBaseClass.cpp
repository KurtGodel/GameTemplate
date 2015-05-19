//
//  ServerBaseClass.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerBaseClass.h"

ServerBaseClass::ServerBaseClass(TcpHandlerCommunicator &tcpHandlerCommunicator, ClientServerCommunicator &clientServerCommunicator) {
    tcpHandler = &tcpHandlerCommunicator;
    client = &clientServerCommunicator;
    udpSocket.bind(sf::Socket::AnyPort);
    udpSocket.setBlocking(false);
}

ServerBaseClass::~ServerBaseClass() {
}

void ServerBaseClass::checkNetworkForMessages() {
    // check for TCP messages from local client
    std::vector<std::string> messages;
    client->lock.lock();
    for(int i=0; i<client->tcpMessagesToServer.size(); i++) {
        messages.push_back(client->tcpMessagesToServer[i]);
    }
    client->tcpMessagesToServer.clear();
    client->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        receivedTcpMessage(messages[i], nullptr);
    }
    messages.clear();
    
    // check for TCP messages from remote clients
    std::vector<sf::TcpSocket*> sockets;
    tcpHandler->lock.lock();
    for(int i=0; i<tcpHandler->messagesFromClients.size(); i++) {
        messages.push_back(tcpHandler->messagesFromClients[i]);
        sockets.push_back(tcpHandler->socketsFromClients[i]);
    }
    tcpHandler->messagesFromClients.clear();
    tcpHandler->socketsFromClients.clear();
    tcpHandler->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        receivedTcpMessage(messages[i], sockets[i]);
    }
    messages.clear();
    
    // check for UDP messages from local client
    client->lock.lock();
    for(int i=0; i<client->udpMessagesToServer.size(); i++) {
        messages.push_back(client->udpMessagesToServer[i]);
    }
    client->udpMessagesToServer.clear();
    client->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        receivedUdpMessage(messages[i], "0.0.0.0", 0);
    }
    messages.clear();
    
    // check for UDP messages from remote clients
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
}

void ServerBaseClass::sendTcp(std::string message, sf::TcpSocket *socket) {
    if(socket == nullptr) {
        // send TCP message to local client
        client->lock.lock();
        client->tcpMessagesFromServer.push_back(message);
        client->lock.unlock();
    }
    else {
        // send TCP message remote client
        socket->send(message.c_str(), message.size());
    }
}

void ServerBaseClass::sendUdp(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient) {
    if(ipAddressOfClient == "0.0.0.0" || ipAddressOfClient == sf::IpAddress::getLocalAddress()) {
        // send UDP message to local client
        client->lock.lock();
        client->udpMessagesFromServer.push_back(message);
        client->lock.unlock();
    }
    else {
        // send UDP message to remote client
        udpSocket.send(message.c_str(), message.size(), ipAddressOfClient, portOfClient);
    }
}
