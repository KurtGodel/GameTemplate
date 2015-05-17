//
//  ServerSocketController.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/16/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerSocketController.h"

ServerSocketController::ServerSocketController(TcpMessageContainer &tcpMessageContainer) {
    messageContainer = &tcpMessageContainer;
    sf::Socket::Status status = listener.listen(55004);
    selector.add(listener);
}

ServerSocketController::~ServerSocketController() {
    //
}

void ServerSocketController::run() {
    // Endless loop that waits for new connections
    while(true)
    {
        if(messageContainer->startClosing > 0) {
            messageContainer->startClosing++;
            return;
        }
        
        // Make the selector wait for data on any socket
        if(selector.wait())
        {
            // Test the listener
            if(selector.isReady(listener))
            {
                // The listener is ready: there is a pending connection
                sf::TcpSocket* client = new sf::TcpSocket;
                if(listener.accept(*client) == sf::Socket::Done)
                {
                    // Add the new client to the clients list
                    clients.push_back(client);
                    // Add the new client to the selector so that we will
                    // be notified when he sends something
                    selector.add(*client);
                }
                else
                {
                    // Error, we won't get a new connection, delete the socket
                    delete client;
                }
            }
            else
            {
                // The listener socket is not ready, test all other sockets (the clients)
                for(std::list<sf::TcpSocket*>::iterator it = clients.begin(); it != clients.end(); ++it)
                {
                    sf::TcpSocket& client = **it;
                    if(selector.isReady(client))
                    {
                        // The client has sent some data, we can receive it
                        char buffer[1024];
                        char *begin = buffer;
                        char *end = begin + sizeof(buffer);
                        std::fill(begin, end, 0);
                        std::size_t received = 0;
                        client.receive(buffer, sizeof(buffer), received);
                        std::string message(buffer);
                        
                        if(message != "") {
                            std::string addres = client.getRemoteAddress().toString();
                            messageContainer->lock.lock();
                            messageContainer->socketsFromClients.push_back(&client);
                            messageContainer->messagesFromClients.push_back(message);
                            messageContainer->lock.unlock();
                        }
                    }
                }
            }
        }
    }
}