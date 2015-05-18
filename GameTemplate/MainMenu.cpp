//
//  MainMenu.cpp
//  TacticalWarfare
//
//  Created by Thomas Redding on 5/5/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow &w) : usernameTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 50)), serverIpTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), portTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), udpPortTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2) {
    std::cout << "Error: Main Menu not constructed with access to parent app";
    w.close();
}

MainMenu::MainMenu(sf::RenderWindow &w, ClientBaseClass* parentApp) : usernameTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 50)), serverIpTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), portTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2), udpPortTextBox(&font, sf::Vector2f(0, 0), sf::Vector2f(100, 30), 2) {
    window = &w;
    app = parentApp;
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
    
    pages[1].labels.push_back(sf::Text("Ser. TCP Port:", font, 50));
    rect = pages[1].labels[3].getGlobalBounds();
    pages[1].labels[3].setPosition(0.0, screenSize.y/2.0 + screenSize.x/15.0 - 30);
    portTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    portTextBox.center(screenSize);
    portTextBox.setPosition(portTextBox.getPosition().x, portTextBox.getPosition().y + screenSize.x/15.0);
    portTextBox.maxCharacterLength = 5;
    
    pages[1].labels.push_back(sf::Text("Ser. UDP Port:", font, 50));
    rect = pages[1].labels[4].getGlobalBounds();
    pages[1].labels[4].setPosition(0.0, screenSize.y/2.0 + 2.0 * screenSize.x/15.0 - 30);
    udpPortTextBox.setSize(screenSize.x/2.0, screenSize.x/20.0);
    udpPortTextBox.center(screenSize);
    udpPortTextBox.setPosition(udpPortTextBox.getPosition().x, udpPortTextBox.getPosition().y + 2.0 * screenSize.x/15.0);
    udpPortTextBox.maxCharacterLength = 5;
    
    // Single Player
    pages.push_back(MenuPage());
    pages[2].labels.push_back(sf::Text("Single Player", font, 100));
    rect = pages[2].labels[0].getGlobalBounds();
    pages[2].labels[0].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.x/10.0);
    pages[2].buttons.push_back(MenuButton("Back", &buttonTexture, &font));
    pages[2].buttons[0].size = screenSize.x/3.0;
    pages[2].buttons[0].x = 0;
    pages[2].buttons[0].y = 0;
    
    //Multiplayer Server
    pages.push_back(MenuPage());
    pages[3].labels.push_back(sf::Text("Multiplayer Server", font, 100));
    rect = pages[3].labels[0].getGlobalBounds();
    pages[3].labels[0].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.x/10.0);
    pages[3].buttons.push_back(MenuButton("Back", &buttonTexture, &font));
    pages[3].buttons[0].size = screenSize.x/3.0;
    pages[3].buttons[0].x = 0;
    pages[3].buttons[0].y = 0;
    pages[3].labels.push_back(sf::Text("IP: ???.???.???.???", font, 50));
    rect = pages[3].labels[1].getGlobalBounds();
    pages[3].labels[1].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.y/2 - rect.height/2.0);
    pages[3].labels.push_back(sf::Text("TCP Port: ?????", font, 50));
    rect = pages[3].labels[2].getGlobalBounds();
    pages[3].labels[2].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.y/2 - rect.height/2.0 + 60.0);
    pages[3].labels.push_back(sf::Text("UDP Port: ?????", font, 50));
    rect = pages[3].labels[3].getGlobalBounds();
    pages[3].labels[3].setPosition(screenSize.x/2.0 - rect.width/2.0, screenSize.y/2 - rect.height/2.0 + 120.0);
}

void MainMenu::think() {
    if(pageNum == MainMenuPageName_MultiplayerServer) {
        std::string ip = sf::IpAddress::getLocalAddress().toString();
        pages[3].labels[1].setString("IP: " + ip);
        
        std::string portNum = app->sendMeMessage("get my server port");
        pages[3].labels[2].setString("TCP Port: " + portNum);
        
        portNum = app->sendMeMessage("get my server udp port");
        pages[3].labels[3].setString("UDP Port: " + portNum);
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
        udpPortTextBox.render(window);
    }
    else {
        usernameTextBox.unfocus();
        serverIpTextBox.unfocus();
        portTextBox.unfocus();
        udpPortTextBox.unfocus();
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
        udpPortTextBox.mouseButtonPressed(event);
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
            app->sendMeMessage("Login To Server\n" + usernameTextBox.getValue() + "\n" + serverIpTextBox.getValue() + "\n" + portTextBox.getValue());
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
    }
}

void MainMenu::mouseUp(sf::Event::MouseButtonEvent event) {
}

void MainMenu::keyDown(sf::Event::KeyEvent event) {
    if(pageNum == MainMenuPageName_MultiplayerClient) {
        usernameTextBox.keyPressed(event);
        serverIpTextBox.keyPressed(event);
        portTextBox.keyPressed(event);
        udpPortTextBox.keyPressed(event);
    }
}

void MainMenu::keyUp(sf::Event::KeyEvent event) {
}

void MainMenu::textEntered(sf::Event::TextEvent event) {
    if(pageNum == MainMenuPageName_MultiplayerClient) {
        usernameTextBox.textEntered(event.unicode);
        serverIpTextBox.textEntered(event.unicode);
        portTextBox.textEntered(event.unicode);
        udpPortTextBox.textEntered(event.unicode);
    }
}

void MainMenu::sendMessage(std::string message) {
}
