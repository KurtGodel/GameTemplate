//
//  Server.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__Server__
#define __GameTemplate__Server__

#include <stdio.h>
#include <iostream>
#include <time.h>
#include <unordered_map>
#include <SFML/Network.hpp>
#include "ServerBaseClass.h"

class Server : public ServerBaseClass {
public:
    Server();
    ~Server();
    void update();
    
protected:
    void receivedUdpMessage(std::string& message, sf::IpAddress address, unsigned short port);
};

#endif /* defined(__GameTemplate__Server__) */
