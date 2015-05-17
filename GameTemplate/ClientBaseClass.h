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
    virtual void sendMeMessage(std::string message) = 0;
    void checkForReceivedSocketMessages();
protected:
    void sendUdpMessage(std::string message);
    bool connectToServer(sf::IpAddress ipAdressOfServer, unsigned short udpPortOfClient, unsigned short udpPortOfServer, unsigned short tcpPortOfServer);
    virtual void receivedUdpMessage(std::string message) = 0;
    virtual void receivedTcpMessage(std::string message) = 0;
private:
    sf::IpAddress serverIP = "";
    unsigned short clientUdpPort = 0;
    unsigned short serverUdpPort = 0;
    
    sf::UdpSocket udpSocket;
    sf::TcpSocket tcpSocket;
};

#endif /* defined(__GameTemplate__ClientBaseClass__) */
