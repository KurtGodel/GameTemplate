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
    void sendMeMessage(std::string message);
private:
    MainMenu mainMenu;
};

#endif /* defined(__GameTemplate__App__) */
