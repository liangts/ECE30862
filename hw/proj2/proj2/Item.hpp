//
//  Item.hpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Item_hpp
#define Item_hpp

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

struct _turn_on{
    string print_msg;
    string action_msg;
};

class Item{
public:
    string name, status, description, writing;
    _turn_on turnon;
    bool able_turnon;
    vector<Trigger*> trigger;
    Item(xml_node<>* node){
        setupItem(node);
    }
    virtual ~Item(){}
    
private:
    void setupItem(xml_node<>* node);
};

#endif /* Item_hpp */
