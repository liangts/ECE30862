//
//  Attack.cpp
//  proj2
//
//  Created by liang on 2016/11/27.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Attack.hpp"

void Attack::setupAttack(xml_node<> *node){
    has_condition = false;
    has_print = false;
    has_action = false;
    
    for (xml_node<>* tmp = node->first_node(); tmp; tmp = tmp->next_sibling()) {
        string s = string(tmp->name());
        
        if (s == "condition"){
            has_condition = true;
            for (xml_node<>* tmp2 = node->first_node(); tmp2; tmp2 = tmp2->next_sibling()) {
                string s2 = string(tmp2->name());
                
                if (s2 == "object")
                    condition.object = tmp2->value();
                if (s2 == "status")
                    condition.status = tmp2->value();
            }
        }
        
        if (s == "print"){
            has_print = true;
            this->print = tmp->value();
        }
        
        
        if (s == "action"){
            has_action = true;
            action.push_back(tmp->value());
        }
        
    }
}
