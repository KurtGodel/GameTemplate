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
    clearGameState();
    loadMap(mapName);
    initalizeDynamicState(teamList);
}

void ServerGame::think() {
    for(unsigned int i=0; i<dynamicGame[dynamicGame.size()-1].players.size(); i++) {
        std::string message = createMessageForTeam(i);
        for(unsigned int j=0; j<dynamicGame[dynamicGame.size()-1].players[i].size(); j++) {
            sendUdpMessage(message, dynamicGame[dynamicGame.size()-1].players[i][j].username);
        }
    }
    
    // update dynamicGame history
    DynamicGameState copyOfCurrentGameState = dynamicGame[dynamicGame.size()-1];
    copyOfCurrentGameState.timeStamp = getTime();
    dynamicGame.push_back(copyOfCurrentGameState);
    if(dynamicGame.size() > 20) {
        dynamicGame.erase(dynamicGame.begin()+dynamicGame.size()-1,dynamicGame.begin()+dynamicGame.size());
    }
}

std::string ServerGame::createMessageForTeam(unsigned int i) {
    std::string rtn = "";
    for(int i=0; i<dynamicGame[dynamicGame.size()-1].players.size(); i++) {
        if(i != 0) {
            rtn += "\n";
        }
        for(int j=0; j<dynamicGame[dynamicGame.size()-1].players[i].size(); j++) {
            if(j != 0) {
                rtn += ";";
            }
            rtn += dynamicGame[dynamicGame.size()-1].players[i][j].username;
            rtn += ",";
            rtn += std::to_string(dynamicGame[dynamicGame.size()-1].players[i][j].x);
            rtn += ",";
            rtn += std::to_string(dynamicGame[dynamicGame.size()-1].players[i][j].y);
        }
    }
    return rtn;
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
    for(int i=0; i<dynamicGame.size(); i++) {
        if(timeStamp > dynamicGame[i].timeStamp) {
            // this frame happened after the event - it should be altered
            for(int j=0; j<dynamicGame[i].players.size(); j++) {
                for(int k=0; k<dynamicGame[i].players[j].size(); k++) {
                    if(dynamicGame[i].players[j][k].username == username) {
                        if(keyCode == sf::Keyboard::Up) {
                            dynamicGame[i].players[j][k].y -= 20;
                        }
                        else if(keyCode == sf::Keyboard::Down) {
                            dynamicGame[i].players[j][k].y += 20;
                        }
                        else if(keyCode == sf::Keyboard::Right) {
                            dynamicGame[i].players[j][k].x += 20;
                        }
                        else if(keyCode == sf::Keyboard::Left) {
                            dynamicGame[i].players[j][k].x -= 20;
                        }
                    }
                }
            }
        }
    }
    std::cout << getTime()-timeStamp << "\n";
}

void ServerGame::sendTcpMessage(std::string message, std::string username) {
    parentApp->sendTcpMessage(message, username);
}

void ServerGame::sendUdpMessage(std::string message, std::string username) {
    parentApp->sendUdpMessage(message, username);
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

void ServerGame::initalizeDynamicState(std::vector<std::vector<std::string>> teamList) {
    dynamicGame.push_back(DynamicGameState());
    for(int i=0; i<teamList.size(); i++) {
        dynamicGame[0].players.push_back(std::vector<Player>());
        for(int j=0; j<teamList[i].size(); j++) {
            dynamicGame[0].players[i].push_back(Player());
            dynamicGame[0].players[i][j].username = teamList[i][j];
            dynamicGame[0].players[i][j].x = 0;
            dynamicGame[0].players[i][j].y = 0;
        }
    }
}