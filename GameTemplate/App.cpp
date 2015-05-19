//
//  App.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/18/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "App.h"

App::App(sf::RenderWindow &w, ClientCommunicator &clientCommunicator) : mainMenu(w, *this), AppBaseClass(clientCommunicator) {
    connectToServer("0.0.0.0", 0);
}

App::~App() {
}

void App::think() {
    // keep sending "george"
    std::cout << "I";
    sendUdp("fred");
}

void App::draw() {
}

void App::mouseMove(sf::Event::MouseMoveEvent event) {
    mainMenu.mouseMove(event);
}

void App::mouseDown(sf::Event::MouseButtonEvent event) {
    mainMenu.mouseDown(event);
}

void App::mouseUp(sf::Event::MouseButtonEvent event) {
    mainMenu.mouseUp(event);
}

void App::keyDown(sf::Event::KeyEvent event) {
    mainMenu.keyDown(event);
}

void App::keyUp(sf::Event::KeyEvent event) {
    mainMenu.keyUp(event);
}

void App::textEntered(sf::Event::TextEvent event) {
    mainMenu.textEntered(event);
}

void App::receivedTcpMessage(std::string message) {
    // todo
}

void App::receivedUdpMessage(std::string message) {
    // todo
}

void App::update() {
}

void App::sendMeMessage(std::string message) {
}
