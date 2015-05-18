//
//  Client.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Client.h"

/*
 Just remember to initalize the ClientBaseClass
*/
Client::Client(sf::RenderWindow &w, TcpMessageContainer &tcpMessageContainer) : mainMenu(w, this), ClientBaseClass(tcpMessageContainer) {
    window = &w;
    sf::IpAddress myIpAddress = sf::IpAddress::getLocalAddress();
    connectToServer(myIpAddress, 0, getServerTcpPort());
}

/*
 This method is called whenever we receive a UDP message from the server.
*/
void Client::receivedUdpMessage(std::string message) {
    std::cout << "CR{UDP:" << message << "}\n";
}

/*
 This method is called whenever we receive a TCP message from the server.
 */
void Client::receivedTcpMessage(std::string message) {
    std::cout << "CR{TCP:" << message << "}\n";
}

/*
 This method is called once-per-frame prior to the draw method. Perform non-drawing related computations here.
*/
void Client::think() {
    if(inMainMenu) {
        mainMenu.think();
    }
}

/*
 This method is called once-per-frame. Perform your drawing here.
*/
void Client::draw() {
    if(inMainMenu) {
        mainMenu.draw();
    }
}

/*
 This function is declared in ClientBaseClass to allow its child objects to send it messages. For instance mainMenu needs to send Client a message  when a user tries to connect to the server.
*/
std::string Client::sendMeMessage(std::string message) {
    std::vector<std::string> messages = split(message, '\n');
    if(messages[0] == "get my server port") {
        return std::to_string(getServerTcpPort());
    }
    else if(messages[0] == "get my server udp port") {
        return std::to_string(getServerUdpPort());
    }
    else if(messages[0] == "Login To Server" && messages.size() >= 5) {
        std::string username = messages[1];
        sf::IpAddress ipAddress(messages[2]);
        unsigned short tcpPort = stoi(messages[3]);
        unsigned short udpPort = stoi(messages[4]);

        connectToServer(ipAddress, udpPort, tcpPort);
    }
}

std::vector<std::string> Client::split(const std::string s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

/*
 The methods here are all called when their corresponding events occur.
*/
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
