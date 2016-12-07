//
//  Item.cpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Item.hpp"

void Item::setupItem(xml_node<> *node) {
    able_turnon = false;
    
    for (xml_node<>* tmp = node->first_node(); tmp; tmp = tmp->next_sibling()) {
        string s = string(tmp->name());
        
        if (s == "name")
            this->name = tmp->value();
        if (s == "description")
            this->description = tmp->value();
        if (s == "status")
            this->status = tmp->value();
        if (s == "writing")
            this->writing = tmp->value();
        
        if (s == "turnon"){
            able_turnon = true;
            string printmsg, actionmsg;
            for (xml_node<>* tmp2 = tmp->first_node(); tmp2; tmp2 = tmp2->next_sibling()) {
                string s2 = string(tmp2->name());
                
                if (s2 == "print")
//                    turnon.print_msg = tmp2->value();
                    printmsg = tmp2->value();
                if (s2 == "action")
//                    turnon.action_msg = tmp2 -> value();
                    actionmsg = tmp2->value();
                
            }
            turnon.print_msg = printmsg;
            turnon.action_msg = actionmsg;
        }
        
        if (s == "trigger")
            trigger.push_back(new Trigger(tmp));
    }
}
