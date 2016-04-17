//
//  Group.cpp
//  HackDfw
//
//  Created by Leelabrindavanan Karunakaran on 4/16/16.
//  Copyright © 2016 Leelabrindavanan Karunakaran. All rights reserved.
//

#include "Group.hpp"

Group::Group() :
sf::Drawable(),
std::vector<sf::Drawable*>() {
}
Group::~Group() {
    for(std::vector<sf::Drawable*>::iterator i = begin(); i != end(); ++i) {
        delete *i;
    }
}

// This is what ables you to do Group.Draw() to draw all the Drawable inside of a Group,
// and to apply common settings such as position, color, ... to its elements.
void Group::render(sf::RenderTarget& Tar) {
    for(std::vector<sf::Drawable*>::iterator i = begin(); i != end(); ++i) {
        Tar.draw(**i);
    }
}