//
//  MainMenu.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow &w, AppBaseClass &app) : usernameTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 50)), serverIpTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), portTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), chatTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 50)) {
    window = &w;
    parentApp = &app;
    if(!buttonTexture.loadFromFile(resourcePath() + "button.png")) {
        std::cout << "Error: Main Menu failed to load button texture";
        w.close();
        return;
    }
    
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        std::cout << "Error: Main Menu failed to load font";
        w.close();
        return;
    }
    
    
    sf::Vector2u screenSize = window->getSize();
    
    // Home
    pages.push_back(MenuPage());
    pages[0].labels.push_back(sf::Text("Home Page", font, 100));
    sf::FloatRect rect = pages[0].labels[0].getGlobalBounds();
    pages[0].labels[0].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.x/10.0);
    pages[0].buttons.push_back(MenuButton("Multiplayer Server", &buttonTexture, &font));
    pages[0].buttons[0].size = screenSize.x/3.0;
    pages[0].buttons[0].center(screenSize);
    pages[0].buttons[0].y += 2.0*screenSize.x/15.0;
    pages[0].buttons.push_back(MenuButton("Multiplayer Client", &buttonTexture, &font));
    pages[0].buttons[1].size = screenSize.x/3.0;
    pages[0].buttons[1].center(screenSize);
    pages[0].buttons[1].y += screenSize.x/15.0;
    pages[0].buttons.push_back(MenuButton("Single Player", &buttonTexture, &font));
    pages[0].buttons[2].size = screenSize.x/3.0;
    pages[0].buttons[2].center(screenSize);
    
    // Multiplayer Client
    pages.push_back(MenuPage());
    pages[1].labels.push_back(sf::Text("Multiplayer Client", font, 100));
    rect = pages[1].labels[0].getGlobalBounds();
    pages[1].labels[0].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.x/10.0);
    pages[1].buttons.push_back(MenuButton("Back", &buttonTexture, &font));
    pages[1].buttons[0].size = screenSize.x/3.0;
    pages[1].buttons[0].x = 0;
    pages[1].buttons[0].y = 0;
    pages[1].buttons.push_back(MenuButton("Sign In", &buttonTexture, &font));
    pages[1].buttons[1].size = screenSize.x/3.0;
    pages[1].buttons[1].center(screenSize);
    pages[1].buttons[1].y += screenSize.x/15.0 * 3.0;
    
    pages[1].labels.push_back(sf::Text("Username:", font, 50));
    rect = pages[1].labels[1].getGlobalBounds();
    pages[1].labels[1].setPosition(0.0, screenSize.y/2.0 - screenSize.x/15.0 - 30);
    usernameTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    usernameTextBox.center(screenSize);
    usernameTextBox.setPosition(usernameTextBox.getPosition().x, usernameTextBox.getPosition().y - screenSize.x/15.0);
    serverIpTextBox.maxCharacterLength = 10;
    
    pages[1].labels.push_back(sf::Text("Server IP:", font, 50));
    rect = pages[1].labels[2].getGlobalBounds();
    pages[1].labels[2].setPosition(0.0, screenSize.y/2.0 - 30);
    serverIpTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    serverIpTextBox.center(screenSize);
    serverIpTextBox.maxCharacterLength = 20;
    
    pages[1].labels.push_back(sf::Text("Server Port:", font, 50));
    rect = pages[1].labels[3].getGlobalBounds();
    pages[1].labels[3].setPosition(0.0, screenSize.y/2.0 + screenSize.x/15.0 - 30);
    portTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    portTextBox.center(screenSize);
    portTextBox.setPosition(portTextBox.getPosition().x, portTextBox.getPosition().y + screenSize.x/15.0);
    portTextBox.maxCharacterLength = 5;
    
    pages[1].labels.push_back(sf::Text("", font, 30));
    rect = pages[1].labels[4].getGlobalBounds();
    pages[1].labels[4].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.y - 50);
    
    // Single Player
    pages.push_back(MenuPage());
    pages[2].labels.push_back(sf::Text("Single Player", font, 100));
    rect = pages[2].labels[0].getGlobalBounds();
    pages[2].labels[0].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.x/10.0);
    pages[2].buttons.push_back(MenuButton("Back", &buttonTexture, &font));
    pages[2].buttons[0].size = screenSize.x/3.0;
    pages[2].buttons[0].x = 0;
    pages[2].buttons[0].y = 0;
    
    // Multiplayer Server
    pages.push_back(MenuPage());
    pages[3].labels.push_back(sf::Text("Multiplayer Server", font, 100));
    rect = pages[3].labels[0].getGlobalBounds();
    pages[3].labels[0].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.x/10.0);
    pages[3].buttons.push_back(MenuButton("Back", &buttonTexture, &font));
    pages[3].buttons[0].size = screenSize.x/3.0;
    pages[3].buttons[0].x = 0;
    pages[3].buttons[0].y = 0;
    pages[3].labels.push_back(sf::Text("Server IP: ???.???.???.???", font, 50));
    rect = pages[3].labels[1].getGlobalBounds();
    pages[3].labels[1].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.y/2 - rect.height/2.0);
    pages[3].labels.push_back(sf::Text("Server Port: ?????", font, 50));
    rect = pages[3].labels[2].getGlobalBounds();
    pages[3].labels[2].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.y/2 - rect.height/2.0 + 60.0);
    pages[3].buttons.push_back(MenuButton("Matchmaking", &buttonTexture, &font));
    pages[3].buttons[1].center(screenSize);
    pages[3].buttons[1].y += rect.height/2.0 + 120;
    
    // Matchmaking
    pages.push_back(MenuPage());
    pages[4].labels.push_back(sf::Text("Matchmaking (C)", font, 100));
    rect = pages[4].labels[0].getGlobalBounds();
    pages[4].labels[0].setPosition(screenSize.x/3.0 - rect.width/2.0, screenSize.x/10.0);
    pages[4].buttons.push_back(MenuButton("Log Out", &buttonTexture, &font));
    pages[4].buttons[0].size = screenSize.x/3.0;
    pages[4].buttons[0].x = 0;
    pages[4].buttons[0].y = 0;
    chatTextBox.setSize(0.25*screenSize.x, screenSize.x/40.0);
    chatTextBox.setPosition(0.875*screenSize.x, screenSize.y - screenSize.x/80.0);
    chatTextBox.maxCharacterLength = 20;
    
    pages[4].buttons.push_back(MenuButton("No Team", &buttonTexture, &font));
    pages[4].buttons[1].size = 200;
    pages[4].buttons[1].x = 50;
    pages[4].buttons[1].y = screenSize.y/2.0;
    pages[4].buttons.push_back(MenuButton("Team 1", &buttonTexture, &font));
    pages[4].buttons[2].size = 200;
    pages[4].buttons[2].x = 300;
    pages[4].buttons[2].y = screenSize.y/2.0;
    pages[4].buttons.push_back(MenuButton("Team 2", &buttonTexture, &font));
    pages[4].buttons[3].size = 200;
    pages[4].buttons[3].x = 550;
    pages[4].buttons[3].y = screenSize.y/2.0;
    pages[4].labels.push_back(sf::Text("A...", font, 16));
    pages[4].labels[1].setPosition(50, screenSize.y/2.0+40.0);
    pages[4].labels.push_back(sf::Text("B...", font, 16));
    pages[4].labels[2].setPosition(300, screenSize.y/2.0+40.0);
    pages[4].labels.push_back(sf::Text("C...", font, 16));
    pages[4].labels[3].setPosition(550, screenSize.y/2.0+40.0);
    
    // delete me and the corresponding functionality when game is launched
    pages[4].buttons.push_back(MenuButton("Launch Game", &buttonTexture, &font));
    pages[4].buttons[4].center(screenSize);
    pages[4].buttons[4].y -= 100;
    
    pages[4].labels.push_back(sf::Text("", font, 16));
    
    
    // Matchmaking (S)
    pages.push_back(MenuPage());
    pages[5].labels.push_back(sf::Text("Matchmaking (S)", font, 100));
    rect = pages[5].labels[0].getGlobalBounds();
    pages[5].labels[0].setPosition(screenSize.x/3.0 - rect.width/2.0, screenSize.x/10.0);
    pages[5].buttons.push_back(MenuButton("Back", &buttonTexture, &font));
    pages[5].buttons[0].size = screenSize.x/3.0;
    pages[5].buttons[0].x = 0;
    pages[5].buttons[0].y = 0;
    
    pages[5].buttons.push_back(MenuButton("No Team", &buttonTexture, &font));
    pages[5].buttons[1].size = 200;
    pages[5].buttons[1].x = 50;
    pages[5].buttons[1].y = screenSize.y/2.0;
    pages[5].buttons.push_back(MenuButton("Team 1", &buttonTexture, &font));
    pages[5].buttons[2].size = 200;
    pages[5].buttons[2].x = 300;
    pages[5].buttons[2].y = screenSize.y/2.0;
    pages[5].buttons.push_back(MenuButton("Team 2", &buttonTexture, &font));
    pages[5].buttons[3].size = 200;
    pages[5].buttons[3].x = 550;
    pages[5].buttons[3].y = screenSize.y/2.0;
    pages[5].labels.push_back(sf::Text("A...", font, 16));
    pages[5].labels[1].setPosition(50, screenSize.y/2.0+40.0);
    pages[5].labels.push_back(sf::Text("B...", font, 16));
    pages[5].labels[2].setPosition(300, screenSize.y/2.0+40.0);
    pages[5].labels.push_back(sf::Text("C...", font, 16));
    pages[5].labels[3].setPosition(550, screenSize.y/2.0+40.0);
    
    pages[5].buttons.push_back(MenuButton("Launch Game", &buttonTexture, &font));
    pages[5].buttons[4].center(screenSize);
    pages[5].buttons[4].y -= 100;
    
    pages[5].labels.push_back(sf::Text("", font, 16));
    
}

void MainMenu::think() {
    if(pageNum == MainMenuPageName_MultiplayerServer) {
        std::string ip = sf::IpAddress::getLocalAddress().toString();
        pages[3].labels[1].setString("IP: " + ip);
        
        std::string portNum = parentApp->sendMeMessage("get my server tcp port");
        pages[3].labels[2].setString("TCP Port: " + portNum);
    }
}

void MainMenu::draw() {
    for(int i=0; i<pages[pageNum].buttons.size(); i++) {
        pages[pageNum].buttons[i].draw(window);
    }
    for(int i=0; i<pages[pageNum].labels.size(); i++) {
        window->draw(pages[pageNum].labels[i]);
    }
    
    if(pageNum == MainMenuPageName_MultiplayerClient) {
        usernameTextBox.render(window);
        serverIpTextBox.render(window);
        portTextBox.render(window);
    }
    else {
        usernameTextBox.unfocus();
        serverIpTextBox.unfocus();
        portTextBox.unfocus();
    }
    
    if(pageNum == MainMenuPageName_Matchmaking || pageNum == MainMenuPageName_ServerMatchmaking) {
        chatTextBox.render(window);
    }
    else {
        chatTextBox.unfocus();
    }
    
    frameCounter++;
}

void MainMenu::mouseMove(sf::Event::MouseMoveEvent event) {
}

void MainMenu::mouseDown(sf::Event::MouseButtonEvent event) {
    float x = event.x;
    float y = event.y;
    for(int i=0; i<pages[pageNum].buttons.size(); i++) {
        if(x > pages[pageNum].buttons[i].x && x < pages[pageNum].buttons[i].x + pages[pageNum].buttons[i].size && y > pages[pageNum].buttons[i].y && y < pages[pageNum].buttons[i].y + pages[pageNum].buttons[i].size*pages[pageNum].buttons[i].textureHeight/pages[pageNum].buttons[i].textureWidth) {
            buttonClicked(i);
            break;
        }
    }
    if(pageNum == MainMenuPageName_MultiplayerClient) {
        usernameTextBox.mouseButtonPressed(event);
        serverIpTextBox.mouseButtonPressed(event);
        portTextBox.mouseButtonPressed(event);
    }
    else if(pageNum == MainMenuPageName_Matchmaking || pageNum == MainMenuPageName_ServerMatchmaking) {
        chatTextBox.mouseButtonPressed(event);
    }
}

void MainMenu::buttonClicked(int index) {
    if(pageNum == MainMenuPageName_Home) {
        if(pages[pageNum].buttons[index].label == "Multiplayer Client") {
            pageNum = MainMenuPageName_MultiplayerClient;
        }
        else if(pages[pageNum].buttons[index].label == "Single Player") {
            pageNum = MainMenuPageName_SinglePlayer;
        }
        else if(pages[pageNum].buttons[index].label == "Multiplayer Server") {
            pageNum = MainMenuPageName_MultiplayerServer;
        }
    }
    else if(pageNum == MainMenuPageName_MultiplayerClient) {
        if(pages[pageNum].buttons[index].label == "Back") {
            pageNum = MainMenuPageName_Home;
        }
        else if(pages[pageNum].buttons[index].label == "Sign In") {
            pages[1].labels[4].setString("Connecting...");
            parentApp->sendMeMessage("Login To Server\n" + usernameTextBox.getValue() + "\n" + serverIpTextBox.getValue() + "\n" + portTextBox.getValue());
        }
    }
    else if(pageNum == MainMenuPageName_SinglePlayer) {
        if(pages[pageNum].buttons[index].label == "Back") {
            pageNum = MainMenuPageName_Home;
        }
    }
    else if(pageNum == MainMenuPageName_MultiplayerServer) {
        if(pages[pageNum].buttons[index].label == "Back") {
            pageNum = MainMenuPageName_Home;
        }
        else if(pages[pageNum].buttons[index].label == "Matchmaking") {
            pageNum = MainMenuPageName_ServerMatchmaking;
        }
    }
    else if(pageNum == MainMenuPageName_Matchmaking) {
        if(pages[pageNum].buttons[index].label == "Log Out") {
            pageNum = MainMenuPageName_Home;
            parentApp->sendMeMessage("Log Out");
        }
        else if(pages[pageNum].buttons[index].label == "No Team") {
            parentApp->sendMeMessage("No Team");
        }
        else if(pages[pageNum].buttons[index].label == "Team 1") {
            parentApp->sendMeMessage("Team 1");
        }
        else if(pages[pageNum].buttons[index].label == "Team 2") {
            parentApp->sendMeMessage("Team 2");
        }
        else if(pages[pageNum].buttons[index].label == "Launch Game") {
            // delete this entire "else-if" block when game is launched
            parentApp->sendMeMessage("Launch Game");
        }
    }
    else if(pageNum == MainMenuPageName_ServerMatchmaking) {
        if(pages[pageNum].buttons[index].label == "Back") {
            pageNum = MainMenuPageName_MultiplayerServer;
        }
        else if(pages[pageNum].buttons[index].label == "No Team") {
            parentApp->sendMeMessage("No Team");
        }
        else if(pages[pageNum].buttons[index].label == "Team 1") {
            parentApp->sendMeMessage("Team 1");
        }
        else if(pages[pageNum].buttons[index].label == "Team 2") {
            parentApp->sendMeMessage("Team 2");
        }
        else if(pages[pageNum].buttons[index].label == "Launch Game") {
            parentApp->sendMeMessage("Launch Game");
        }
    }
}

void MainMenu::mouseUp(sf::Event::MouseButtonEvent event) {
}

void MainMenu::keyDown(sf::Event::KeyEvent event) {
    if(pageNum == MainMenuPageName_MultiplayerClient) {
        usernameTextBox.keyPressed(event);
        serverIpTextBox.keyPressed(event);
        portTextBox.keyPressed(event);
    }
    else if(pageNum == MainMenuPageName_Matchmaking || pageNum == MainMenuPageName_ServerMatchmaking) {
        if(chatTextBox.isFocused() && event.code == 58 && chatTextBox.getValue() != "") {
            // send chat to server
            std::string str = "Chat Message\n" + chatTextBox.getValue();
            parentApp->sendMeMessage(str);
            chatTextBox.setValue("");
        }
        else {
            chatTextBox.keyPressed(event);
        }
    }
}

void MainMenu::keyUp(sf::Event::KeyEvent event) {
}

void MainMenu::textEntered(sf::Event::TextEvent event) {
    if(pageNum == MainMenuPageName_MultiplayerClient) {
        usernameTextBox.textEntered(event.unicode);
        serverIpTextBox.textEntered(event.unicode);
        portTextBox.textEntered(event.unicode);
    }
    else if(pageNum == MainMenuPageName_Matchmaking || pageNum == MainMenuPageName_ServerMatchmaking) {
        chatTextBox.textEntered(event.unicode);
    }
}

void MainMenu::sendMessage(std::string message) {
}

void MainMenu::sendMeResultOfClientConnect(std::string message) {
    if(message == "DID CONNECT") {
        pageNum = MainMenuPageName_Matchmaking;
        pages[1].labels[4].setString("");
    }
    else if(message == "USERNAME NOT UNIQUE") {
        pages[1].labels[4].setString("Username Already in Use.");
    }
    else if(message == "DID NOT CONNECT") {
        pages[1].labels[4].setString("Connection Failed");
    }
    else if(message == "CONNECTING TO SELF") {
        pages[1].labels[4].setString("You Can't Connect to Yourself");
    }
    else {
        // should never happen
    }
}

void MainMenu::updateChat(std::vector<std::string> *chatMessages) {
    // todo
    std::string str = "";
    for(int i=0; i<chatMessages->size(); i++) {
        str += chatMessages->at(i);
        str += "\n";
    }
    if(pageNum == MainMenuPageName_Matchmaking) {
        pages[4].labels[4].setString(str);
        sf::FloatRect rect = pages[4].labels[4].getGlobalBounds();
        sf::Vector2u screenSize = window->getSize();
        pages[4].labels[4].setPosition(0.75*screenSize.x, screenSize.y - screenSize.x/20.0 - rect.height);
    }
    else {
        pages[5].labels[4].setString(str);
        sf::FloatRect rect = pages[5].labels[4].getGlobalBounds();
        sf::Vector2u screenSize = window->getSize();
        pages[5].labels[4].setPosition(0.75*screenSize.x, screenSize.y - screenSize.x/20.0 - rect.height);
    }
}

void MainMenu::updateTeams(std::vector<std::string> *teamList) {
    std::vector<std::string> dup(*teamList);
    std::vector<std::string> noTeam = split(dup[1], '\t');
    std::vector<std::string> team1 = split(dup[2], '\t');
    std::vector<std::string> team2 = split(dup[3], '\t');
    std::string str = "";
    for(int i=0; i<noTeam.size(); i++) {
        if(i != 0) {
            str += "\n";
        }
        str += noTeam[i];
    }
    pages[4].labels[1].setString(str);
    pages[5].labels[1].setString(str);
    str = "";
    for(int i=0; i<team1.size(); i++) {
        if(i != 0) {
            str += "\n";
        }
        str += team1[i];
    }
    pages[4].labels[2].setString(str);
    pages[5].labels[2].setString(str);
    str = "";
    for(int i=0; i<team2.size(); i++) {
        if(i != 0) {
            str += "\n";
        }
        str += team2[i];
    }
    pages[4].labels[3].setString(str);
    pages[5].labels[3].setString(str);
}

std::vector<std::string> MainMenu::split(const std::string s, char delim) {
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
