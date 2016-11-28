//
//  Creature.cpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Creature.hpp"

void Creature::setupCreature(xml_node<> *node){
    for (xml_node<>* tmp = node->first_node(); tmp; tmp = tmp->next_sibling()) {
        string s = string(tmp->name());
        
        if (s == "name")
            this->name = tmp->value();
        if (s == "status")
            this->status = tmp->value();
        if (s == "description")
            this->description = tmp->value();
        if (s == "vulnerability")
            vulnerability.push_back(tmp->value());
        if (s == "attack")
            attack = new Attack(tmp);
        if (s == "trigger")
            trigger.push_back(new Trigger(tmp));
        
    }
}
