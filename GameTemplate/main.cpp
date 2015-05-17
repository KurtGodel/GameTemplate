
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

#include "Client.h"
#include "Server.h"
#include "ServerSocketController.h"
#include "TcpMessageContainer.h"

void* startServer(void* input) {
    Server server(*(TcpMessageContainer*) input);
    while (true) {
        server.baseClassUpdate();
    }
}

void* startServerSocketController(void* input) {
    ServerSocketController serverSocketController(*(TcpMessageContainer*) input);
    serverSocketController.run();
}

int main(int, char const**)
{
    // Create the fullscreen window
    sf::VideoMode oneValidFullscreenMode = sf::VideoMode::getFullscreenModes()[0];
    sf::RenderWindow window(oneValidFullscreenMode, "SFML window", sf::Style::Fullscreen);
    window.setFramerateLimit(20);

    // Set the Icon
    sf::Image icon;
    if(!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    TcpMessageContainer tcpMessageContainer;
    
    pthread_t startServerSocketControllerThread;
    pthread_create(&startServerSocketControllerThread, NULL, startServerSocketController, (void *)(&tcpMessageContainer));
    
    // wait 0.1 seconds for the server to be set up
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 100000;
    tim.tv_nsec *= 1000;
    nanosleep(&tim , &tim2);
    
    pthread_t serverThread;
    pthread_create(&serverThread, NULL, startServer, (void *)(&tcpMessageContainer));
    
    // wait 0.1 seconds for the server to be set up
    nanosleep(&tim , &tim2);
    
    Client client(window);
    
    // Start the game loop
    while(window.isOpen())
    {
        if(tcpMessageContainer.startClosing >= 2) {
            window.close();
        }
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) {
                tcpMessageContainer.startClosing = 1;
            }
            else if(event.type == sf::Event::MouseMoved) {
                client.mouseMove(event.mouseMove);
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                client.mouseDown(event.mouseButton);
            }
            else if(event.type == sf::Event::MouseButtonReleased) {
                client.mouseUp(event.mouseButton);
            }
            else if(event.type == sf::Event::KeyPressed) {
                client.keyDown(event.key);
            }
            else if(event.type == sf::Event::KeyReleased) {
                client.keyUp(event.key);
            }
            else if(event.type == sf::Event::TextEntered) {
                client.textEntered(event.text);
            }
        }
        
        // check for messages from server
        client.checkForReceivedSocketMessages();
        
        // do calculations
        client.think();

        // Clear screen
        window.clear();
        
        // Render screen
        client.draw();

        // Update the window
        window.display();
    }
    
    return EXIT_SUCCESS;
}
