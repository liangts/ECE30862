//
//  main.cpp
//  proj2
//
//  Created by liang on 2016/11/23.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Game_system.hpp"

using namespace std;

int _load_xml_elements(xml_node<>* node ,vector<xml_node<>*> rv_ptr, vector<xml_node<>*> cv_ptr, vector<xml_node<>*> crv_ptr, vector<xml_node<>*> iv_ptr){
    int success = 0;
    for (xml_node<>* tmp = node->first_node(); tmp != 0; tmp->next_sibling()) {
        string s = string(tmp->name());
        
        if (s == "room")
            rv_ptr.push_back(tmp);
        if (s == "container")
            cv_ptr.push_back(tmp);
        if (s == "item")
            iv_ptr.push_back(tmp);
        if (s == "creature")
            crv_ptr.push_back(tmp);
    }
    success = 1;
    return success;
}



int main(int argc, const char * argv[]) {
    if(argc != 2){
        cout << "Incorrect parameters" <<endl;
        cout << "Usage: ./a.out <xml_map_name>" <<endl;
        
        return 1;
    }
    
    file<> xmlFile(argv[1]);
    xml_document<> map;
    map.parse<0>(xmlFile.data());
    xml_node<>* node = map.first_node();
    
    vector<xml_node<>*> room_node_ptr;
    vector<xml_node<>*> container_node_ptr;
    vector<xml_node<>*> creature_node_ptr;
    vector<xml_node<>*> item_node_ptr;

    int contd = _load_xml_elements(node, room_node_ptr, container_node_ptr, creature_node_ptr, item_node_ptr);
    
    if (contd != 1)
        return 2;
    
    for (int ind = 0; ind < room_node_ptr.size(); ind++) {
        room_ptr_vector.push_back(new Room(room_node_ptr[ind]));
    }
    
    for (int ind = 0; ind < container_node_ptr.size(); ind++) {
        container_ptr_vector.push_back(new Container(container_node_ptr[ind]));
    }
    
    for (int ind = 0; ind < item_node_ptr.size(); ind++) {
        item_ptr_vector.push_back(new Item(item_node_ptr[ind]));
    }
    
    for (int ind = 0; ind < creature_node_ptr.size(); ind++) {
        creature_ptr_vector.push_back(new Creature(creature_node_ptr[ind]));
    }
    
    string input_cmd;
    curr_room_ptr = room_ptr_vector[0];
    cout << curr_room_ptr->description <<endl;
    bool _override = false;
    for(;;){
        _override = trigger::check_wo_cmd();
        if(game_over_indication)
            return 0;
        if(!_override)
            return 0;
        getline(cin, input_cmd);
        
        if (string(input_cmd) == "q")
            return 0;
        
        _override = trigger::check_w_cmd(input_cmd);
        if(game_over_indication)
            return 0;
        if (!_override)
            return 0;
        
        game::input_response(input_cmd);
        if(game_over_indication)
            return 0;
    }

    
    return 0;
}


