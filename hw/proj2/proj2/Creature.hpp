//
//  Creature.hpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Creature_hpp
#define Creature_hpp

#include<iostream>
#include<sstream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<string>
#include<list>
#include "rapidxml-1.13/rapidxml.hpp"
#include "rapidxml-1.13/rapidxml_utils.hpp"
#include "rapidxml-1.13/rapidxml_print.hpp"
#include "Trigger.hpp"
#include "Attack.hpp"
using namespace std;
using namespace rapidxml;

class Creature{
public:
    string name;
    string status;
    string description;
    vector<string> vulnerability;
    vector<Trigger*> trigger;
    Attack* attack;
    
    Creature(xml_node<>* node){
        setupCreature(node);
    }
    
    virtual ~Creature(){}
    
private:
    void setupCreature(xml_node<>* node);
};


#endif /* Creature_hpp */
