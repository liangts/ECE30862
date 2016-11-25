//
//  Trigger.cpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Trigger.hpp"

void Trigger::construct_trigger(xml_node<>* node){
    //Init elements;
    has_command = false;
    has_print = false;
    has_action = false;
    type = "single";
    iterator = 0;
    
    for(xml_node<>* son = node ->first_node();son; son = son->next_sibling()){
        if (string(son->name()) == "type")
            type = son -> value();
        
        if (string(son->name()) == "print"){
            has_print = true;
            print = son -> value();
        }
        
        
        if (string(son->name()) == "command"){
            has_command = true;
            command = son->name();
        }
        
        if (string(son->name()) == "action"){
            has_action = true;
            string temp = son -> name();
            action.push_back(temp);
        }
        
        if (string(son->name()) == "condition"){
            condition = _return_condition(son);
            if (condition == 2)
                setupStatus(node);
            else if (condition == 3)
                setupOwner(node);
        }
    }
}

int Trigger::_return_condition(xml_node<> *node){
    int n = 0;
    for (xml_node<>* son = node ->first_node();son; son = son->next_sibling()){
        ++n;
    }
    return n;
}

void Trigger::setupStatus(xml_node<> *node){
    for (xml_node<>* son = node ->first_node();son; son = son->next_sibling()){
        if(string(son->name()) == "object"){
            status.object = son -> value();
        }
        if(string(son->name()) == "status"){
            status.status = son -> value();
        }
    }

}


void Trigger::setupOwner(xml_node<> *node){
    for(xml_node<>* son = node -> first_node();son; son = son -> next_sibling()){
        if(string(son->name()) == "object"){
            owner.object = son -> value();
        }
        if(string(son->name()) == "has"){
            owner.has = son -> value();
        }
        if(string(son->name()) == "owner"){
            owner.owner = son -> value();
        }
    }
}
















