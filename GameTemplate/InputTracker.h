//
//  InputTracker.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/23/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__InputTracker__
#define __GameTemplate__InputTracker__

#include <stdio.h>
#include <string>

class InputTracker {
public:
    std::string username = "";
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    
    std::string toString();
    bool fromString(std::string str);
    
    long long timeStamp;
private:
    bool charToBool(char c);
};


#endif /* defined(__GameTemplate__InputTracker__) */
