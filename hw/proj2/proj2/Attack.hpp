//
//  Attack.hpp
//  proj2
//
//  Created by liang on 2016/11/27.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Attack_hpp
#define Attack_hpp

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

using namespace std;
using namespace rapidxml;

struct _condition{
    string object;
    string status;
};

class Attack{
public:
    _condition condition;
    string print;
    vector<string> action;
    
    bool has_condition;
    bool has_print;
    bool has_action;
    
    Attack(xml_node<>* node){
        setupAttack(node);
    }
    
    virtual ~Attack(){}
    
private:
    void setupAttack(xml_node<>* node);
    
};
#endif /* Attack_hpp */
