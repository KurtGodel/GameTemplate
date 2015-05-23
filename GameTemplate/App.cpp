//
//  App.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/18/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "App.h"

App::App(sf::RenderWindow &w, ClientCommunicator &clientCommunicator) : mainMenu(w, *this), AppBaseClass(clientCommunicator), game(w, *this) {
    connectToServer("", "0.0.0.0", 0);
}

App::~App() {
}

void App::think() {
    // keep sending "george"
    
    long long ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
    if(isShowingMainMenu) {
        mainMenu.think();
    }
    else {
        game.think();
    }
}

void App::draw() {
    if(isShowingMainMenu) {
        mainMenu.draw();
    }
    else {
        game.draw();
    }
}

void App::mouseMove(sf::Event::MouseMoveEvent event) {
    if(isShowingMainMenu) {
        mainMenu.mouseMove(event);
    }
    else {
        game.mouseMove(event);
    }
}

void App::mouseDown(sf::Event::MouseButtonEvent event) {
    if(isShowingMainMenu) {
        mainMenu.mouseDown(event);
    }
    else {
        game.mouseDown(event);
    }
}

void App::mouseUp(sf::Event::MouseButtonEvent event) {
    if(isShowingMainMenu) {
        mainMenu.mouseUp(event);
    }
    else {
        game.mouseUp(event);
    }
}

void App::keyDown(sf::Event::KeyEvent event) {
    if(isShowingMainMenu) {
        mainMenu.keyDown(event);
    }
    else {
        game.keyDown(event);
    }
}

void App::keyUp(sf::Event::KeyEvent event) {
    if(isShowingMainMenu) {
        mainMenu.keyUp(event);
    }
    else {
        game.keyUp(event);
    }
}

void App::textEntered(sf::Event::TextEvent event) {
    if(isShowingMainMenu) {
        mainMenu.textEntered(event);
    }
    else {
        game.textEntered(event);
    }
}

void App::receivedTcpMessage(std::string message) {
    if(isShowingMainMenu) {
        if(message == "DID CONNECT" || message == "DID NOT CONNECT" || message == "USERNAME NOT UNIQUE") {
            mainMenu.sendMeResultOfClientConnect(message);
        }
        else {
            // do something else with it
            std::vector<std::string> arr = split(message, '\n');
            if(arr.size() == 0) {
                return;
            }
            if(arr[0] == "CHAT MESSAGE" && arr.size() == 2) {
                chat.push_back(arr[1]);
                mainMenu.updateChat(&chat);
            }
            else if(arr[0] == "TEAM LIST") {
                mainMenu.updateTeams(&arr);
            }
            else if(arr[0] == "LAUNCHING GAME") {
                isShowingMainMenu = false;
                game.startGame(username);
            }
            else {
                // handle other messages
            }
        }
    }
    else {
        game.receivedTcpMessage(message);
    }
}

void App::receivedUdpMessage(std::string message) {
    if(!isShowingMainMenu) {
        game.receivedUdpMessage(message);
    }
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
            if(sf::IpAddress::getLocalAddress().toString() == ipAddress.toString()) {
                // you can't connect to yourself
                // reinstate these two lines of code when its time for release
                // mainMenu.sendMeResultOfClientConnect("CONNECTING TO SELF");
                // return;
            }
            unsigned short port = stoi(arr[3]);
            connectToServer(username, ipAddress, port);
        }
    }
    else if(arr[0] == "Log Out") {
        connectToServer("", "0.0.0.0", 0);
    }
    else if(arr[0] == "Chat Message") {
        sendTcp(message);
    }
    else if(arr[0] == "No Team") {
        sendTcp("Join No Team");
    }
    else if(arr[0] == "Team 1") {
        sendTcp("Join Team 1");
    }
    else if(arr[0] == "Team 2") {
        sendTcp("Join Team 2");
    }
    else if(arr[0] == "Launch Game") {
        sendTcp("LAUNCH GAME");
    }
    else if(arr[0] == "Matchmakign Server") {
        username = "SERVER";
    }
}

std::vector<std::string> App::split(const std::string s, char delim) {
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
