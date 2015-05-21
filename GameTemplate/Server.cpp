//
//  Server.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Server.h"

Server::Server(TcpHandlerCommunicator &tcpHandlerCommunicator, ClientServerCommunicator &clientServerCommunicator) : ServerBaseClass(tcpHandlerCommunicator, clientServerCommunicator) {
}

Server::~Server() {
}

void Server::run() {
    // sleep for 1 second
    struct timespec tim, tim2;
    tim.tv_sec = 1;
    tim.tv_nsec = 0;
    nanosleep(&tim , &tim2);
}

void Server::receivedTcpMessage(std::string message, sf::TcpSocket *socket) {
    if(socket == nullptr) {
        // local client sent the message
    }
    else {
        // remote client sent the message
        std::vector<std::string> arr = split(message, '\n');
        if(arr.size() == 0) {
            return;
        }
        if(arr.size() == 2 && arr[0] == "Give UDP Socket") {
            // give new client UDP port number
            if(isUsernameUnique(arr[1])) {
                // username is unique; send UDP port back
                std::string newMessage = "Server UDP Port\n"+std::to_string(getMyUdpPort());
                sendTcp(newMessage, socket);
            }
            else {
                // username is a duplicate; send this message back and refuse to give the client the UDP port #
                std::string newMessage = "Username Not Unique";
                sendTcp(newMessage, socket);
            }
        }
        else {
            // its a normal TCP message
        }
    }
}

void Server::receivedUdpMessage(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient) {
}

std::vector<std::string> Server::split(const std::string s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool Server::isUsernameUnique(std::string name) {
    return true;
}