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
    
    for(xml_node<>* tmp = node ->first_node();tmp; tmp = tmp->next_sibling()){
        if (string(tmp->name()) == "type")
            type = tmp -> value();
        
        if (string(tmp->name()) == "print"){
            has_print = true;
            print = tmp -> value();
        }
        
        
        if (string(tmp->name()) == "command"){
            has_command = true;
            command = tmp->name();
        }
        
        if (string(tmp->name()) == "action"){
            has_action = true;
            string temp = tmp -> name();
            action.push_back(temp);
        }
        
        if (string(tmp->name()) == "condition"){
            condition = _return_condition(tmp);
            if (condition == 2)
                setupStatus(tmp);
            else if (condition == 3)
                setupOwner(tmp);
        }
    }
}

int Trigger::_return_condition(xml_node<> *node){
    int n = 0;
    for (xml_node<>* tmp = node ->first_node();tmp; tmp = tmp->next_sibling()){
        ++n;
    }
    return n;
}

void Trigger::setupStatus(xml_node<> *node){
    for (xml_node<>* tmp = node ->first_node();tmp; tmp = tmp->next_sibling()){
        if(string(tmp->name()) == "object"){
            status.object = tmp -> value();
        }
        if(string(tmp->name()) == "status"){
            status.status = tmp -> value();
        }
    }

}


void Trigger::setupOwner(xml_node<> *node){
    for(xml_node<>* tmp = node -> first_node();tmp; tmp = tmp -> next_sibling()){
        if(string(tmp->name()) == "object"){
            owner.object = tmp -> value();
        }
        if(string(tmp->name()) == "has"){
            owner.has = tmp -> value();
        }
        if(string(tmp->name()) == "owner"){
            owner.owner = tmp -> value();
            cout<<"testpoint1: " << tmp->value() <<endl;
        }
    }
}
















