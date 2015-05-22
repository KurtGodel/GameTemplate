//
//  App.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/18/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__App__
#define __GameTemplate__App__

#include <stdio.h>
#include <sstream>
#include <chrono>
#include <SFML/Graphics.hpp>
#include "AppBaseClass.h"
#include "MainMenu.h"
#include "ClientGame.h"

class App : public AppBaseClass {
public:
    App(sf::RenderWindow &w, ClientCommunicator &clientCommunicator);
    ~App();
    void think();
    void draw();
    void mouseMove(sf::Event::MouseMoveEvent event);
    void mouseDown(sf::Event::MouseButtonEvent event);
    void mouseUp(sf::Event::MouseButtonEvent event);
    void keyDown(sf::Event::KeyEvent event);
    void keyUp(sf::Event::KeyEvent event);
    void textEntered(sf::Event::TextEvent event);
    void receivedUdpMessage(std::string message);
    void receivedTcpMessage(std::string message);
    std::string sendMeMessage(std::string message);
private:
    MainMenu mainMenu;
    ClientGame game;
    std::vector<std::string> split(const std::string s, char delim);
    std::vector<std::string> chat;
    std::string username = "";
    long long lastAliveMessageSent;
    bool isShowingMainMenu = true;
};

#endif /* defined(__GameTemplate__App__) */
