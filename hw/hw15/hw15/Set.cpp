//
//  Set.cpp
//  hw15
//
//  Created by liang on 2016/11/2.
//  Copyright © 2016年 Tianshu. All rights reserved.
//

#include "Set.hpp"
#include <stdio.h>

int Set::_search_duplicate_elements(Elements* ptr, int num_checked){
    
    int duplicated = 0;
    
    if (ptr->next != NULL){
        duplicated = _search_duplicate_elements(ptr ->next, num_checked);
    }
    
    if (num_checked == ptr->value)
        duplicated = 1;
    return duplicated;
}

Elements* Set::_return_element_pos(Elements* ptr, int num_checked){
    if (num_checked == ptr->value)
        return ptr;
    
    if (ptr->next != NULL){
        _return_element_pos(ptr->next, num_checked);
    }
    
    return NULL;
    
}

Set::Set(int n){
    Elements* new_Elements = new Elements(n);
    Set* new_Set = new Set();
    new_Set->head = new_Elements;
}

void Set::add_elements(Elements* head, int num){
    if (_return_element_pos(head, num) == NULL){
        Elements* new_elements = new Elements(num, head);
        head->prev = new_elements;
        head = new_elements;
    }
}

void Set::del_elements(Elements *head, int num){
    Elements* tmp = _return_element_pos(head, num);
    if (tmp != NULL){
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        delete tmp;
    }
}

Set* Set::and_set(Elements *head_1, Elements *head_2){
    Elements* ptr1 = head_1;
    Elements* ptr2 = head_2;
    Set* new_Set = NULL;
    
    while (ptr2 != NULL) {
        if (_return_element_pos(ptr1, ptr2->value) != NULL){
            if (new_Set == NULL)
                new_Set = new Set(ptr2->value);
            else
                new_Set->add_elements(new_Set->head, ptr2->value);
        }
        ptr2 = ptr2->next;
    }
    
    return new_Set;
}

Set* Set::complement_set(Elements *head){
    Set* new_Set = NULL;
    for (int i = 0 ; i < 64; i++) {
        if (_return_element_pos(head, i) == NULL){
            if (new_Set == NULL)
                new_Set = new Set(i);
            else
                new_Set->add_elements(new_Set->head, i);
        }
    }
    
    return new_Set;
}

Set* Set::diff_set(Elements *head_1, Elements *head_2){
    Elements* ptr1 = head_1;
    Elements* ptr2 = head_2;
    Set* new_Set = NULL;
    
    while (ptr2 != NULL) {
        if (_return_element_pos(ptr1, ptr2->value) == NULL){
            if (new_Set == NULL)
                new_Set = new Set(ptr2->value);
            else
                new_Set->add_elements(new_Set->head, ptr2->value);
        }
        ptr2 = ptr2->next;
    }
    
    return new_Set;
}

void Set::print_out_set(Set *set){
    Elements* ptr = set -> head;
    printf("The set is :");
    while (ptr != NULL) {
        printf("%d, ", ptr->value);
        ptr = ptr->next;
    }
    printf("\n");
}




