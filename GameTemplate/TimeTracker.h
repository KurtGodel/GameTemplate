//
//  TimeTracker.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/23/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__TimeTracker__
#define __GameTemplate__TimeTracker__

#include <stdio.h>

#include <stdio.h>
#include <chrono>
#include <vector>
#include <sstream>
#include "ServerBaseClass.h"
#include "TimeTrackerClient.h"

class TimeTracker {
public:
    TimeTracker(ServerBaseClass &serverBaseClass);
    void start(std::vector<std::string>usernames);
    void update();
    void receivedMesage(std::string message, std::string username);
    long long getClientTime(std::string username);
    long long fromClientTimeToServerTime(long long clientTime, std::string username);
    long long getDeltaTime();
private:
    ServerBaseClass *parentApp;
    std::vector<TimeTrackerClient> users;
    int clientNum = 0;
    
    long long getTime();
    std::vector<std::string> split(const std::string s, char delim);
    long long findMedian(std::vector<long long> arr);
    
    long long timeOfLastFrame = 0;
    long long deltaTime = 0;
};

#endif /* defined(__GameTemplate__TimeTracker__) */
