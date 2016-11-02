//
//  Canine.hpp
//  Hw14
//
//  Created by liang on 2016/11/1.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Canine_hpp
#define Canine_hpp

#include "Mammal.hpp"
#include <string>
#include <sstream>

using namespace std;

class Canine : public Mammal{
private:
    string breed;
public:
    Canine(string name):Mammal(4), breed(name){}
    virtual ~Canine();
//    int getlegs();
    virtual ostringstream return_breed();
    
    
};


#endif /* Canine_hpp */
