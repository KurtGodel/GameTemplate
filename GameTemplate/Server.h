//
//  Server.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__Server__
#define __GameTemplate__Server__

#include <stdio.h>
#include <sstream>
#include <iostream>
#include "ServerBaseClass.h"

class Server : public ServerBaseClass {
public:
    Server(TcpHandlerCommunicator &tcpHandlerCommunicator, ClientServerCommunicator &clientServerCommunicator);
    ~Server();
    void run();
protected:
    void receivedTcpMessage(std::string message, sf::TcpSocket *socket);
    void receivedUdpMessage(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient);
private:
    std::vector<std::string> chatMessages;
    std::vector<std::string> split(const std::string s, char delim);
    bool isUsernameUnique(std::string name);
    std::map<std::string, sf::TcpSocket*> tableOfClientsByUsername;
    std::map<sf::TcpSocket*, std::string> tableOfClientsBySocket;
    
    void sendTcpMessageToAllClients(std::string message);
};

#endif /* defined(__GameTemplate__Server__) */
