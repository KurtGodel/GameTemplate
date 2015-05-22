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

void ClientGame::startGame() {
    clearGameState();
    sendTcpMessage("WHICH MAP");
}

void ClientGame::receivedTcpMessage(std::string message) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() == 0) {
        return;
    }
    if(arr[0] == "START GAME" && arr.size() >= 2) {
        loadMap(arr[1]);
    }
}

void ClientGame::receivedUdpMessage(std::string message) {
    std::cout << "(" << message << ")\n";
    updateDynamicGameFromServerMessage(message);
}

void ClientGame::sendTcpMessage(std::string message) {
    parentApp->sendTcp(message);
}

void ClientGame::sendUdpMessage(std::string message) {
    parentApp->sendUdp(message);
}

void ClientGame::think() {
}

void ClientGame::draw() {
    // draw static state
    for(int i=0; i<staticGame.backgroundCircles.size(); i++) {
        sf::CircleShape circle = sf::CircleShape(50);
        circle.setPosition(staticGame.backgroundCircles[i]);
        circle.setFillColor(sf::Color(100, 250, 50));
        window->draw(circle);
    }
    for(int i=0; i<dynamicGame.players.size(); i++) {
        for(int j=0; j<dynamicGame.players[i].size(); j++) {
            sf::CircleShape circle = sf::CircleShape(30);
            circle.setPosition(sf::Vector2f(dynamicGame.players[i][j].x, dynamicGame.players[i][j].y));
            circle.setFillColor(sf::Color(255, 128, 128));
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
    sf::Vector2u screenSize = window->getSize();
    sendUdpMessage("KEY DOWN\n" + std::to_string(getTime()) + "\n" + std::to_string(event.code));
}

void ClientGame::keyUp(sf::Event::KeyEvent event) {
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
    return elems;
}

void ClientGame::clearGameState() {
    staticGame.backgroundCircles.clear();
}

long long ClientGame::getTime() {
    return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

void ClientGame::updateDynamicGameFromServerMessage(std::string str) {
    // clear game state
    dynamicGame.players.clear();
    
    std::vector<std::string> teams = split(str, '\n');
    for(int i=0; i<teams.size(); i++) {
        dynamicGame.players.push_back(std::vector<Player>());
        std::vector<std::string> players = split(teams[i], ';');
        for(int j=0; j<players.size(); j++) {
            dynamicGame.players[i].push_back(Player());
            updatePlayer(&dynamicGame.players[i][j], split(players[j], ','));
        }
    }
}

void ClientGame::updatePlayer(Player *player, std::vector<std::string> arr) {
    if(arr.size() != 3) {
        return;
    }
    player->username = arr[0];
    player->x = stof(arr[1]);
    player->y = stof(arr[2]);
}
