//
//  App.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/18/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "App.h"

App::App(sf::RenderWindow &w, ClientCommunicator &clientCommunicator) : mainMenu(w, *this), AppBaseClass(clientCommunicator) {
    connectToServer("", "0.0.0.0", 0);
}

App::~App() {
}

void App::think() {
    // keep sending "george"
    mainMenu.think();
}

void App::draw() {
    mainMenu.draw();
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
    if(message == "DID CONNECT" || message == "DID NOT CONNECT" || message == "USERNAME NOT UNIQUE") {
        mainMenu.sendMeResultOfClientConnect(message);
    }
    else {
        // do something else with it
    }
}

void App::receivedUdpMessage(std::string message) {
}

void App::update() {
}

std::string App::sendMeMessage(std::string message) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() == 0) {
        std::cout << "Error: empty message sent to App";
        return nullptr;
    }
    if(arr[0] == "get my server tcp port") {
        return std::to_string(getTcpPortOfLocalServer());
    }
    else if(arr[0] == "Login To Server") {
        if(arr.size() == 4) {
            username = arr[1];
            sf::IpAddress ipAddress(arr[2]);
            unsigned short port = stoi(arr[3]);
            connectToServer(username, ipAddress, port);
        }
    }
    else if(arr[0] == "Log Out") {
        connectToServer("", "0.0.0.0", 0);
    }
    else if(arr[0] == "Chat Message") {
        // sendTcp(message);
    }
}

std::vector<std::string> App::split(const std::string s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
