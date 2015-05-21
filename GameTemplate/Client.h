//
//  Client.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__Client__
#define __GameTemplate__Client__

#include <stdio.h>
#include <iostream>
#include <sstream>
#include "ClientCommunicator.h"
#include "ClientServerCommunicator.h"

class Client {
public:
    Client(ClientServerCommunicator &clientServerCommunicator, ClientCommunicator &clientCommunicator);
    ~Client();
    void run();
private:
    bool connectTcpToServer(sf::IpAddress serverIpAddress, unsigned short serverPort);
    void sendTcpMessage(std::string message);
    void sendUdpMessage(std::string message);
    std::vector<std::string> split(const std::string s, char delim);
    
    ClientCommunicator *app;
    ClientServerCommunicator *server;
    
    sf::TcpSocket tcpSocket;
    sf::UdpSocket udpSocket;
    
    sf::IpAddress ipAddressOfServer = "0.0.0.0";
    unsigned short tcpPortOfServer = 0;
    unsigned short udpPortOfServer = 0;
};

#endif /* defined(__GameTemplate__Client__) */
