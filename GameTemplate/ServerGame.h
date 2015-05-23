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
#include <chrono>
#include <unordered_map>
#include "ResourcePath.hpp"
#include "ServerBaseClass.h"

#include "StaticGameState.h"
#include "InputTracker.h"
#include "TimeTracker.h"
#include "ServerPlayer.h"

class ServerGame {
public:
    ServerGame(ServerBaseClass &serverBaseClass);
    ~ServerGame();
    void startGame(std::string mapName, std::vector<std::vector<std::string>>teamList);
    void think();
    void receivedTcpMessage(std::string message, std::string username);
    void receivedUdpMessage(std::string message, std::string username);
private:
    TimeTracker timeTracker;
    
    StaticGameState staticGame;
    
    std::string mapName = "";
    ServerBaseClass *parentApp;
    std::unordered_map<std::string, ServerPlayer> players;
    std::vector<std::unordered_map<std::string, ServerPlayer>> history;
    std::vector<std::vector<std::string>> teams;
    
    
    std::vector<std::string> split(const std::string s, char delim);
    std::string readFile(std::string fileName);
    void sendTcpMessage(std::string message, std::string username);
    void sendUdpMessage(std::string message, std::string username);
    void updateInputs(long long timeStamp, std::string message, std::string username);
    void loadMap(std::string newMapName);
    void move(long long timeStamp, float deltaX, float deltaY, std::string username);
    long long getTime();
    std::string createMessageForTeam(int teamNum);
    std::string applyInputsToWorld(std::string username);
};

#endif /* defined(__GameTemplate__ServerGame__) */
