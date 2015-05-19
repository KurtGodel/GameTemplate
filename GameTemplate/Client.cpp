//
//  Client.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Client.h"

Client::Client(ClientServerCommunicator &clientServerCommunicator, ClientCommunicator &clientCommunicator) {
    app = &clientCommunicator;
    server = &clientServerCommunicator;
    tcpSocket.setBlocking(false);
    udpSocket.setBlocking(false);
    udpSocket.bind(sf::Socket::AnyPort);
}

Client::~Client() {
    udpSocket.unbind();
    tcpSocket.disconnect();
}

void Client::run() {
    // check connect requests
    app->lock.lock();
    if(app->connectToServerIp.size() > 0 && app->connectToServerTcpPort.size() > 0) {
        sf::IpAddress addr = app->connectToServerIp[app->connectToServerIp.size()-1];
        unsigned short port = app->connectToServerTcpPort[app->connectToServerTcpPort.size()-1];
        app->lock.unlock();
        connectTcpToServer(addr, port);
    }
    else {
        app->lock.unlock();
    }
    
    // send udp messges to server
    std::vector<std::string> messages;
    app->lock.lock();
    for(int i=0; i<app->udpMessagesToServer.size(); i++) {
        messages.push_back(app->udpMessagesToServer[i]);
    }
    app->udpMessagesToServer.clear();
    app->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        sendUdpMessage(messages[i]);
    }
    messages.clear();
    
    // send tcp messges to server
    app->lock.lock();
    for(int i=0; i<app->tcpMessagesToServer.size(); i++) {
        messages.push_back(app->tcpMessagesToServer[i]);
    }
    app->tcpMessagesToServer.clear();
    app->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        sendTcpMessage(messages[i]);
    }
    messages.clear();
    
    // check for udp messages from local "server"
    server->lock.lock();
    for(int i=0; i<server->udpMessagesFromServer.size(); i++) {
        messages.push_back(server->udpMessagesFromServer[i]);
    }
    server->lock.unlock();
    app->lock.lock();
    for(int i=0; i<messages.size(); i++) {
        app->udpMessagesFromServer.push_back(messages[i]);
    }
    server->udpMessagesFromServer.clear();
    app->lock.unlock();
    messages.clear();
    
    // check for tcp messages from local "server"
    server->lock.lock();
    for(int i=0; i<server->tcpMessagesFromServer.size(); i++) {
        messages.push_back(server->tcpMessagesFromServer[i]);
    }
    server->tcpMessagesFromServer.clear();
    server->lock.unlock();
    app->lock.lock();
    for(int i=0; i<messages.size(); i++) {
        app->tcpMessagesFromServer.push_back(messages[i]);
    }
    app->lock.unlock();
    messages.clear();
    
    // check udp messages from remote server
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
        app->lock.lock();
        app->udpMessagesFromServer.push_back(message);
        app->lock.unlock();
    }
    
    
    // check tcp messages from remote server
    begin = buffer;
    end = begin + sizeof(buffer);
    std::fill(begin, end, 0);
    tcpSocket.receive(buffer, sizeof(buffer), received);
    message = std::string(buffer);
    if(message != "") {
        app->lock.lock();
        app->tcpMessagesFromServer.push_back(message);
        app->lock.unlock();
    }
    
    
    // sleep for 1 second
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 0;
    nanosleep(&tim , &tim2);
}

bool Client::connectTcpToServer(sf::IpAddress ipAddressOfServer, unsigned short portOfServer) {
    ipAddressOfServer = "0.0.0.0";
    tcpPortOfServer = 0;
    udpPortOfServer = 0;
    if(ipAddressOfServer == "0.0.0.0" || portOfServer == 0) {
        // connect to local "server"
        // i.e. do nothing after setting the above values to 0
    }
    else {
        // connect to remote server
        tcpSocket.setBlocking(true);
        tcpSocket.disconnect();
        sf::Socket::Status status = tcpSocket.connect(ipAddressOfServer, portOfServer);
        tcpSocket.setBlocking(false);
        if(status == sf::Socket::Status::Done) {
            // we have successfuly connected to the server
            ipAddressOfServer = tcpSocket.getRemoteAddress();
            tcpPortOfServer = tcpSocket.getRemotePort();
            return true;
        }
        else {
            // a problem occured - abandoning disconnect
            return false;
        }
    }
}

void Client::sendTcpMessage(std::string message) {
    if(tcpPortOfServer == 0 || ipAddressOfServer == "0.0.0.0") {
        // send message to local "server"
        server->lock.lock();
        server->tcpMessagesToServer.push_back(message);
        server->lock.unlock();
    }
    else {
        tcpSocket.send(message.c_str(), message.size());
    }
}

void Client::sendUdpMessage(std::string message) {
    if(tcpPortOfServer == 0 || ipAddressOfServer == "0.0.0.0") {
        // send message to local "server"
        server->lock.lock();
        server->udpMessagesToServer.push_back(message);
        server->lock.unlock();
    }
    else {
        // send message to remote server
        if(udpPortOfServer == 0) {
            // we don't know the server port
            std::string newMessage = "Give UPD Socket";
            tcpSocket.send(newMessage.c_str(), newMessage.size());
        }
        else {
            // we do know the server port
            udpSocket.send(message.c_str(), message.size(), ipAddressOfServer, udpPortOfServer);
        }
    }
}
