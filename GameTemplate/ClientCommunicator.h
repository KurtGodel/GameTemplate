//
//  ClientCommunicator.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ClientCommunicator__
#define __GameTemplate__ClientCommunicator__

#include <stdio.h>
#include <vector>
#include <mutex>
#include <SFML/Network.hpp>

struct ClientCommunicator {
    std::mutex lock;
    std::vector<std::string>tcpMessagesFromServer;
    std::vector<std::string>tcpMessagesToServer;
    std::vector<std::string>udpMessagesFromServer;
    std::vector<std::string>udpMessagesToServer;
    std::vector<sf::IpAddress>connectToServerIp;
    std::vector<unsigned short>connectToServerTcpPort;
    unsigned short tcpPortOfLocalServer = 0;
    
    std::vector<std::string>debug;
};

#endif /* defined(__GameTemplate__ClientCommunicator__) */
