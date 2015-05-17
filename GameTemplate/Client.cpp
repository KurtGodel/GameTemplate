//
//  Client.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Client.h"

Client::Client(sf::RenderWindow &w) : mainMenu(w, this), ClientBaseClass() {
    window = &w;
    connectToServer("137.22.169.68", 55001, 55002, 55004);
}

void Client::receivedUdpMessage(std::string message) {
}

void Client::receivedTcpMessage(std::string message) {
}

void Client::think() {
}

void Client::draw() {
    if(inMainMenu) {
        mainMenu.draw();
    }
}

void Client::mouseMove(sf::Event::MouseMoveEvent event) {
    if(inMainMenu) {
        mainMenu.mouseMove(event);
    }
}

void Client::mouseDown(sf::Event::MouseButtonEvent event) {
    if(inMainMenu) {
        mainMenu.mouseDown(event);
    }
}

void Client::mouseUp(sf::Event::MouseButtonEvent event) {
    if(inMainMenu) {
        mainMenu.mouseUp(event);
    }
}

void Client::keyDown(sf::Event::KeyEvent event) {
    if(inMainMenu) {
        mainMenu.keyDown(event);
    }
}

void Client::keyUp(sf::Event::KeyEvent event) {
    if(inMainMenu) {
        mainMenu.keyUp(event);
    }
}

void Client::textEntered(sf::Event::TextEvent event) {
    if(inMainMenu) {
        mainMenu.textEntered(event);
    }
}

void Client::sendMeMessage(std::string message) {
}
