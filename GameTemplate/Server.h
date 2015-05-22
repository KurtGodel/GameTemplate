//
//  Server.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__Server__
#define __GameTemplate__Server__

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <chrono>
#include "ServerBaseClass.h"
#include "ClientOfServer.h"
#include "ServerGame.h"

class Server : public ServerBaseClass {
public:
    Server(TcpHandlerCommunicator &tcpHandlerCommunicator, ClientServerCommunicator &clientServerCommunicator);
    ~Server();
    void run();
    void sendTcpMessage(std::string message, std::string username);
    void sendUdpMessage(std::string message, std::string username);
protected:
    void receivedTcpMessage(std::string message, sf::TcpSocket *socket);
    void receivedUdpMessage(std::string message, sf::IpAddress ipAddressOfClient, unsigned short portOfClient);
private:
    std::vector<std::string> chatMessages;
    bool isUsernameUnique(std::string name);
    std::vector<ClientOfServer> tableOfClients;
    std::vector<std::vector<std::string>> teams;
    
    bool isGameOccuring = false;
    ServerGame game;
    
    void removeTcpSocket(sf::TcpSocket *socketToRemove);
    void sendTcpMessageToAllClients(std::string message);
    void sendListOfTeamsToAllClients();
    void changeTeamOfClient(std::string username, int newTeam);
    void heardFromClient(sf::TcpSocket *socket);
    void logOutUser(sf::TcpSocket *socket);
    std::vector<std::string> split(const std::string s, char delim);
};

#endif /* defined(__GameTemplate__Server__) */
