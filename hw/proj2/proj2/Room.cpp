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
        string s = string(tmp->name());
        if(s == "name")
            name = tmp -> value();
        if(s == "status")
            status = tmp->value();
        if(s == "type")
            type = tmp -> value();
        if(s == "description")
            description = tmp -> value();
        if(s == "border"){
            _boundary * newborder = new _boundary();
            string bdname, direction;
            for(xml_node<>* tmp2 = tmp -> first_node();tmp2; tmp2 = tmp2 -> next_sibling()){
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

        if(s == "container")
            container.push_back(tmp ->value());
        if (s == "item")
            item.push_back(tmp->value());
        if (s == "creature")
            creature.push_back(tmp->value());
        if (s == "trigger")
            trigger.push_back(new Trigger(tmp));
    }
}
