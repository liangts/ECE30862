//
//  Mammal.hpp
//  Hw14
//
//  Created by liang on 2016/11/1.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Mammal_hpp
#define Mammal_hpp


#include <iostream>
using namespace std;

class Mammal{
private:
    const int legs;
public:
    Mammal(const int num): legs(num){}
    virtual ~Mammal();
    int getlegs();
};


#endif /* Mammal_hpp */
