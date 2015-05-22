//
//  ServerGame.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ServerGame__
#define __GameTemplate__ServerGame__

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ResourcePath.hpp"
#include "ServerBaseClass.h"
#include "StaticGameState.h"
#include "DynamicGameState.h"

class ServerGame {
public:
    ServerGame(ServerBaseClass &serverBaseClass);
    ~ServerGame();
    void startGame(std::string mapName, std::vector<std::vector<std::string>>teams);
    void receivedTcpMessage(std::string message, std::string username);
    void receivedUdpMessage(std::string message, std::string username);
private:
    ServerBaseClass *parentApp;
    std::vector<std::string> split(const std::string s, char delim);
    std::string readFile(std::string fileName);
    void sendTcpMessage(std::string message, std::string username);
    void sendUdpMessage(std::string message, std::string username);
    void loadMap(std::string newMapName);
    void clearGameState();
    
    StaticGameState staticGame;
    std::vector<DynamicGameState> gameHistory;
    std::string mapName = "";
};

#endif /* defined(__GameTemplate__ServerGame__) */
