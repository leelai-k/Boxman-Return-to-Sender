//
//  Group.hpp
//  HackDfw
//
//  Created by Leelabrindavanan Karunakaran on 4/16/16.
//  Copyright © 2016 Leelabrindavanan Karunakaran. All rights reserved.
//

#ifndef GROUP_INCLUDED_HPP
#define GROUP_INCLUDED_HPP

#include <SFML/Graphics.hpp>

class Group : public sf::Drawable, public std::vector<sf::Drawable*> {
public:
    Group();
    ~Group();
    
    void render(sf::RenderTarget&);
};

#endif /* Group_hpp */
