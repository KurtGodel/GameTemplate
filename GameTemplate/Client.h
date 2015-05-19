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
#include "ClientCommunicator.h"
#include "ClientServerCommunicator.h"

class Client {
public:
    Client(ClientServerCommunicator &clientServerCommunicator, ClientCommunicator &clientCommunicator);
    ~Client();
    void run();
private:
    bool connectTcpToServer(sf::IpAddress ipAddressOfServer, unsigned short portOfServer);
    void sendTcpMessage(std::string message);
    void sendUdpMessage(std::string message);
    
    ClientCommunicator *app;
    ClientServerCommunicator *server;
    
    sf::TcpSocket tcpSocket;
    sf::UdpSocket udpSocket;
    
    sf::IpAddress ipAddressOfServer = "0.0.0.0";
    unsigned short tcpPortOfServer = 0;
    unsigned short udpPortOfServer = 0;
};

#endif /* defined(__GameTemplate__Client__) */
