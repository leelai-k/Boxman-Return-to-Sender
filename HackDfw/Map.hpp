//
//  Map.hpp
//  HackDfw
//
//  Created by Leelabrindavanan Karunakaran on 4/17/16.
//  Copyright © 2016 Leelabrindavanan Karunakaran. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <stdio.h>
#include <vector>
class Map{
public:
    typedef struct Res_Struct{
        int frame;
        double x,
        y;
        int id;         //1st digit is type, 2nd is frame, 3rd is 0 ind inst
        bool seen;
    } Res;
    Map(int frame_size);
    std::vector <std::vector<Res>> resList; //index corresponds to frame
    std::vector<Res> getRes(int frame_num);
    void addRes(int frame, double x, double y, int id);
    void updateFrameRes(std::vector<Map::Res> m, int frame_num);
    
};

#endif /* Map_hpp */
