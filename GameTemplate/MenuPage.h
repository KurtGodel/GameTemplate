//
//  MenuPage.h
//  GameTemplate
//
//  Created by Thomas Redding on 5/15/15.
//  Copyright (c) 2015 Thomas Redding. All rights reserved.
//

#ifndef __GameTemplate__MenuPage__
#define __GameTemplate__MenuPage__

#include <stdio.h>

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "ResourcePath.hpp"
#include "MenuButton.h"

class MenuPage {
public:
    MenuPage();
    std::string name;
    std::vector<MenuButton> buttons;
    std::vector<sf::Text> labels;
};

#endif /* defined(__GameTemplate__MenuPage__) */
