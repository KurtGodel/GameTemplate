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
#include <SFML/Graphics.hpp>
#include "AppBaseClass.h"
#include "MainMenu.h"

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
    void update();
    std::string sendMeMessage(std::string message);
private:
    MainMenu mainMenu;
    std::vector<std::string> split(const std::string s, char delim);
    std::vector<std::string> chat;
    std::string username = "";
};

#endif /* defined(__GameTemplate__App__) */
