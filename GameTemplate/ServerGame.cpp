//
//  ServerGame.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerGame.h"

/*
 All messages take the form
 {message type}
 {time stamp}
 {contents of message}
 
 
 EXAPLES FROM CLIENT (TO SERVER)
    WHICH MAP
    1432407479521
 
    PING
    1432407479521
    1432407475521
 
 EXAMPLES FROM SERVER (TO CLIENT):
    PING
    1432407479521
*/

ServerGame::ServerGame(ServerBaseClass &serverBaseClass) : timeTracker(serverBaseClass) {
    parentApp = &serverBaseClass;
}

ServerGame::~ServerGame() {
}

void ServerGame::startGame(std::string mapName, std::vector<std::vector<std::string>>teamList) {
    loadMap(mapName);
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
    // apply player actions
    for(int i=0; i<teams.size(); i++) {
        for(int j=0; j<teams[i].size(); j++) {
            applyInputsToWorld(teams[i][j]);
        }
    }
    
    // send info back to players
    for(int i=0; i<teams.size(); i++) {
        std::string teamMessage = createMessageForTeam(i);
        for(int j=0; j<teams[i].size(); j++) {
            sendUdpMessage("UPDATE\n" + std::to_string(timeTracker.getClientTime(teams[i][j])) + "\n" + teamMessage, teams[i][j]);
        }
    }
    
    // let timeTranslator update itself
    timeTracker.update();
    
    // update history vector
    history.push_back(players);
    if(history.size() > 40) {
        history.erase(history.begin(), history.begin()+1);
    }
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
            message += std::to_string(players[teams[i][j]].x);
            message += ",";
            message += std::to_string(players[teams[i][j]].y);
        }
    }
    return message;
}

std::string ServerGame::applyInputsToWorld(std::string username) {
    if(players[username].input.up) {
        players[username].x += timeTracker.getDeltaTime()/1000.0*100.0;
    }
}

void ServerGame::receivedTcpMessage(std::string message, std::string username) {
    if(message == "WHICH MAP") {
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
        sendTcpMessage("START GAME\n" + std::to_string(timeTracker.getClientTime(username)) + "\n" + mapName + "|" + teamsString, username);
    }
    else if(message.size() > 4 && message.substr(0,4) == "PING") {
        timeTracker.receivedMesage(message, username);
    }
    else if(message.size() > 5 && message.substr(0,5) == "INPUT") {
        std::vector<std::string> arr = split(message, '\n');
        if(arr.size() == 3) {
            players[username].input.fromString(arr[2]);
        }
    }
}

void ServerGame::receivedUdpMessage(std::string message, std::string username) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() < 3) {
        return;
    }
    if(arr[0] == "INPUT") {
        long long timeStampInServerTime = timeTracker.fromClientTimeToServerTime(players[username].input.timeStamp, username);
        if(stoll(arr[1]) > timeStampInServerTime) {
            players[username].input.timeStamp = timeStampInServerTime;
            players[username].input.fromString(arr[2]);
        }
    }
}

void ServerGame::loadMap(std::string newMapName) {
    staticGame.backgroundCircles.clear();
    mapName = newMapName;
    std::string mapString = readFile(mapName+".txt");
    std::vector<std::string> lineByLine = split(mapString, '\n');
    for(int i=0; i<lineByLine.size(); i++) {
        std::vector<std::string> csv = split(lineByLine[i], ',');
        if(csv.size() == 2) {
            staticGame.backgroundCircles.push_back(sf::Vector2f(stof(csv[0]), stof(csv[1])));
        }
    }
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

std::string ServerGame::readFile(std::string fileName) {
    std::string line;
    std::ifstream myfile (resourcePath()+fileName);
    std::string str = "";
    if (myfile.is_open()) {
        while(getline(myfile,line)) {
            str += line + "\n";
        }
        myfile.close();
        return str;
    }
    else {
        return "";
    }
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