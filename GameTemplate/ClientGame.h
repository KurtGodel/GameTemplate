//
//  ClientGame.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ClientGame__
#define __GameTemplate__ClientGame__

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "AppBaseClass.h"

#include "StaticGameState.h"
#include "InputTracker.h"
#include "ClientPlayer.h"

class ClientGame {
public:
    ClientGame(sf::RenderWindow &w, AppBaseClass &appBaseClass);
    ~ClientGame();
    void startGame(std::string userName);
    void receivedTcpMessage(std::string message);
    void receivedUdpMessage(std::string message);
    void sendTcpMessage(std::string message);
    void sendUdpMessage(std::string message);
    void think();
    void draw();
    void mouseMove(sf::Event::MouseMoveEvent event);
    void mouseDown(sf::Event::MouseButtonEvent event);
    void mouseUp(sf::Event::MouseButtonEvent event);
    void keyDown(sf::Event::KeyEvent event);
    void keyUp(sf::Event::KeyEvent event);
    void textEntered(sf::Event::TextEvent event);
private:
    AppBaseClass *parentApp;
    sf::RenderWindow *window;
    std::string mapName;
    StaticGameState staticGame;
    std::string myUserName = "";
    InputTracker input;
    
    std::unordered_map<std::string, ClientPlayer> players;
    std::vector<std::vector<std::string>> teams;
    
    std::string readFile(std::string fileName);
    void loadMap(std::string newMapName);
    void clearGameState();
    long long getTime();
    std::vector<std::string> split(const std::string s, char delim);
    void loadPlayers(std::string teamsString);
    void updateWorld(std::string messageFromServer, long long lag);
};

#endif /* defined(__GameTemplate__ClientGame__) */
