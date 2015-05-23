//
//  TimeTracker.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/23/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "TimeTracker.h"

TimeTracker::TimeTracker(ServerBaseClass &serverBaseClass) {
    parentApp = &serverBaseClass;
}

void TimeTracker::start(std::vector<std::string>usernames) {
    users.clear();
    for(int i=0; i<usernames.size(); i++) {
        users.push_back(TimeTrackerClient());
        users[i].username = usernames[i];
    }
    timeOfLastFrame = getTime();
}

long long TimeTracker::getClientTime(std::string username) {
    for(int i=0; i<users.size(); i++) {
        if(users[i].username == username) {
            if(users[i].serverFromStamps.size() == 0) {
                // we don't have any PING data, so we assume that their time is equal to ours
                return getTime();
            }
            std::vector<long long> diffs;
            for(int j=0; j<users[i].serverFromStamps.size(); j++) {
                diffs.push_back(users[i].clientStamps[j] - (users[i].serverFromStamps[j]+users[i].serverToStamps[j])/2);
            }
            long long median = findMedian(diffs);
            return getTime() + median;
        }
    }
    return 0;
}

long long TimeTracker::fromClientTimeToServerTime(long long clientTime, std::string username) {
    for(int i=0; i<users.size(); i++) {
        if(users[i].username == username) {
            if(users[i].serverFromStamps.size() == 0) {
                // we don't have any PING data, so we assume that their time is equal to ours
                return getTime();
            }
            std::vector<long long> diffs;
            for(int j=0; j<users[i].serverFromStamps.size(); j++) {
                diffs.push_back(users[i].clientStamps[j] - (users[i].serverFromStamps[j]+users[i].serverToStamps[j])/2);
            }
            long long median = findMedian(diffs);
            return clientTime - median;
        }
    }
    return 0;
}

long long TimeTracker::findMedian(std::vector<long long> arr) {
    long long median;
    size_t size = arr.size();
    sort(arr.begin(), arr.end());
    if(size%2 == 0) {
        median = (arr[size / 2 - 1] + arr[size / 2]) / 2;
    }
    else {
        median = arr[size / 2];
    }
    return median;
}

void TimeTracker::update() {
    if(users.size() == 0) {
        return;
    }
    
    if(getTime()-users[clientNum].timeOfLastMessageSent > 1000) {
        // its been too long since we've sent a PING
        users[clientNum].timeOfLastMessageSent = getTime();
        std::string message = "PING\n" + std::to_string(getTime());
        parentApp->sendTcpMessage(message, users[clientNum].username);
    }
    clientNum = (clientNum+1)%users.size();
    
    deltaTime = getTime() - timeOfLastFrame;
    timeOfLastFrame = getTime();
}

long long TimeTracker::getDeltaTime() {
    return deltaTime;
}

void TimeTracker::receivedMesage(std::string message, std::string username) {
    std::vector<std::string> arr = split(message, '\n');
    if(arr.size() != 3) {
        return;
    }
    for(int i=0; i<users.size(); i++) {
        if(users[i].username == username) {
            users[i].serverFromStamps.push_back(stoll(arr[1]));
            users[i].clientStamps.push_back(stoll(arr[2]));
            users[i].serverToStamps.push_back(getTime());
            if(users[i].serverFromStamps.size() > 20) {
                users[i].serverFromStamps.erase(users[i].serverFromStamps.begin(), users[i].serverFromStamps.begin()+1);
                users[i].clientStamps.erase(users[i].clientStamps.begin(), users[i].clientStamps.begin()+1);
                users[i].serverToStamps.erase(users[i].serverToStamps.begin(), users[i].serverToStamps.begin()+1);
            }
            return;
        }
    }
}

long long TimeTracker::getTime() {
    return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::vector<std::string> TimeTracker::split(const std::string s, char delim) {
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