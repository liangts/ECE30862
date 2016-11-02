//
//  main.cpp
//  Hw14
//
//  Created by liang on 2016/11/1.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "Mammal.hpp"
#include "Canine.hpp"
#include "Pet.hpp"

string getStringStream(ostringstream s){
    return s.str();
}

int main(int argc, const char * argv[]) {
//    Mammal* test = new Mammal(5);
//    Canine* testCanine = new Canine("test_breed");
    
    Pet* testPet = new Pet("breed_name");

    /*
    The functions which return the name of the Pet/Canine is not type string!
     The type of return is ostringstream
     
     Use the function above getStringStream to return a string
     
     or
     
     do something like return_breed().str()
                                       ^     make sure you have ".str()"
     
     */
    
    
    cout<<getStringStream(testPet->return_breed())<<endl;
    cout<<testPet->getlegs()<<endl;
    cout<<getStringStream(testPet->Canine::return_breed())<<endl;
    cout<<testPet->Mammal::getlegs()<<endl;
    
    return 0;
}
