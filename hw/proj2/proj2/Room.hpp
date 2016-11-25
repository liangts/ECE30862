//
//  Room.hpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Room_hpp
#define Room_hpp

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
using namespace std;
using namespace rapidxml;


struct _boundary{
    string dir;
    string name;
    
};

class Room{
public:
    string name;
    string status;
    string type;
    string description;
    vector<_boundary *> border;
    vector<string> container;
    vector<string> item;
    vector<string> creature;
    vector<Trigger*> trigger;
    
    Room(xml_node<>* node){
        setupRoom(node);
    }
    virtual ~Room(){};
    
    
private:
    void setupRoom(xml_node<>* room);
    
};

#endif /* Room_hpp */
