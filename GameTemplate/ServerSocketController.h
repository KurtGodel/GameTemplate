//
//  ServerSocketController.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/16/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ServerSocketController__
#define __GameTemplate__ServerSocketController__

#include <stdio.h>
#include <iostream>
#include <list>
#include <SFML/Network.hpp>
#include <TcpMessageContainer.h>

class ServerSocketController {
public:
    ServerSocketController(TcpMessageContainer &tcpMessageContainer);
    ~ServerSocketController();
    void run();
private:
    std::list<sf::TcpSocket*> clients;
    sf::SocketSelector selector;
    sf::TcpListener listener;
    TcpMessageContainer *messageContainer;
};

#endif /* defined(__GameTemplate__ServerSocketController__) */
