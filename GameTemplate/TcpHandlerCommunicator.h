//
//  TcpHandlerCommunicator.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/18/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__TcpHandlerCommunicator__
#define __GameTemplate__TcpHandlerCommunicator__

#include <stdio.h>
#include <mutex>
#include <vector>
#include <SFML/Network.hpp>

struct TcpHandlerCommunicator {
    std::mutex lock;
    std::vector<std::string>messagesFromClients;
    std::vector<sf::TcpSocket*>socketsFromClients;
    unsigned short tcpPortOfLocalServer = 0;
};

#endif /* defined(__GameTemplate__TcpHandlerCommunicator__) */
