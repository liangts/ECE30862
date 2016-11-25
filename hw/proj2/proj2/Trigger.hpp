//
//  Trigger.hpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Trigger_hpp
#define Trigger_hpp

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


struct _status{
    string object;
    string status;
};

struct _owner{
    string object;
    string has;
    string owner;
    
};

class Trigger{
public:
    string command, type, print;
    
    vector<string> action;
    int condition;
    bool has_command, has_print, has_action;
    
    _status status;
    _owner owner;
    
    int iterator;
    
    Trigger(xml_node<>* node){
        construct_trigger(node);
    }
    
    virtual ~Trigger(){};
    
    
private:
    void construct_trigger(xml_node<>* node);
    int _return_condition(xml_node<>* node);
    void setupStatus(xml_node<>* node);
    void setupOwner(xml_node<>* node);
};

#endif /* Trigger_hpp */
