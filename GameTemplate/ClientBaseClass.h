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
    void connectToServer(sf::IpAddress ipAdressOfServer, unsigned short portOfClient, unsigned short portOfServer);
    virtual void receivedUdpMessage(std::string message) = 0;
private:
    sf::IpAddress serverIP = "";
    unsigned short clientPort = 0;
    unsigned short serverPort = 0;
    sf::UdpSocket udpSocket;
};

#endif /* defined(__GameTemplate__ClientBaseClass__) */
