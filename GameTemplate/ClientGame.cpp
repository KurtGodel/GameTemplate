//
//  ClientGame.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "ClientGame.h"

ClientGame::ClientGame(sf::RenderWindow &w, AppBaseClass &appBaseClass) {
    parentApp = &appBaseClass;
    window = &w;
}

ClientGame::~ClientGame() {
}

void ClientGame::startGame(std::string userName) {
    myUserName = userName;
    clearGameState();
    sendTcpMessage("WHICH MAP");
}

void ClientGame::receivedTcpMessage(std::string message) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() == 0) {
        return;
    }
    if(arr[0] == "START GAME" && arr.size() >= 3) {
        long long timeStamp = stoll(arr[1]);
        std::vector<std::string> arr2 = split(arr[2], '|');
        loadMap(arr2[0]);
        loadPlayers(arr2[1]);
    }
    else if(arr[0] == "PING") {
        message += "\n";
        message += std::to_string(getTime());
        sendTcpMessage(message);
    }
}

void ClientGame::receivedUdpMessage(std::string message) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() == 0) {
        return;
    }
    if(arr[0] == "UPDATE" && arr.size() >= 3) {
        long long timeStamp = stoll(arr[1]);
        long long lag = getTime() - timeStamp;
        updateWorld(arr[2], lag);
    }
}

void ClientGame::updateWorld(std::string messageFromServer, long long lag) {
    std::vector<std::string> teamStrings = split(messageFromServer, '|');
    for(int i=0; i<teamStrings.size(); i++) {
        std::vector<std::string> playerStrings = split(teamStrings[i], ';');
        for(int j=0; j<playerStrings.size(); j++) {
            std::vector<std::string> arr = split(playerStrings[j], ',');
            if(arr.size() == 3) {
                players[arr[0]].x = stod(arr[1]);
                players[arr[0]].y = stod(arr[2]);
            }
        }
    }
}

void ClientGame::sendTcpMessage(std::string message) {
    parentApp->sendTcp(message);
}

void ClientGame::sendUdpMessage(std::string message) {
    parentApp->sendUdp(message);
}

void ClientGame::think() {
    sendUdpMessage("INPUT\n" + std::to_string(getTime()) + "\n" + input.toString());
}

void ClientGame::draw() {
    // draw static state
    for(int i=0; i<staticGame.backgroundCircles.size(); i++) {
        sf::CircleShape circle = sf::CircleShape(50);
        circle.setPosition(staticGame.backgroundCircles[i]);
        circle.setFillColor(sf::Color(100, 250, 50));
        window->draw(circle);
    }
    
    // draw players
    for(int i=0; i<teams.size(); i++) {
        for(int j=0; j<teams[i].size(); j++) {
            sf::CircleShape circle = sf::CircleShape(50);
            circle.setPosition(staticGame.backgroundCircles[i]);
            circle.setFillColor(sf::Color(255, 50, 50));
            circle.setPosition(players[teams[i][j]].x, players[teams[i][j]].y);
            window->draw(circle);
        }
    }
}

void ClientGame::mouseMove(sf::Event::MouseMoveEvent event) {
}

void ClientGame::mouseDown(sf::Event::MouseButtonEvent event) {
}

void ClientGame::mouseUp(sf::Event::MouseButtonEvent event) {
}

void ClientGame::keyDown(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Up) {
        input.up = true;
    }
    if(event.code == sf::Keyboard::Down) {
        input.down = true;
    }
    if(event.code == sf::Keyboard::Left) {
        input.left = true;
    }
    if(event.code == sf::Keyboard::Right) {
        input.right = true;
    }
}

void ClientGame::keyUp(sf::Event::KeyEvent event) {
    if(event.code == sf::Keyboard::Up) {
        input.up = false;
    }
    if(event.code == sf::Keyboard::Down) {
        input.down = false;
    }
    if(event.code == sf::Keyboard::Left) {
        input.left = false;
    }
    if(event.code == sf::Keyboard::Right) {
        input.right = false;
    }
}

void ClientGame::textEntered(sf::Event::TextEvent event) {
}

void ClientGame::loadMap(std::string newMapName) {
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

void ClientGame::loadPlayers(std::string teamsString) {
    players.clear();
    teams.clear();
    std::vector<std::string> arr = split(teamsString, ';');
    for(int i=0; i<arr.size(); i++) {
        teams.push_back(std::vector<std::string>());
        std::vector<std::string> arr2 = split(arr[i], ',');
        for(int j=0; j<arr2.size(); j++) {
            teams[i].push_back(arr2[j]);
        }
    }
    
    for(int i=0; i<teams.size(); i++) {
        for(int j=0; j<teams[i].size(); j++) {
            players[teams[i][j]] = ClientPlayer();
        }
    }
}

std::string ClientGame::readFile(std::string fileName) {
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

std::vector<std::string> ClientGame::split(const std::string s, char delim) {
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

void ClientGame::clearGameState() {
    staticGame.backgroundCircles.clear();
}

long long ClientGame::getTime() {
    return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}
