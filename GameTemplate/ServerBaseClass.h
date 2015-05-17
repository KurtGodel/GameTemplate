//
//  ServerBaseClass.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/16/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ServerBaseClass__
#define __GameTemplate__ServerBaseClass__

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <list>
#include <unordered_map>
#include <SFML/Network.hpp>
#include "TcpMessageContainer.h"

class ServerBaseClass {
public:
    ServerBaseClass(TcpMessageContainer &tcpMessageContainer);
    ~ServerBaseClass();
    bool baseClassUpdate();
    
protected:
    virtual void update() = 0;
    virtual void receivedUdpMessage(std::string message, sf::IpAddress address, unsigned short port) = 0;
    virtual void receivedTcpMessage(std::string message, sf::TcpSocket *socket) = 0;
    void sendUdpMessage(std::string message, sf::IpAddress address, unsigned int port);
    void sendTcpMessage(std::string message, sf::TcpSocket *socket);
private:
    bool checkForMessages();
    unsigned short serverUdpPort;
    sf::UdpSocket udpSocket;
    TcpMessageContainer *messageContainer;
};

#endif /* defined(__GameTemplate__ServerBaseClass__) */
