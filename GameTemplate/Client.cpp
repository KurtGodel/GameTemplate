//
//  Client.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/19/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "Client.h"

Client::Client(ClientServerCommunicator &clientServerCommunicator, ClientCommunicator &clientCommunicator) {
    app = &clientCommunicator;
    server = &clientServerCommunicator;
    tcpSocket.setBlocking(false);
    udpSocket.setBlocking(false);
    udpSocket.bind(sf::Socket::AnyPort);
    app->tcpPortOfLocalServer = server->tcpPortOfLocalServer;
}

Client::~Client() {
    udpSocket.unbind();
    tcpSocket.disconnect();
}

void Client::run() {
    // check connect requests
    app->lock.lock();
    if(app->connectToServerIp.size() > 0 && app->connectToServerTcpPort.size() > 0 && app->connectToServerUsername.size() > 0) {
        username = app->connectToServerUsername[app->connectToServerUsername.size()-1];
        sf::IpAddress addr = app->connectToServerIp[app->connectToServerIp.size()-1];
        unsigned short port = app->connectToServerTcpPort[app->connectToServerTcpPort.size()-1];
        app->connectToServerIp.clear();
        app->connectToServerTcpPort.clear();
        app->connectToServerUsername.clear();
        app->lock.unlock();
        bool didSucceed = connectTcpToServer(addr, port);
        if(didSucceed) {
            // send udp message to server; because we don't know the UDP port of the socket, this will actually send a TCP message requesting a UDP port
            sendUdpMessage("-");
        }
        else {
            if(addr.toString() == "0.0.0.0" || port == 0) {
                // connected to local server
            }
            else {
                // failed to connect to remote server
                app->lock.lock();
                app->tcpMessagesFromServer.push_back("DID NOT CONNECT");
                app->lock.unlock();
            }
        }
    }
    else {
        app->lock.unlock();
    }
    
    // send udp messges to server
    std::vector<std::string> messages;
    app->lock.lock();
    for(int i=0; i<app->udpMessagesToServer.size(); i++) {
        messages.push_back(app->udpMessagesToServer[i]);
    }
    app->udpMessagesToServer.clear();
    app->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        sendUdpMessage(messages[i]);
    }
    messages.clear();
    
    // send tcp messges to server
    app->lock.lock();
    for(int i=0; i<app->tcpMessagesToServer.size(); i++) {
        messages.push_back(app->tcpMessagesToServer[i]);
    }
    app->tcpMessagesToServer.clear();
    app->lock.unlock();
    for(int i=0; i<messages.size(); i++) {
        sendTcpMessage(messages[i]);
    }
    messages.clear();
    
    // check for udp messages from local "server"
    server->lock.lock();
    for(int i=0; i<server->udpMessagesFromServer.size(); i++) {
        messages.push_back(server->udpMessagesFromServer[i]);
    }
    server->udpMessagesFromServer.clear();
    server->lock.unlock();
    app->lock.lock();
    for(int i=0; i<messages.size(); i++) {
        app->udpMessagesFromServer.push_back(messages[i]);
    }
    app->lock.unlock();
    messages.clear();
    
    // check for tcp messages from local "server"
    server->lock.lock();
    for(int i=0; i<server->tcpMessagesFromServer.size(); i++) {
        messages.push_back(server->tcpMessagesFromServer[i]);
    }
    server->tcpMessagesFromServer.clear();
    server->lock.unlock();
    app->lock.lock();
    for(int i=0; i<messages.size(); i++) {
        app->tcpMessagesFromServer.push_back(messages[i]);
    }
    app->lock.unlock();
    messages.clear();
    
    std::string message;
    // check udp messages from remote server
    while(true) {
        char buffer[1024];
        char *begin = buffer;
        char *end = begin + sizeof(buffer);
        std::fill(begin, end, 0);
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;
        udpSocket.receive(buffer, sizeof(buffer), received, sender, port);
        message = std::string(buffer);
        if(message != "") {
            app->lock.lock();
            app->udpMessagesFromServer.push_back(message);
            app->lock.unlock();
        }
        else {
            break;
        }
    }
    
    
    // check tcp messages from remote server
    while(true) {
        sf::Packet packet;
        tcpSocket.receive(packet);
        message = "";
        packet >> message;
        if(message != "") {
            std::vector<std::string> arr = split(message, '\n');
            if(arr.size() == 2 && arr[0] == "Server UDP Port") {
                // finish up connection
                udpPortOfServer = stoi(arr[1]);
                app->lock.lock();
                app->tcpMessagesFromServer.push_back("DID CONNECT");
                app->lock.unlock();
            }
            else if(arr.size() == 3 && arr[0] == "Username Not Unique") {
                // finish up connection
                udpPortOfServer = stoi(arr[1]);
                app->lock.lock();
                app->tcpMessagesFromServer.push_back("USERNAME NOT UNIQUE");
                app->lock.unlock();
            }
            else {
                // pass on to app
                app->lock.lock();
                app->tcpMessagesFromServer.push_back(message);
                app->lock.unlock();
            }
        }
        else {
            break;
        }
    }
    
    // sleep for 10 milliseconds
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = 10;
    tim.tv_nsec *= 1000000;
    nanosleep(&tim , &tim2);
}

std::vector<std::string> Client::split(const std::string s, char delim) {
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

bool Client::connectTcpToServer(sf::IpAddress serverIpAddress, unsigned short serverPort) {
    ipAddressOfServer = "0.0.0.0";
    tcpPortOfServer = 0;
    udpPortOfServer = 0;
        
    tcpSocket.disconnect();
    if(serverIpAddress.toString() == "0.0.0.0" || serverPort == 0) {
        // connect to local "server"
        // i.e. do nothing after setting the above values to 0
        return false;
    }
    else {
        // connect to remote server
        sf::Time waitTime = sf::milliseconds(3000);
        tcpSocket.setBlocking(true);
        sf::Socket::Status status = tcpSocket.connect(serverIpAddress, serverPort, waitTime);
        tcpSocket.setBlocking(false);
        if(status == sf::Socket::Status::Done) {
            // we have successfuly connected to the server
            ipAddressOfServer = tcpSocket.getRemoteAddress();
            tcpPortOfServer = tcpSocket.getRemotePort();
            return true;
        }
        else {
            // a problem occured - disconnect
            if(status == sf::Socket::Status::Error) {
            }
            else if(status == sf::Socket::Status::Disconnected) {
            }
            else if(status == sf::Socket::Status::NotReady) {
            }
            else if(status == sf::Socket::Status::NotReady) {
            }
            return false;
        }
    }
}

void Client::sendTcpMessage(std::string message) {
    if(tcpPortOfServer == 0 || ipAddressOfServer.toString() == "0.0.0.0") {
        // send message to local "server"
        server->lock.lock();
        server->tcpMessagesToServer.push_back(message);
        server->lock.unlock();
    }
    else {
        sf::Packet packet;
        packet << message;
        tcpSocket.send(packet);
    }
}

void Client::sendUdpMessage(std::string message) {
    if(tcpPortOfServer == 0 || ipAddressOfServer.toString() == "0.0.0.0") {
        // send message to local "server"
        server->lock.lock();
        server->udpMessagesToServer.push_back(message);
        server->lock.unlock();
    }
    else {
        // send message to remote server
        if(udpPortOfServer == 0) {
            // we don't know the server port
            /*
             Give UDP Socket
             {username}
            */
            std::string newMessage = "Give UDP Socket\n" + username + "\n" + std::to_string(udpSocket.getLocalPort());
            sf::Packet packet;
            packet << newMessage;
            tcpSocket.send(packet);
        }
        else {
            // we do know the server port
            udpSocket.send(message.c_str(), message.size(), ipAddressOfServer, udpPortOfServer);
        }
    }
}
