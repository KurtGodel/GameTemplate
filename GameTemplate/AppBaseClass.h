//
//  AppBaseClass.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__AppBaseClass__
#define __GameTemplate__AppBaseClass__

#include <stdio.h>
#include <string>
#include <iostream>
#include "ClientCommunicator.h"

class AppBaseClass {
public:
    AppBaseClass(ClientCommunicator &clientCommunicator);
    ~AppBaseClass();
    void checkNetworkForMessages();
    void sendUdp(std::string message);
    void sendTcp(std::string message);
    virtual std::string sendMeMessage(std::string message) = 0;
protected:
    void connectToServer(std::string username, sf::IpAddress ipAddressOfServer, unsigned short tcpPortOfServer);
    virtual void receivedTcpMessage(std::string message) = 0;
    virtual void receivedUdpMessage(std::string message) = 0;
    unsigned short getUdpPort();
    virtual void think() = 0;
    virtual void draw() = 0;
    unsigned short getTcpPortOfLocalServer();
private:
    ClientCommunicator *communicator;
};

#endif /* defined(__GameTemplate__AppBaseClass__) */
