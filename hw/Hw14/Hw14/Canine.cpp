//
//  Canine.cpp
//  Hw14
//
//  Created by liang on 2016/11/1.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Canine.hpp"
Canine::~Canine(){
    
}
/*
int Canine::getlegs(){
    return legs;
}
*/
ostringstream Canine::return_breed(){
    ostringstream output_s;
    output_s<<breed;
    
    return output_s;
}

