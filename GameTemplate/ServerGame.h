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

#include "InputTracker.h"
#include "TimeTracker.h"
#include "ServerPlayer.h"

class ServerGame {
public:
    // Ignore Me
    ServerGame(ServerBaseClass &serverBaseClass); // constructor
    ~ServerGame(); // deconstructor
    
    
    void startGame(std::string mapName, std::vector<std::vector<std::string>>teamList); // is called at the start of a new game
    void think(); // is called every "frame"
    void receivedTcpMessage(std::string message, std::string username); // is called when the server receives a TCP message from a client
    void receivedUdpMessage(std::string message, std::string username); // is called when the server receives a UDP message from a client
private:
    std::unordered_map<std::string, ServerPlayer> players; // hashtable of usernames to player-objects
    std::vector<std::vector<std::string>> teams; // list of teams - each team is a list of usernames
    
    void updateInputs(long long timeStamp, std::string message, std::string username);
    void move(long long timeStamp, float deltaX, float deltaY, std::string username);
    std::string createMessageForTeam(int teamNum);
    std::string applyInputsToWorld();
    void shoot(std::string username, long long timeStamp, double x, double y);
    
    
    
    // premade methods & objects
    TimeTracker timeTracker; // this object keeps track of clock-discrepencies between the client and the server
    
    std::vector<std::string> split(const std::string s, char delim); // splits a string; EX: split("Alice is cool.", ' ') --> ["Alice", "is", "cool"]
    void sendTcpMessage(std::string message, std::string username); // sends a TCP message to a client (specified by username)
    void sendUdpMessage(std::string message, std::string username); // sends a TCP message to a client (specified by username)
    long long getTime(); // get the current time in milliseconds
    
    
    
    // ignore below this line
    ServerBaseClass *parentApp;
};

#endif /* defined(__GameTemplate__ServerGame__) */
