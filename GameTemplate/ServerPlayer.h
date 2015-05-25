//
//  ServerPlayer.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/25/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__ServerPlayer__
#define __GameTemplate__ServerPlayer__

#include <stdio.h>
#include "InputTracker.h"
struct ServerPlayer {
    double x = 0;
    double y = 0;
    InputTracker input;
};

#endif /* defined(__GameTemplate__ServerPlayer__) */
