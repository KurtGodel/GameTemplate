//
//  TcpHandler.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/18/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__TcpHandler__
#define __GameTemplate__TcpHandler__

#include <stdio.h>

#include <stdio.h>
#include <iostream>
#include <list>
#include "TcpHandlerCommunicator.h"

class TcpHandler {
public:
    TcpHandler(TcpHandlerCommunicator &tcpHandlerCommunicator);
    ~TcpHandler();
    void run();
private:
    std::list<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    sf::TcpListener listener;
    TcpHandlerCommunicator *communicator;
    unsigned short tcpPort;
};


#endif /* defined(__GameTemplate__TcpHandler__) */
