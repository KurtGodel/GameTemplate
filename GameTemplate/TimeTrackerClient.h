//
//  TimeTrackerClient.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/23/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__TimeTrackerClient__
#define __GameTemplate__TimeTrackerClient__

#include <stdio.h>

struct TimeTrackerClient {
public:
    std::string username;
    long long timeOfLastMessageSent = -1;
    std::vector<long long>serverFromStamps;
    std::vector<long long>serverToStamps;
    std::vector<long long>clientStamps;
};

#endif /* defined(__GameTemplate__TimeTrackerClient__) */
