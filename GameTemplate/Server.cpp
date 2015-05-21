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
    // sleep for 100 milliseconds
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
}

void Server::receivedTcpMessage(std::string message, sf::TcpSocket *socket) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() == 0) {
        return;
    }
    if(socket == nullptr) {
        // local client sent the message
        if(arr[0] == "Chat Message" && arr.size() == 2) {
            chatMessages.push_back("Server: " + arr[1]);
            sendTcpMessageToAllClients("CHAT MESSAGE\n"+chatMessages[chatMessages.size()-1]);
        }
    }
    else {
        // remote client sent the message
        if(arr[0] == "Give UDP Socket" && arr.size() == 2) {
            // give new client UDP port number
            if(isUsernameUnique(arr[1])) {
                // username is unique; send UDP port back
                tableOfClientsByUsername[arr[1]] = socket;
                tableOfClientsBySocket[socket] = arr[1];
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
            if(arr[0] == "Chat Message" && arr.size() == 2) {
                chatMessages.push_back(tableOfClientsBySocket[socket] + ": " + arr[1]);
                sendTcpMessageToAllClients("CHAT MESSAGE\n"+chatMessages[chatMessages.size()-1]);
            }
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
    sf::TcpSocket *quail = tableOfClientsByUsername[name];
    if(quail == nullptr) {
        if(name == "Server") {
            return false;
        }
        else {
            return true;
        }
    }
    else {
        return false;
    }
}

void Server::sendTcpMessageToAllClients(std::string message) {
    typedef std::map<std::string, sf::TcpSocket*>::iterator it_type;
    for(it_type iterator = tableOfClientsByUsername.begin(); iterator != tableOfClientsByUsername.end(); iterator++) {
        // iterate through clients and send message
        sendTcp(message, iterator->second);
    }
    sendTcp(message, nullptr);
}
