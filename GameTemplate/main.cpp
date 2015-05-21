
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include "App.h"
#include "TcpHandler.h"
#include "Client.h"
#include "Server.h"

struct ClientServerTcpCommunicatorPair {
    ClientServerCommunicator *clientServerCommunicator;
    TcpHandlerCommunicator *tcpHandlerCommunicator;
};

struct ClientServerCommunicatorPair {
    ClientServerCommunicator *clientServerCommunicator;
    ClientCommunicator *clientCommunicator;
};

void* startServerThread(void* input) {
    ClientServerTcpCommunicatorPair *clientServerTcpCommunicatorPair = (ClientServerTcpCommunicatorPair*) input;
    Server server(*clientServerTcpCommunicatorPair->tcpHandlerCommunicator, *clientServerTcpCommunicatorPair->clientServerCommunicator);
    while (true) {
        server.checkNetworkForMessages();
        server.run();
    }
}

void* startClientThread(void* input) {
    ClientServerCommunicatorPair *clientServerCommunicatorPair = (ClientServerCommunicatorPair*) input;
    Client client(*clientServerCommunicatorPair->clientServerCommunicator, *clientServerCommunicatorPair->clientCommunicator);
    while (true) {
        client.run();
    }
}

void* startTcpListenerThread(void* input) {
    TcpHandler tcpHandler(*(TcpHandlerCommunicator*) input);
    while (true) {
        tcpHandler.run();
    }
}

int main(int, char const**)
{
    // Create the fullscreen window
    sf::VideoMode oneValidFullscreenMode = sf::VideoMode::getFullscreenModes()[0];
    sf::RenderWindow window(oneValidFullscreenMode, "SFML window", sf::Style::Fullscreen);
    window.setFramerateLimit(10);

    // Set the Icon
    sf::Image icon;
    if(!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    TcpHandlerCommunicator tcpHandlerCommunicator;
    ClientCommunicator clientCommunicator;
    ClientServerCommunicator clientServerCommunicator;
    ClientServerTcpCommunicatorPair clientServerTcpCommunicatorPair;
    clientServerTcpCommunicatorPair.clientServerCommunicator = &clientServerCommunicator;
    clientServerTcpCommunicatorPair.tcpHandlerCommunicator = &tcpHandlerCommunicator;
    ClientServerCommunicatorPair clientServerCommunicatorPair;
    clientServerCommunicatorPair.clientCommunicator = &clientCommunicator;
    clientServerCommunicatorPair.clientServerCommunicator = &clientServerCommunicator;
    
    
    pthread_t tcpListenerThread;
    pthread_create(&tcpListenerThread, NULL, startTcpListenerThread, (void *)(&tcpHandlerCommunicator));
    
    pthread_t serverThread;
    pthread_create(&serverThread, NULL, startServerThread, (void *)(&clientServerTcpCommunicatorPair));
    
    pthread_t clientThread;
    pthread_create(&clientThread, NULL, startClientThread, (void *)(&clientServerCommunicatorPair));
    
    App app(window, clientCommunicator);
    
    // special font
    sf::Font font;
    if(!font.loadFromFile(resourcePath() + "cmunrm.ttf")) {
        window.close();
    }
    
    std::string debugStr = "";
    
    // Start the game loop
    while(window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::MouseMoved) {
                app.mouseMove(event.mouseMove);
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                app.mouseDown(event.mouseButton);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                app.mouseUp(event.mouseButton);
            }
            else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Key::Space) {
                    int q = 42;
                    q = 17;
                    
                    q = 19;
                    q = 8;
                    int r = 19;
                    r = q+5;
                }
                app.keyDown(event.key);
            }
            else if(event.type == sf::Event::KeyReleased) {
                app.keyUp(event.key);
            }
            else if(event.type == sf::Event::TextEntered) {
                app.textEntered(event.text);
            }
        }
        
        // syncronize threads
        app.checkNetworkForMessages();
        
        // do calculation
        app.think();

        // Clear screen
        window.clear();
        
        // Render screen
        app.draw();
        
        std::vector<std::string>toPrint;
        tcpHandlerCommunicator.lock.lock();
        for(int i=0; i<tcpHandlerCommunicator.debug.size(); i++) {
            toPrint.push_back(tcpHandlerCommunicator.debug[i]);
        }
        tcpHandlerCommunicator.debug.clear();
        tcpHandlerCommunicator.lock.unlock();
        
        clientServerCommunicator.lock.lock();
        for(int i=0; i<clientServerCommunicator.debug.size(); i++) {
            toPrint.push_back(clientServerCommunicator.debug[i]);
        }
        clientServerCommunicator.debug.clear();
        clientServerCommunicator.lock.unlock();
        
        clientCommunicator.lock.lock();
        for(int i=0; i<clientCommunicator.debug.size(); i++) {
            toPrint.push_back(clientCommunicator.debug[i]);
        }
        clientCommunicator.debug.clear();
        clientCommunicator.lock.unlock();
        
        // print stuff
        int numOfItems = toPrint.size();
        if(numOfItems > 10) {
            numOfItems = 10;
        }
        for(int i=0; i<numOfItems; i++) {
            debugStr += toPrint[i] + "\n";
            std::cout << toPrint[i] << "\n";
        }
        sf::Text text(debugStr, font, 16);
        text.setColor(sf::Color::Red);
        window.draw(text);
        
        // Update the window
        window.display();
    }
    
    pthread_cancel(clientThread);
    pthread_cancel(serverThread);
    pthread_cancel(tcpListenerThread);
    
    return EXIT_SUCCESS;
}
