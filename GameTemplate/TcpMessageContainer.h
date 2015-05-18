//
//  TcpMessageContainer.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/16/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__TcpMessageContainer__
#define __GameTemplate__TcpMessageContainer__

#include <stdio.h>
#include <vector>
#include <mutex>

class TcpMessageContainer {
public:
    int startClosing = 0;
    std::mutex lock;
    unsigned short serverPort = 0;
    unsigned short serverUdpPort = 0;
    std::vector<std::string>messagesFromClients;
    std::vector<sf::TcpSocket*>socketsFromClients;
};

#endif /* defined(__GameTemplate__TcpMessageContainer__) */
