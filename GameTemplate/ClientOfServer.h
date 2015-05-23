//
//  ClientOfServer.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ClientOfServer__
#define __GameTemplate__ClientOfServer__

#include <stdio.h>
#include <SFML/Network.hpp>

struct ClientOfServer {
    std::string username;
    sf::TcpSocket *tcpSocket;
    unsigned short udpPort = 0;
};

#endif /* defined(__GameTemplate__ClientOfServer__) */
