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
#include "TcpMessageContainer.h"

class ClientBaseClass {
public:
    ClientBaseClass(TcpMessageContainer &tcpMessageContainer);
    ~ClientBaseClass();
    virtual std::string sendMeMessage(std::string message) = 0;
    void checkForReceivedSocketMessages();
protected:
    void sendUdpMessage(std::string message);
    void sendTcpMessage(std::string message);
    bool connectToServer(sf::IpAddress ipAdressOfServer, unsigned short udpPortOfServer, unsigned short tcpPortOfServer);
    virtual void receivedUdpMessage(std::string message) = 0;
    virtual void receivedTcpMessage(std::string message) = 0;
    unsigned short getServerTcpPort();
    unsigned short getServerUdpPort();
private:
    sf::IpAddress serverIP = "";
    unsigned short serverUdpPort = 0;
    
    sf::UdpSocket udpSocket;
    sf::TcpSocket tcpSocket;
    
    TcpMessageContainer *messageContainer;
};

#endif /* defined(__GameTemplate__ClientBaseClass__) */
