//
//  Pet.cpp
//  Hw14
//
//  Created by liang on 2016/11/2.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Pet.hpp"


Pet::Pet(string name):Canine(name){}

ostringstream Pet::return_breed(){
    ostringstream output_s;
    output_s<<"AKC:"<<Canine::return_breed().str();
    
    return output_s;
}
