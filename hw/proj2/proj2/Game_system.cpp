//
//  Game_system.cpp
//  proj2
//
//  Created by liang on 2016/12/3.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Game_system.hpp"

int _load_xml_elements(xml_node<>* node ,vector<xml_node<>*> rv_ptr, vector<xml_node<>*> cv_ptr, vector<xml_node<>*> crv_ptr, vector<xml_node<>*> iv_ptr){
    int success = 0;
    for (xml_node<>* tmp = node->first_node(); tmp; tmp = tmp ->next_sibling()){
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


void game::showInventory(){
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

void game::put(string src, string dest){
    int i ,j, k;
    for (i = 0; i < inventory.size(); i++) {
        if (inventory[i] == src){
            if (curr_room_ptr->name == dest){
                game::drop(src);
                return;
            }
        
            for (j =0; j < curr_room_ptr->container.size(); j++) {
                if (curr_room_ptr -> container[j] == dest)
                    break;
            }
            if (j == curr_room_ptr->container.size()){
                cout << "There is nothing called "<< dest <<" in this room." <<endl;
                return;
            }
        
            for (j = 0; j < container_ptr_vector.size(); j++) {
                if (container_ptr_vector[j] -> name == dest){
                    if (container_ptr_vector[j]->accept.size() == 0){
                        container_ptr_vector[j] -> item.push_back(src);
                        inventory.erase(inventory.begin()+i);
                        cout << src <<" has been put to "<< dest << endl;
                        if(container_ptr_vector[j]->status == "")
                            container_ptr_vector[j]->status = "unlocked";
                        return;
                    }
                    for (k = 0; k < container_ptr_vector[j]->accept.size(); k++) {
                        if (container_ptr_vector[j]->accept[k] == src){
                            container_ptr_vector[j]->item.push_back(src);
                            inventory.erase(inventory.begin()+ i);
                            cout << src << " has been put to "<< dest << endl;
                            if (container_ptr_vector[j]->status == "")
                                container_ptr_vector[j]->status = "unlocked";
                            return;
                        }
                    }
                    cout << dest << "does not accept " << src << endl;
                    return;
                }
            }
            return;
        }
    }
    cout << "There is no " << src <<" in your inventory." << endl;
}

void game::turnon(string input){
    for(int i = 0; i < inventory.size(); i++){
        if(inventory[i] == input){
            for(int j = 0; j < item_ptr_vector.size(); j++){
                if(item_ptr_vector[j] -> name == input){
                    if(item_ptr_vector[j] -> able_turnon == false){
                        cout<<"Item is not able to be turned on." << endl;
                    }else{
                        cout<<"You activate the "<< item_ptr_vector[j]->name<<"."<<endl;
                        cout << item_ptr_vector[j] -> turnon.print_msg << endl;
                        game::checkAction(item_ptr_vector[j] -> turnon.action_msg);
                    }
                }
            }
            return;
        }
    }
    cout << "There is no such thing in your inventory to turn on." << endl;
}


void game::open(string input){
    int index;
    for(index = 0; index < curr_room_ptr -> container.size(); index++){
        if(curr_room_ptr -> container[index] == input){
            break;
        }
    }
    if(index == curr_room_ptr -> container.size()){
        cout << "There is no such thing here to open." << endl;
        return;
    }
    for(int i = 0; i < container_ptr_vector.size(); i++){
        if(container_ptr_vector[i] -> name == input){

            if(container_ptr_vector[i] -> status == "locked"){
                cout << container_ptr_vector[i] -> name << " is locked." << endl;
                return;
            }
            if((container_ptr_vector[i] -> item).size() == 0){
                cout <<container_ptr_vector[i] -> name << " is empty." << endl;
                return;
            }
            container_ptr_vector[i] -> status = "unlocked";

            cout << container_ptr_vector[i] -> name << " contains ";
            int j;
            for(j = 0; j < (container_ptr_vector[i] -> item).size() - 1; j++){
                cout << container_ptr_vector[i] -> item[j] << ", ";
            }
            cout << container_ptr_vector[i] -> item[j] << endl;
            return;
        }
    }
    
}


void game::exit(){
    if (curr_room_ptr->type == "exit"){
        game::over();
        return;
    }
    cout << "There is no exit in this room." <<endl;
}

void game::attack(string creature, string weapon){
    int index_creature;
    int index_weapon;
    
    for (index_creature = 0; index_creature < curr_room_ptr->creature.size(); index_creature++){
        if (curr_room_ptr-> creature[index_creature] == creature)
            break;
    }
    if (index_creature == curr_room_ptr->creature.size()){
        cout << "There is no creature " << creature << " here." << endl;
        return;
    }
    
    for (index_weapon = 0; index_weapon < inventory.size(); index_weapon++){
        if (inventory[index_weapon] == weapon)
            break;
    }
    
    if (index_weapon == inventory.size()){
        cout << "There is no weapon" << weapon << "in your inventory." << endl;
        return;
    }
    
    cout << "You assault the " << creature << "with the " << weapon << endl;
    
    for(index_creature = 0; index_creature<creature_ptr_vector.size(); index_creature++){
        if(creature_ptr_vector[index_creature]->name == creature){ break;}
    }
    for(index_weapon = 0; index_weapon < creature_ptr_vector[index_creature]->vulnerability.size();index_weapon++){
        if(creature_ptr_vector[index_creature]->vulnerability[index_weapon] == weapon)
            break;
    }
    if(index_weapon == creature_ptr_vector[index_creature]->vulnerability.size()){
        cout<<"It seems "<<weapon<<" is useless to "<<creature<<endl;
        return;
    }
    if(creature_ptr_vector[index_creature]->attack == NULL){
        return;
    }
    
    if(creature_ptr_vector[index_creature]->attack->has_condition){
        string object = creature_ptr_vector[index_creature]->attack->condition.object;
        string status = creature_ptr_vector[index_creature]->attack->condition.status;
        bool found = false;
        bool match = false;
        for(index_weapon = 0; index_weapon < item_ptr_vector.size(); index_weapon++){
            if(item_ptr_vector[index_weapon]->name == object){
                found = true;
                match = item_ptr_vector[index_weapon]->status == status;
                break;
            }
        }
        if(!found){
            for(index_weapon = 0; index_weapon < room_ptr_vector.size(); index_weapon++){
                if(room_ptr_vector[index_weapon]->name == object){
                    found = true;
                    match = room_ptr_vector[index_weapon]->status == status;
                    break;
                }
            }
        }
        if(!found){
            for(index_weapon = 0; index_weapon < container_ptr_vector.size(); index_weapon++){
                if(container_ptr_vector[index_weapon]->name == object){
                    found = true;
                    match = container_ptr_vector[index_weapon]->status == status;
                    break;
                }
            }
        }
        if(!found){
            for(index_weapon = 0; index_weapon < creature_ptr_vector.size(); index_weapon++){
                if(creature_ptr_vector[index_weapon]->name == object){
                    found = true;
                    match = creature_ptr_vector[index_weapon]->status == status;
                    break;
                }
            }
        }
        if(!match){
            cout<<"You need make sure "<<object<<" is "<<status<<endl;
            return;
        }
    }

    if(creature_ptr_vector[index_creature]->attack->has_print){
        cout<<creature_ptr_vector[index_creature]->attack->print<<endl;
    }
    if(creature_ptr_vector[index_creature]->attack->has_action){
        for(index_weapon = 0; index_weapon<creature_ptr_vector[index_creature]->attack->action.size();index_weapon++){
            checkAction(creature_ptr_vector[index_creature]->attack->action[index_weapon]);
        }
    }
}


void game::input_response(string input){
    if(input == "n" || input == "s" || input == "w" || input == "e"){
        game::changeRoom(input);
        return;
    }
    if(input == "i"){
        showInventory();
        return;
    }

    if(input == "take"){
        cout<<"What do you want to take? ";
        getline(cin, input);
        take(input);
        return;
    }
    if(input.find("take") != string::npos){
        input.erase(0,5);
        take(input);
        return;
    }

    if(input == "drop"){
        cout<<"What do you want to drop? ";
        getline(cin, input);
        drop(input);
        return;
    }
    if(input.find("drop") != string::npos){
        input.erase(0,5);
        drop(input);
        return;
    }

    if(input == "read"){
        cout<<"What do you want to read? ";
        getline(cin, input);
        read(input);
        return;
    }
    if(input.find("read") != string::npos){
        input.erase(0,5);
        read(input);
        return;
    }
    //open
    if(input == "open"){
        cout<<"What do you want to open? ";
        getline(cin, input);
        if(input == "exit"){
            exit();
            return;
        }
        open(input);
        return;
    }
    if(input.find("open") != string::npos){
        input.erase(0,5);
        if(input == "exit"){
            exit();
            return;
        }
        open(input);
        return;
    }
    //put
    if(input == "put"){
        cout << "What do you want to put? ";
        getline(cin, input);
        string put_item = input;
        cout << "Where do you want to put in? ";
        getline(cin, input);
        string put_into = input;
        put(put_item, put_into);
        return;
    }
    if(input.find("put") != string::npos){
        input.erase(0,4);
        unsigned long space_pos = input.find(" "); //it's also size of item string
        string put_item = input.substr(0, space_pos);
        input.erase(0, space_pos + 4);
        string put_into = input;
        put(put_item, put_into);
        return;
    }
    //turn on
    if(input == "turn on"){
        cout<<"What do you want to turn on? ";
        getline(cin, input);
        turnon(input);
        return;
    }
    if(input.find("turn on") != string::npos){
        input.erase(0,8);
        turnon(input);
        return;
    }
    //attack
    if(input == "attack"){
        cout << "What do you want to attack? ";
        getline(cin, input);
        string monster = input;
        cout << "What do you want to attack with? ";
        getline(cin, input);
        string weapon = input;
        attack(monster, weapon);
        return;
    }
    if(input.find("attack") != string::npos){
        input.erase(0,7);
        unsigned long space_pos = input.find(" "); //it's also size of item string
        string monster = input.substr(0, space_pos);
        input.erase(0, space_pos + 6);
        string weapon = input;
        attack(monster, weapon);
        return;
    }
    cout << "Error" << endl;
    
}


string objects::type_detection(string unknown){

    for (int i = 0; i < room_ptr_vector.size(); i++) {
        if (room_ptr_vector[i]->name == unknown)
            return "Room";
    }
    
    for (int i = 0; i < container_ptr_vector.size(); i++) {
        if (container_ptr_vector[i]->name == unknown)
            return "Container";
    }
    
    for (int i = 0; i < item_ptr_vector.size(); i++) {
        if (item_ptr_vector[i]->name == unknown)
            return "Item";
    }
    
    for (int i = 0; i < creature_ptr_vector.size(); i++) {
        if (creature_ptr_vector[i]->name == unknown)
            return "Creature";
    }
    
    return NULL;
}


bool trigger::owner(Trigger *t){

    string owner = t -> owner.owner;
    string has = t -> owner.has;
    string object = t -> owner.object;
    //if owner + object == true && has == yes,
    // or owner + object == false && has == no, trigger activated
    //print and actions(plural), return true
    int i,j,k;
    if(owner == "inventory"){
        for(i = 0; i < inventory.size(); i++){
            if(inventory[i] == object){
                if(has == "yes"){
                    if(t->has_print)
                        cout<<t->print<<endl;
                    if(t->has_action){
                        for(k = 0; k < t->action.size();k++){
                            game::checkAction(t->action[k]);
                        }
                    }
                    return true;
                }else
                    return false;
            }
        }
        if(i == inventory.size()){
            if(has == "no"){
                if(t->has_print)
                    cout<<t->print<<endl;
                if(t->has_action){
                    for(k = 0; k < t->action.size();k++){
                        game::checkAction(t->action[k]);
                    }
                }
                return true;
            }else
                return false;
        }
    }
    string owner_type = objects::type_detection(owner);
    string object_type = objects::type_detection(object);
    if(owner_type == "Room"){
        for(i = 0; i < room_ptr_vector.size(); i++){
            if(room_ptr_vector[i] -> name == owner){
                if(object_type == "Item"){
                    for(j = 0; j < room_ptr_vector[i] -> item.size(); j++){
                        if(room_ptr_vector[i]->item[j] == object){
                            if(has == "yes"){
                                if(t->has_print)
                                    cout<<t->print<<endl;
                                if(t->has_action){
                                    for(k = 0; k < t->action.size();k++){
                                        game::checkAction(t->action[k]);
                                    }
                                }
                                return true;
                            }else
                                return false;
                        }
                    }
                    
                    if(j == room_ptr_vector[i]->item.size()){
                        if(has == "no"){
                            if(t->has_print)
                                cout<<t->print<<endl;
                            if(t->has_action){
                                for(k = 0; k < t->action.size();k++){
                                    game::checkAction(t->action[k]);
                                }
                            }
                            return true;
                        }else
                            return false;
                    }
                }
                if(object_type == "Container"){
                    for(j = 0; j < room_ptr_vector[i] -> container.size(); j++){
                        if(room_ptr_vector[i]->container[j]== object){
                            if(has == "yes"){
                                if(t->has_print)
                                    cout<<t->print<<endl;
                                if(t->has_action){
                                    for(k = 0; k < t->action.size();k++){
                                        game::checkAction(t->action[k]);
                                    }
                                }
                                return true;
                            }else
                                return false;
                        }
                    }
                    if(j == room_ptr_vector[i]->container.size()){
                        if(has == "no"){
                            if(t->has_print)
                                cout<<t->print<<endl;
                            if(t->has_action){
                                for(k = 0; k < t->action.size();k++){
                                    game::checkAction(t->action[k]);
                                }
                            }
                            return true;
                        }else
                            return false;
                    }
                }
                if(object_type == "Creature"){
                    for(j = 0; j < room_ptr_vector[i] -> creature.size(); j++){
                        if(room_ptr_vector[i]->creature[j]== object){
                            if(has == "yes"){
                                if(t->has_print)
                                    cout<<t->print<<endl;
                                if(t->has_action){
                                    for(k = 0; k < t->action.size();k++){
                                        game::checkAction(t->action[k]);
                                    }
                                }
                                return true;
                            }else
                                return false;
                        }
                    }
                    if(j == room_ptr_vector[i]->creature.size()){
                        if(has == "no"){
                            if(t->has_print)
                                cout<<t->print<<endl;
                            if(t->has_action){
                                for(k = 0; k < t->action.size();k++){
                                    game::checkAction(t->action[k]);
                                }
                            }
                            return true;
                        }else
                            return false;
                    }
                }
            }
        }
    }
    if(owner_type == "Container"){
        for(i = 0; i < container_ptr_vector.size(); i++){
            if(container_ptr_vector[i]->name == owner){
                //Object can only be item
                for(j = 0; j < container_ptr_vector[i] -> item.size(); j++){
                    if(container_ptr_vector[i]->item[j]== object){
                        if(has == "yes"){
                            if(t->has_print)
                                cout<<t->print<<endl;
                            if(t->has_action){
                                for(k = 0; k < t->action.size();k++){
                                    game::checkAction(t->action[k]);
                                }
                            }
                            return true;
                        }else
                            return false;
                    }
                }
                if(j == container_ptr_vector[i]->item.size()){
                    if(has == "no"){
                        if(t->has_print)
                            cout<<t->print<<endl;
                        if(t->has_action){
                            for(k = 0; k < t->action.size();k++){
                                game::checkAction(t->action[k]);
                            }
                        }
                        return true;
                    }else
                        return false;
                }
            }
        }
    }
    return false;
}


bool trigger::status(Trigger *t){
    //check object
    string object = t -> status.object;
    //check object's status
    string status = t -> status.status;
    //if it matches the status
    //print and actions(plural), return true
    int i,j;
    string object_type = objects::type_detection(object);
    if(object_type == "Room"){
        for(i = 0; i < room_ptr_vector.size(); i++){
            if(room_ptr_vector[i] -> name == object){
                if(room_ptr_vector[i] -> status == status){
                    if(t->has_print)
                        cout<<t->print<<endl;
                    if(t->has_action){
                        for(j = 0; j < t->action.size();j++){
                            game::checkAction(t->action[j]);
                        }
                    }
                    return true;
                }
            }
        }
    }
    if(object_type == "Item"){
        for(i = 0; i < item_ptr_vector.size(); i++){
            if(item_ptr_vector[i] -> name == object){
                if(item_ptr_vector[i] -> status == status){
                    if(t->has_print)
                        cout<<t->print<<endl;
                    if(t->has_action){
                        for(j = 0; j < t->action.size();j++){
                            game::checkAction(t->action[j]);
                        }
                    }
                    return true;
                }
            }
        }
    }
    if(object_type == "Container"){
        for(i = 0; i < container_ptr_vector.size(); i++){
            if(container_ptr_vector[i] -> name == object){
                if(container_ptr_vector[i] -> status == status){
                    if(t->has_print)
                        cout<<t->print<<endl;
                    if(t->has_action){
                        for(j = 0; j < t->action.size();j++){
                            game::checkAction(t->action[j]);
                        }
                    }
                    return true;
                }
            }
        }
    }
    if(object_type == "Creature"){
        for(i = 0; i < creature_ptr_vector.size(); i++){
            if(creature_ptr_vector[i] -> name == object){
                if(creature_ptr_vector[i] -> status == status){
                    if(t->has_print)
                        cout<<t->print<<endl;
                    if(t->has_action){
                        for(j = 0; j < t->action.size();j++){
                            game::checkAction(t->action[j]);
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}


bool trigger::check_wo_cmd(){
    //check all triggers and pick the triggers with no command
    //if it is permanent, continue, no worry
    //else if it is single, check if it has not been executed before
    //if it is 3-cond, go to ownerTrigger()
    //else if it is 2-cond, go to statusTrigger()
    int i,j,k;
    bool room_t = false;
    bool item_t = false;
    bool container_t = false;
    bool creature_t = false;
    Trigger *t;
    //current room trigger
    if(curr_room_ptr -> trigger.size() != 0){ //has triggers~
        for(j = 0; j < curr_room_ptr->trigger.size(); j++){
            t = curr_room_ptr->trigger[j];
            if(!t->has_command){
                if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                    if(t->condition == 3)
                        room_t = owner(t);
                    else if(t->condition == 2)
                        room_t = status(t);
                    if(room_t == true)
                        t->iterator++;
                }
            }
        }
    }
    //current room's item trigger
    for(i = 0; i < curr_room_ptr -> item.size(); i++){
        string target = curr_room_ptr -> item[i];
        for(j = 0; j < item_ptr_vector.size(); j++){
            if(item_ptr_vector[j] -> name == target){
                for(k = 0; k < item_ptr_vector[j] -> trigger.size(); k++){
                    t = item_ptr_vector[j] -> trigger[k];
                    if(!t->has_command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                item_t = owner(t);
                            else if(t->condition == 2)
                                item_t = status(t);
                            if(item_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    //current room's container trigger
    for(i = 0; i < curr_room_ptr -> container.size(); i++){
        string target = curr_room_ptr -> container[i];
        for(j = 0; j < container_ptr_vector.size(); j++){
            if(container_ptr_vector[j] -> name == target){
                for(k = 0; k < container_ptr_vector[j] -> trigger.size(); k++){
                    t = container_ptr_vector[j] -> trigger[k];
                    if(!t->has_command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                container_t = owner(t);
                            else if(t->condition == 2)
                                container_t = status(t);
                            if(container_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    //current room's creature trigger
    for(i = 0; i < curr_room_ptr -> creature.size(); i++){
        string target = curr_room_ptr -> creature[i];
        for(j = 0; j < creature_ptr_vector.size(); j++){
            if(creature_ptr_vector[j] -> name == target){
                for(k = 0; k < creature_ptr_vector[j] -> trigger.size(); k++){
                    t = creature_ptr_vector[j] -> trigger[k];
                    if(!t->has_command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                creature_t = owner(t);
                            else if(t->condition == 2)
                                creature_t = status(t);
                            if(creature_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    return (room_t||item_t||container_t||creature_t);
}

bool trigger::check_w_cmd(string input){
    int i,j,k;
    bool room_t = false;
    bool item_t = false;
    bool container_t = false;
    bool creature_t = false;
    Trigger *t;
    //current room trigger
    if(curr_room_ptr -> trigger.size() != 0){ //has triggers~
        for(j = 0; j < curr_room_ptr->trigger.size(); j++){
            t = curr_room_ptr->trigger[j];
            if(t -> has_command && input == t -> command){
                if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                    if(t->condition == 3)
                        room_t = owner(t);
                    else if(t->condition == 2)
                        room_t = status(t);
                    if(room_t == true)
                        t->iterator++;
                }
            }
        }
    }
    
    for(i = 0; i < inventory.size(); i++){
        string target = inventory[i];
        for(j = 0; j < item_ptr_vector.size(); j++){
            if(item_ptr_vector[j] -> name == target){
                for(k = 0; k < item_ptr_vector[j] -> trigger.size(); k++){
                    t = item_ptr_vector[j] -> trigger[k];
                    if(t -> has_command && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                item_t = owner(t);
                            else if(t->condition == 2)
                                item_t = status(t);
                            if(item_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    
    
    //current room's item trigger
    for(i = 0; i < curr_room_ptr -> item.size(); i++){
        string target = curr_room_ptr -> item[i];
        for(j = 0; j < item_ptr_vector.size(); j++){
            if(item_ptr_vector[j] -> name == target){
                for(k = 0; k < item_ptr_vector[j] -> trigger.size(); k++){
                    t = item_ptr_vector[j] -> trigger[k];
                    if(t -> has_command && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                item_t = owner(t);
                            else if(t->condition == 2)
                                item_t = status(t);
                            if(item_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    //current room's container trigger
    for(i = 0; i < curr_room_ptr -> container.size(); i++){
        string target = curr_room_ptr -> container[i];
        for(j = 0; j < container_ptr_vector.size(); j++){
            if(container_ptr_vector[j] -> name == target){
                for(k = 0; k < container_ptr_vector[j] -> trigger.size(); k++){
                    t = container_ptr_vector[j] -> trigger[k];
                    if(t -> has_command && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                container_t = owner(t);
                            else if(t->condition == 2)
                                container_t = status(t);
                            if(container_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    //current room's creature trigger
    for(i = 0; i < curr_room_ptr -> creature.size(); i++){
        string target = curr_room_ptr -> creature[i];
        for(j = 0; j < creature_ptr_vector.size(); j++){
            if(creature_ptr_vector[j] -> name == target){
                for(k = 0; k < creature_ptr_vector[j] -> trigger.size(); k++){
                    t = creature_ptr_vector[j] -> trigger[k];
                    if(t -> has_command && input == t -> command){
                        if(t->type == "permanent" || (t->type == "single" && t->iterator == 0)){
                            if(t->condition == 3)
                                creature_t = owner(t);
                            else if(t->condition == 2)
                                creature_t = status(t);
                            if(creature_t == true)
                                t->iterator++;
                        }
                    }
                }
            }
        }
    }
    return (room_t||item_t||container_t||creature_t);

}









