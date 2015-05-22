//
//  StaticGameState.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/21/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__StaticGameState__
#define __GameTemplate__StaticGameState__

#include <stdio.h>
#include <vector>
#include <SFML/Graphics.hpp>

struct StaticGameState {
    std::vector<sf::Vector2f> backgroundCircles;
};

#endif /* defined(__GameTemplate__StaticGameState__) */
