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

#include "InputTracker.h"
#include "ClientPlayer.h"

class ClientGame {
public:
    ClientGame(sf::RenderWindow &w, AppBaseClass &appBaseClass);
    ~ClientGame();
    
    // Game Specific Methods
    void startGame(std::string userName); // called at the beginning of a game
    
    // Network Methods
    void receivedTcpMessage(std::string message); // is called whenever a TCP message is received from the server
    void receivedUdpMessage(std::string message); // is called whenever a UDP message is received from the server
    void sendTcpMessage(std::string message); // sends a TCP message to the server
    void sendUdpMessage(std::string message); // sends a UDP message to the server
    
    // Per Frame Methods
    void think(); // called once per frame - do game-related calculations here
    void draw(); // called once per frame - draw the game to the window using *window
    
    // Event Methods
    void mouseMove(sf::Event::MouseMoveEvent event); // called whenever the client moves the mouse
    void mouseDown(sf::Event::MouseButtonEvent event); // called whenever the client presses the mouse down
    void mouseUp(sf::Event::MouseButtonEvent event); // called whenever the client releases the mouse
    void keyDown(sf::Event::KeyEvent event); // called whenever a key is pressed
    void keyUp(sf::Event::KeyEvent event); // called whenever a key is released
    void textEntered(sf::Event::TextEvent event); // called when text is entered (via the keyboard) - we probably won't need this
private:
    InputTracker input; // used to keep track of the current state of input devices
    sf::RenderWindow *window; // used to find information about the current window and to draw to the current window
    std::string myUserName = ""; // is set to the username of this client
    std::unordered_map<std::string, ClientPlayer> players; // a hashtable of all the players
    std::vector<std::vector<std::string>> teams; // a list of teams - each team is a list of usernames
    
    
    void updateWorld(std::string messageFromServer, long long timeStamp);
    
    
    // Premade Methods
    long long getTime(); // get the current time in milliseconsd
    std::vector<std::string> split(const std::string s, char delim); // splits a string; EX: split("Alice is cool.", ' ') --> ["Alice", "is", "cool"]
    void loadPlayers(std::string teamsString); // loads the players given at the start of the game into the players hash-table and the teams list
    
    
    
    // Ignore Me
    AppBaseClass *parentApp;
};

#endif /* defined(__GameTemplate__ClientGame__) */
