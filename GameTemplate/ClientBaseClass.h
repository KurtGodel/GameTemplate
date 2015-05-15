//
//  ClientBaseClass.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ClientBaseClass__
#define __GameTemplate__ClientBaseClass__

#include <stdio.h>
#include <string>
#include <iostream>
#include <SFML/Network.hpp>

class ClientBaseClass {
public:
    ClientBaseClass();
    ~ClientBaseClass();
    void connectToServer(sf::IpAddress addressOfServer, unsigned short portOfServer);
    void sendUdpMessage(std::string message);
    void sendTcpMessage(std::string message);
    void checkForReceivedSocketMessages();
    virtual void receivedUdpMessage(std::string message) = 0;
    virtual void receivedTcpMessage(std::string message) = 0;
    virtual void sendClientMessage(std::string message) = 0;
private:
    sf::IpAddress serverAddress = "";
    unsigned short serverPort = 0;
    sf::UdpSocket udpSocket;
    sf::TcpSocket tcpSocket;
};

#endif /* defined(__GameTemplate__ClientBaseClass__) */
