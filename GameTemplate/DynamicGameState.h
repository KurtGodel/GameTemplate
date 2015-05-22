//
//  DynamicGameState.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__DynamicGameState__
#define __GameTemplate__DynamicGameState__

#include <stdio.h>
#include <SFML/Graphics.hpp>

struct DynamicGameState {
    long long timeStamp;
    std::vector<sf::Vector2f> players;
};

#endif /* defined(__GameTemplate__DynamicGameState__) */
