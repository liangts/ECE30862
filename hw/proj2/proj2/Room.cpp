//
//  Room.cpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Room.hpp"

void Room::setupRoom(xml_node<> *room){
    for (xml_node<>* tmp = room->first_node(); tmp; tmp = tmp->next_sibling()){
        if(string(tmp->name()) == "name"){
            name = tmp -> value();
        }
        if(string(tmp->name()) == "status"){
            status = tmp->value();
        }
        if(string(tmp->name()) == "type"){
            type = tmp -> value();
        }
        if(string(tmp->name()) == "description"){
            description = tmp -> value();
        }
        if(string(tmp->name()) == "border"){
            _boundary * newborder = new _boundary();
            string bdname, direction;
            for(xml_node<>* tmp2 = tmp -> first_node();
                tmp2; tmp2 = tmp2 -> next_sibling()){
                if(string(tmp2->name()) == "name"){
                    bdname = tmp2 -> value();
                }
                if(string(tmp2->name()) == "direction"){
                    direction = tmp2->value();
                    if(direction == "north"){direction = "n";}
                    if(direction == "south"){direction = "s";}
                    if(direction == "west"){direction = "w";}
                    if(direction == "east"){direction = "e";}
                }
            }
            newborder -> dir = direction;
            newborder -> name = bdname;
            border.push_back(newborder);
        }
        string tmp_buffer;
        if(string(tmp->name()) == "container"){
            tmp_buffer = tmp -> value();
            container.push_back(tmp_buffer);
        }
        if(string(tmp->name()) == "item"){
            tmp_buffer = tmp -> value();
            item.push_back(tmp_buffer);
        }
        if(string(tmp->name()) == "creature"){
            tmp_buffer = tmp -> value();
            creature.push_back(tmp_buffer);
        }
        if(string(tmp->name()) == "trigger"){
            Trigger * t = new Trigger(tmp);
            trigger.push_back(t);
        }
    }
}
