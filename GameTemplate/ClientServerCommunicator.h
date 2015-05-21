//
//  ClientServerCommunicator.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ClientServerCommunicator__
#define __GameTemplate__ClientServerCommunicator__

#include <stdio.h>
#include <mutex>
#include <vector>
#include <string>

struct ClientServerCommunicator {
    std::mutex lock;
    std::vector<std::string>tcpMessagesFromServer;
    std::vector<std::string>tcpMessagesToServer;
    std::vector<std::string>udpMessagesFromServer;
    std::vector<std::string>udpMessagesToServer;
    unsigned short tcpPortOfLocalServer = 0;
    
    std::vector<std::string>debug;
};

#endif /* defined(__GameTemplate__ClientServerCommunicator__) */
