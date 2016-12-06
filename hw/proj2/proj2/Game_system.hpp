//
//  Game_system.hpp
//  proj2
//
//  Created by liang on 2016/12/3.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Game_system_hpp
#define Game_system_hpp

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include<list>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "Room.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Creature.hpp"

using namespace std;
using namespace rapidxml;

vector<Room*> room_ptr_vector;
vector<Container*> container_ptr_vector;
vector<Item*> item_ptr_vector;
vector<Creature*> creature_ptr_vector;

vector<string>inventory;
bool game_over_indication = false;

Room* curr_room_ptr = NULL;

namespace objects {
    void _add(string condition);
    void _delete(string obj_name);
    void _update(string condition);
    string type_detection(string);

}

namespace game {
    void over();
    void checkAction(string action);
    void input_response(string);
    
    void changeRoom(string input);
    void showInventory();
    void take(string input);
    void drop(string input);
    void read(string input);
    void put(string src, string dest);
    void turnon(string input);
    void open(string input);
    void exit();
    void attack(string creature, string weapon);
}

namespace trigger {
    bool owner(Trigger* t);
    bool status(Trigger* t);
    bool check_wo_cmd();
    bool check_w_cmd(string input);
    
}


#endif /* Game_system_hpp */















