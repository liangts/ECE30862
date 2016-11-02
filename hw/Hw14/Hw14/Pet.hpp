//
//  Pet.hpp
//  Hw14
//
//  Created by liang on 2016/11/2.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Pet_hpp
#define Pet_hpp
#include <string>
#include "Canine.hpp"
#include <sstream>
class Pet : public Canine{
public:
    Pet(string name);
    ostringstream return_breed();
    
};
#endif /* Pet_hpp */
