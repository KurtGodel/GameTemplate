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
Client::Client(sf::RenderWindow &w) : mainMenu(w, this), ClientBaseClass() {
    window = &w;
    sf::IpAddress myIpAddress = sf::IpAddress::getLocalAddress();
    connectToServer(myIpAddress, 55001, 55002, 55004);
}

/*
 This method is called whenever we receive a UDP message from the server.
*/
void Client::receivedUdpMessage(std::string message) {
}

/*
 This method is called whenever we receive a TCP message from the server.
 */
void Client::receivedTcpMessage(std::string message) {
}

/*
 This method is called once-per-frame prior to the draw method. Perform non-drawing related computations here.
*/
void Client::think() {
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
void Client::sendMeMessage(std::string message) {
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
