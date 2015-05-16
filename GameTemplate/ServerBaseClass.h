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
#include <unordered_map>
#include <SFML/Network.hpp>


class ServerBaseClass {
public:
    ServerBaseClass();
    ~ServerBaseClass();
    void baseClassUpdate();
    
protected:
    virtual void update() = 0;
    virtual void receivedUdpMessage(std::string& message, sf::IpAddress address, unsigned short port) = 0;
    void sendUdpMessage(std::string message, sf::IpAddress address, unsigned int port);
    
private:
    void checkForUdpMessages();
    
    sf::UdpSocket udpSocket;
    unsigned short udpPort;
};

#endif /* defined(__GameTemplate__ServerBaseClass__) */
