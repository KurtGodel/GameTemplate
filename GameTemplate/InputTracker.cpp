//
//  InputTracker.cpp
//  GameTemplate
//
//  Created by Thomas Redding on 5/23/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#include "InputTracker.h"

std::string InputTracker::toString() {
    std::string rtn = "";
    rtn += std::to_string(up);
    rtn += std::to_string(down);
    rtn += std::to_string(left);
    rtn += std::to_string(right);
    return rtn;
}

bool InputTracker::fromString(std::string str) {
    if(str.length() != 4) {
        return false;
    }
    up = charToBool(str[0]);
    down = charToBool(str[1]);
    left = charToBool(str[2]);
    right = charToBool(str[3]);
}

bool InputTracker::charToBool(char c) {
    if(c == '1') {
        return true;
    }
    else {
        return false;
    }
}
