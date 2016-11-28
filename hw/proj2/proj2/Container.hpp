//
//  Container.hpp
//  proj2
//
//  Created by liang on 2016/11/24.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Container_hpp
#define Container_hpp

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

class Container{
public:
    string name;
    string description;
    string status;
    vector<string> item;
    vector<string> accept;
    vector<Trigger*> trigger;
    Container(xml_node<>* node){
        setupContainer(node);
    }
    virtual ~Container(){}
    
    
private:
    void setupContainer(xml_node<>* node);
};

#endif /* Container_hpp */
