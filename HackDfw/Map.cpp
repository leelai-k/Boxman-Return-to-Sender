//
//  Map.cpp
//  HackDfw
//
//  Created by Leelabrindavanan Karunakaran on 4/17/16.
//  Copyright © 2016 Leelabrindavanan Karunakaran. All rights reserved.
//

#include "Map.hpp"
Map::Map(int frame_size){
    Map::resList.resize(frame_size);
}

std::vector<Map::Res> Map::getRes(int frame_num){
    return Map::resList[frame_num];
}

void Map::addRes(int frame, double x, double y, int id){
    Map::Res r;
    r.frame = frame;
    r.x = x;
    r.y = y;
    r.id = id;
    r.seen = false;
    Map::resList[frame].push_back(r);
    
}

void Map::updateFrameRes(std::vector<Map::Res> m, int frame_num){
    Map::resList[frame_num] = m;
}