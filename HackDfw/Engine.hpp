//
//  Engine.hpp
//  HackDfw
//
//  Created by Leelabrindavanan Karunakaran on 4/16/16.
//  Copyright © 2016 Leelabrindavanan Karunakaran. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>

class Engine{
public:
    typedef struct Coordinate_Struct{
        double ground;
        double x,
        y,
        x_dist,
        vx,
        vy,
        ax,
        ay;
        bool up;
        bool right;
        bool left;
        bool down;
        bool air;
    } Coordinate;
    
    Engine();
    
    Coordinate current_Coor;
    
    void cycle();
    
    void calc_accel();
    
    void calc_variables();
    
    double getX();
    
    double getDist();
    
    double getY();
    
    void setUp();
    void setDown();
    void setLeft();
    void setRight();
    
    void clearButton();
};

#endif /* Engine_hpp */
