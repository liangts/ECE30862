//
//  Game_system.cpp
//  proj2
//
//  Created by liang on 2016/12/3.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Game_system.hpp"

void objects::_add(string condition){
    string object_name;
    string location;
    unsigned long to_pos = condition.find(" to ");
    object_name = condition.substr(0, to_pos);
    location = condition.substr(to_pos + 4);
    int i;
    string object_type = objects::type_detection(object_name);
    if(object_type == "Item"){
        for(i = 0; i < room_ptr_vector.size(); i++){
            if(room_ptr_vector[i]->name == location){
                room_ptr_vector[i]->item.push_back(object_name);
                return;
            }
        }
        for(i = 0; i < container_ptr_vector.size(); i++){
            if(container_ptr_vector[i]->name == location){
                container_ptr_vector[i]->item.push_back(object_name);
                return;
            }
        }
    }
    if(object_type == "Creature"){
        for(i = 0; i < room_ptr_vector.size(); i++){
            if(room_ptr_vector[i]->name == location){
                room_ptr_vector[i]->creature.push_back(object_name);
                return;
            }
        }
    }
    if(object_type == "Container"){
        for(i = 0; i < room_ptr_vector.size(); i++){
            if(room_ptr_vector[i]->name == location){
                room_ptr_vector[i]->container.push_back(object_name);
                return;
            }
        }
    }
}

void objects::_delete(string obj_name){
    for(int i = 0; i < room_ptr_vector.size(); i++){
        if(room_ptr_vector[i]->name == obj_name){
            for(int j = 0; j < curr_room_ptr -> border.size(); j++){
                if(curr_room_ptr -> border[j] -> name == obj_name){
                    curr_room_ptr->border.erase(curr_room_ptr->border.begin()+j);
                    return;
                }
            }
        }
    }
    for(int i = 0; i < container_ptr_vector.size(); i++){
        if(container_ptr_vector[i]->name == obj_name){
            for(int j = 0; j < room_ptr_vector.size(); j++){
                for(int k = 0; k < room_ptr_vector[j] -> container.size(); k++){
                    if(room_ptr_vector[j] -> container[k] == obj_name){
                        room_ptr_vector[j] -> container.erase(room_ptr_vector[j]->container.begin()+k);
                        return;
                    }
                }
            }
        }
    }
    for(int i = 0; i < item_ptr_vector.size(); i++){
        if(item_ptr_vector[i]->name == obj_name){
            for(int j = 0; j < room_ptr_vector.size(); j++){
                for(int k = 0; k < room_ptr_vector[j] -> item.size(); k++){
                    if(room_ptr_vector[j] -> item[k] == obj_name){
                        room_ptr_vector[j] -> item.erase(room_ptr_vector[j]->item.begin()+k);
                        return;
                    }
                }
            }
        }
    }
    for(int i = 0; i < creature_ptr_vector.size(); i++){
        if(creature_ptr_vector[i]->name == obj_name){
            for(int j = 0; j < room_ptr_vector.size(); j++){
                for(int k = 0; k < room_ptr_vector[j] -> creature.size(); k++){
                    if(room_ptr_vector[j] -> creature[k] == obj_name){
                        room_ptr_vector[j] -> creature.erase(room_ptr_vector[j]->creature.begin()+k);
                        return;
                    }
                }
            }
        }
    }
}


void objects::_update(string condition){
    string object_name;
    string new_status;
    unsigned long to_pos = condition.find(" to ");
    object_name = condition.substr(0, to_pos);
    new_status = condition.substr(to_pos + 4);
    int i;
    for(i = 0; i < room_ptr_vector.size(); i++){
        if(room_ptr_vector[i]->name == object_name){
            room_ptr_vector[i]->status = new_status;
            return;
        }
    }
    for(i = 0; i < container_ptr_vector.size(); i++){
        if(container_ptr_vector[i]->name == object_name){
            container_ptr_vector[i]->status = new_status;
            return;
        }
    }
    for(i = 0; i < item_ptr_vector.size(); i++){
        if(item_ptr_vector[i]->name == object_name){
            item_ptr_vector[i]->status = new_status;
            return;
        }
    }
    for(i = 0; i < creature_ptr_vector.size(); i++){
        if(creature_ptr_vector[i]->name == object_name){
            creature_ptr_vector[i]->status = new_status;
            return;
        }
    }
}


void game::over(){
    game_over_indication = true;
    cout << "Victory!" << endl;
}


void game::checkAction(string action){
    if(action.find("Add") != string::npos){
        objects::_add(action.erase(0,4));
        return;
    }
    if(action.find("Delete") != string::npos){
        objects::_delete(action.erase(0,7));
        return;
    }
    if(action.find("Update") != string::npos){
        objects::_update(action.erase(0,7));
        return;
    }
    if(action == "Game Over"){
        game::over();
        return;
    }
    game::input_response(action);
}


void game::changeRoom(string input){
    unsigned long i = (curr_room_ptr ->border).size();
    int index = 0;
    for(index = 0; index < i; index++){
        if(curr_room_ptr -> border[index] -> dir == input){
            for(int index2 = 0; index2 < room_ptr_vector.size(); index2++){
                if(room_ptr_vector[index2] -> name == curr_room_ptr -> border[index] -> name)
                    curr_room_ptr = room_ptr_vector[index2];
            }
            break;
        }
    }
    if(index == i){
        cout << "You can't go that way" << endl;
    }else{
        cout << curr_room_ptr -> description << endl;
    }
}


void game::showInventoru(){
    if (inventory.size() == 0){
        cout << "Inventory: Empty" << endl;
        return;
    }
    
    cout << "Inventory: ";
    int i = 0;
    for (i = 0; i < inventory.size() - 1; i++)
        cout << inventory[i] << ",";
    cout << inventory[i] << endl;
}


void game::take(string input){
    int i,j,k;
    for(i = 0; i < (curr_room_ptr -> item).size(); i++){
        if(curr_room_ptr -> item[i] == input){
            inventory.push_back(input);
            (curr_room_ptr -> item).erase((curr_room_ptr -> item).begin() + i);
            cout << input << " has been added to inventory." << endl;
            return;
        }
    }
    
    for(i = 0; i < (curr_room_ptr -> container).size(); i++){
        for(j = 0; j < container_ptr_vector.size(); j++){
            if(container_ptr_vector[j]->name == curr_room_ptr->container[i] && container_ptr_vector[j]->status == "unlocked"){
                for(k = 0; k < container_ptr_vector[j]->item.size();k++){
                    if(container_ptr_vector[j]->item[k] == input){
                        (curr_room_ptr -> item).push_back(container_ptr_vector[j] -> item[k]);
                        container_ptr_vector[j] -> item.erase(container_ptr_vector[j]->item.begin()+k);
                        take(input);
                        return;
                    }
                }
            }
        }
    }
    cout << "There is no such thing to take." << endl;
}

void game::drop(string input){
    for (int i = 0; i < inventory.size(); i++) {
        if(inventory[i] == input){
            (curr_room_ptr->item).push_back(input);
            inventory.erase(inventory.begin() + i);
            cout << input << "has been dropped." <<endl;
            return;
        }
    }
    cout << "There is no such thing to drop." << endl;
}

void game::read(string input){
    for (int i = 0; i < inventory.size(); i++) {
        if (inventory[i] == input){
            for (int j = 0; j < item_ptr_vector.size(); j++) {
                if (item_ptr_vector[j] -> name == input){
                    if (item_ptr_vector[j] -> writing.size() == 0)
                        cout << "There is nothing to read." <<endl;
                    else
                        cout << item_ptr_vector[j] -> writing << endl;
                }
            }
            return;
        }
    }
    cout << "There is nothing in your inventory to read." << endl;
}

void game::put(string input){
    
    
    
}

















