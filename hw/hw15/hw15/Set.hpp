//
//  Set.hpp
//  hw15
//
//  Created by liang on 2016/11/2.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>




class Elements{
public:
    int value;
    Elements* next;
    Elements* prev;
    
    Elements(int n):value(n),next(NULL),prev(NULL){}
    Elements(int n, Elements* p_next):value(n), next(p_next), prev(NULL){}
    Elements(int n, Elements* p_next, Elements* p_prev):value(n) ,next(p_next), prev(p_prev){}
    
    
};

class Set{
private:
    Elements* head;
    int _search_duplicate_elements(Elements* ptr, int num_checked);
    Elements* _return_element_pos(Elements* ptr, int num_checked);
    
public:
    Set(){}
    Set(int n);
    void add_elements(Elements* head, int num);
    void del_elements(Elements* head, int num);
    Set* and_set(Elements* head_1, Elements* head_2);
    Set* complement_set(Elements* head);
    Set* diff_set(Elements* head_1, Elements* head_2);
    void print_out_set(Set* set);
    
};
#endif /* Set_hpp */
