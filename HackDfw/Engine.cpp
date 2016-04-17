//
//  Engine.cpp
//  HackDfw
//
//  Created by Leelabrindavanan Karunakaran on 4/16/16.
//  Copyright © 2016 Leelabrindavanan Karunakaran. All rights reserved.
//
#include <cmath>
#include "Engine.hpp"
#define vmax 30
#define vmin 10
    
Engine::Engine(){
        current_Coor.ground = 513;
        current_Coor.x = 0;
        current_Coor.y = current_Coor.ground - 145;
        current_Coor.x_dist = 0;
        current_Coor.vx = 0;
        current_Coor.vy = 0;
        current_Coor.ax = 0;
        current_Coor.ay = 0;
        current_Coor.up = false;
        current_Coor.down = false;
        current_Coor.left = false;
        current_Coor.right = false;
        current_Coor.air = false;
        current_Coor = current_Coor;
    }
    
Engine::Coordinate current_Coor;
void Engine::cycle(){
        Engine::calc_accel();
        Engine::calc_variables();
        current_Coor = current_Coor;
    }
    
void Engine::calc_accel(){
        int button_press_x = 0;
        
        if(current_Coor.up == true){
            if(!current_Coor.air){
                current_Coor.vy = -20;
            }
            
        }
        
        if(current_Coor.right == true){
            if(current_Coor.vx < vmin){
                current_Coor.vx = vmin;
            }
            if(current_Coor.vx < 0){
                current_Coor.vx = vmin - 5;
            }
            current_Coor.ax = 2;
            button_press_x = 1;
        }
        
        if(current_Coor.left == true){
            if(current_Coor.vx > -1 * vmin){
                current_Coor.vx = -1 * vmin;
            }
            if(current_Coor.vx > 0){
                current_Coor.vx = -1 * vmin + 5;
            }
            current_Coor.ax = -2;
            button_press_x = 1;
        }
        
      /*  if(current_Coor.down == true){
            current_Coor.ay = 1;
        }
        */
        //default x and y accel
        if(button_press_x == 0){
            if(current_Coor.vx > 0){
                current_Coor.ax = -2;
            }
            else if(current_Coor.vx < 0){
                current_Coor.ax = 2;
            }
            else{
                current_Coor.ax = 0;
            }

            if((current_Coor.vx > 0) && (current_Coor.vx < 5)){
                current_Coor.ax = -0.05;
            }
            if((current_Coor.vx < 0) && (current_Coor.vx > -5)){
                current_Coor.ax = 0.05;
            }
 
        }
        if(current_Coor.air == true){
            current_Coor.ay = 1;
        }
        else{
            current_Coor.ay = 0;
        }
    
    }
    
void Engine::calc_variables(){
        current_Coor.vx = current_Coor.vx + current_Coor.ax;
        current_Coor.vy = current_Coor.vy + current_Coor.ay;
        
        if(current_Coor.vx > vmax){
            current_Coor.vx = vmax;
        }
        
        if(current_Coor.vx < -1 * vmax){
            current_Coor.vx = -1 * vmax;
        }
        
        if(current_Coor.vy > vmax){
            current_Coor.vy = vmax;
        }
        
        if(current_Coor.vy < -1 * vmax){
            current_Coor.vy = -1 * vmax;
        }
        if((current_Coor.vx) > 0 && (current_Coor.vx < 1)){
           current_Coor.vx = 0;
        }
        if((current_Coor.vx) < 0 && (current_Coor.vx > -1)){
            current_Coor.vx = 0;
        }
    
    
        current_Coor.x = current_Coor.x + current_Coor.vx;
        current_Coor.y = current_Coor.y + current_Coor.vy;
    
        current_Coor.x_dist = current_Coor.x_dist + current_Coor.vx;
    
        if(current_Coor.x < 0){
            current_Coor.x = 0;
        }
        if(current_Coor.x > 800 -84){
            current_Coor.x = 800 -84;
        }
        
        if(current_Coor.y < 0){
            current_Coor.y = 0;
        }
        if(current_Coor.y > current_Coor.ground - 145){
            current_Coor.y = current_Coor.ground - 145;
        }
        if(current_Coor.y < current_Coor.ground - 145){
            current_Coor.air = true;
        }
        else{
            current_Coor.air = false;
        }

    }
    
double Engine::getX(){
        return current_Coor.x;
    }
    
double Engine::getY(){
        return current_Coor.y;
    }
double Engine::getDist(){
        return current_Coor.x_dist;
}
void Engine::setUp(){
        current_Coor.up = true;
    }
void Engine::setDown(){
        current_Coor.down = true;
    }
void Engine::setLeft(){
        current_Coor.left = true;
    }
void Engine::setRight(){
        current_Coor.right = true;
    }
void Engine::clearButton(){
    current_Coor.up = false;
    current_Coor.down = false;
    current_Coor.left = false;
    current_Coor.right = false;
}


