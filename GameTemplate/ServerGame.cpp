//
//  ServerGame.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ServerGame.h"

ServerGame::ServerGame(ServerBaseClass &serverBaseClass) {
    parentApp = &serverBaseClass;
}

ServerGame::~ServerGame() {
}

void ServerGame::startGame(std::string mapName, std::vector<std::vector<std::string>>teamList) {
    teams = teamList;
    clearGameState();
    loadMap(mapName);
}

void ServerGame::think() {
    for(unsigned int i=0; i<teams.size(); i++) {
        std::string message = createMessageForTeam(i);
        for(unsigned int j=0; j<teams[i].size(); j++) {
            sendTcpMessage(message, teams[i][j]);
        }
    }
}

std::string ServerGame::createMessageForTeam(unsigned int i) {
    return "";
}

void ServerGame::receivedTcpMessage(std::string message, std::string username) {
    if(message == "WHICH MAP") {
        sendTcpMessage("START GAME\n" + mapName, username);
    }
}

void ServerGame::receivedUdpMessage(std::string message, std::string username) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() == 0) {
        return;
    }
    
    /*
     Format of Inputs:
     event type: KEY DOWN
     milliseconds since 1970: 1432268103
     paramters of event: 15
     */
    if(arr[0] == "KEY DOWN" && arr.size() >= 3) {
        keyDown(stoll(arr[1]), stoi(arr[2]), username);
    }
}

void ServerGame::keyDown(long long timeStamp, int keyCode, std::string username) {
    std::cout << getTime()-timeStamp << "\n";
}

void ServerGame::sendTcpMessage(std::string message, std::string username) {
    if(username == "") {
        parentApp->sendTcpMessage(message, "SERVER");
    }
    else {
        parentApp->sendTcpMessage(message, username);
    }
}

void ServerGame::sendUdpMessage(std::string message, std::string username) {
    if(username == "") {
        parentApp->sendUdpMessage(message, "SERVER");
    }
    else {
        parentApp->sendUdpMessage(message, username);
    }
}

void ServerGame::loadMap(std::string newMapName) {
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
    return elems;
}

void ServerGame::clearGameState() {
    staticGame.backgroundCircles.clear();
}

long long ServerGame::getTime() {
    return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}