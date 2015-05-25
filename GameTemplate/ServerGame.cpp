//
//  ServerGame.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerGame.h"

void ServerGame::startGame(std::string mapName, std::vector<std::vector<std::string>>teamList) {
    std::vector<std::string> listOfPlayers;
    teams = teamList;
    for(int i=0; i<teams.size(); i++) {
        for(int j=0; j<teams[i].size(); j++) {
            players[teams[i][j]] = ServerPlayer();
            listOfPlayers.push_back(teams[i][j]);
        }
    }
    timeTracker.start(listOfPlayers);
}

void ServerGame::think() {
    // apply player actions to world and history
    applyInputsToWorld();
    
    // send info back to players
    for(int i=0; i<teams.size(); i++) {
        std::string teamMessage = createMessageForTeam(i);
        for(int j=0; j<teams[i].size(); j++) {
            sendUdpMessage("UPDATE\n" + std::to_string(timeTracker.getClientTime(teams[i][j])) + "\n" + teamMessage, teams[i][j]);
        }
    }
    
    // let timeTranslator update itself
    timeTracker.update();
}

std::string ServerGame::createMessageForTeam(int teamNum) {
    std::string message = "";
    for(int i=0; i<teams.size(); i++) {
        if(i != 0) {
            message += "|";
        }
        for(int j=0; j<teams[i].size(); j++) {
            if(j != 0) {
                message += ";";
            }
            message += teams[i][j];
            message += ",";
            message += std::to_string(players[teams[i][j]].input.timeStamp);
            message += ",";
            message += std::to_string(players[teams[i][j]].x);
            message += ",";
            message += std::to_string(players[teams[i][j]].y);
        }
    }
    return message;
}

std::string ServerGame::applyInputsToWorld() {
    for(int i=0; i<teams.size(); i++) {
        for(int j=0; j<teams[i].size(); j++) {
            if(players[teams[i][j]].input.up) {
                players[teams[i][j]].y -= timeTracker.getDeltaTime()/1000.0*100.0;
            }
            if(players[teams[i][j]].input.down) {
                players[teams[i][j]].y += timeTracker.getDeltaTime()/1000.0*100.0;
            }
            if(players[teams[i][j]].input.right) {
                players[teams[i][j]].x += timeTracker.getDeltaTime()/1000.0*100.0;
            }
            if(players[teams[i][j]].input.left) {
                players[teams[i][j]].x -= timeTracker.getDeltaTime()/1000.0*100.0;
            }
        }
    }
}

void ServerGame::receivedTcpMessage(std::string message, std::string username) {
    if(message == "GIVE NEW GAME INFO") {
        std::string teamsString = "";
        for(int i=0; i<teams.size(); i++) {
            if(i != 0) {
                teamsString += ";";
            }
            for(int j=0; j<teams[i].size(); j++) {
                if(j != 0) {
                    teamsString += ",";
                }
                teamsString += teams[i][j];
            }
        }
        sendTcpMessage("START GAME\n" + std::to_string(timeTracker.getClientTime(username)) + "\n" + teamsString, username);
    }
    else if(message.size() > 4 && message.substr(0,4) == "PING") {
        timeTracker.receivedMesage(message, username);
    }
    else if(message.size() > 5 && message.substr(0,5) == "SHOOT") {
        std::vector<std::string> arr = split(message, '\n');
        if(arr.size() == 3) {
            std::vector<std::string> xy = split(arr[2], ',');
            long long timeStamp = timeTracker.fromClientTimeToServerTime(stoll(arr[1]), username);
            shoot(username, timeStamp, stod(xy[0]), stod(xy[1]));
        }
    }
}

void ServerGame::shoot(std::string username, long long timeStamp, double x, double y) {
    for(int j=0; j<teams.size(); j++) {
        for(int k=0; k<teams[j].size(); k++) {
            if((players[teams[j][k]].x - x)*(players[teams[j][k]].x - x) + (players[teams[j][k]].y - y)*(players[teams[j][k]].y - y) < 2500) {
                // kill
                players[teams[j][k]].x = 0;
                players[teams[j][k]].y = 0;
            }
        }
    }
}

void ServerGame::receivedUdpMessage(std::string message, std::string username) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() < 3) {
        return;
    }
    if(arr[0] == "INPUT") {
        long long timeStampInServerTime = timeTracker.fromClientTimeToServerTime(stoll(arr[1]), username);
        if(timeStampInServerTime > players[username].input.timeStamp) {
            players[username].input.timeStamp = timeStampInServerTime;
            players[username].input.fromString(arr[2]);
        }
    }
}

// IGNORE BELOW THIS LINE

ServerGame::ServerGame(ServerBaseClass &serverBaseClass) : timeTracker(serverBaseClass) {
    parentApp = &serverBaseClass;
}

ServerGame::~ServerGame() {
}

long long ServerGame::getTime() {
    return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

void ServerGame::sendTcpMessage(std::string message, std::string username) {
    parentApp->sendTcpMessage(message, username);
}

void ServerGame::sendUdpMessage(std::string message, std::string username) {
    parentApp->sendUdpMessage(message, username);
}

std::vector<std::string> ServerGame::split(const std::string s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    if(s[s.length()-1] == delim) {
        elems.push_back("");
    }
    return elems;
}