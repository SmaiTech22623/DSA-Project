#pragma once
#include "Manager_data.h"

class Manager{
    struct Manager_data* head, *end;
public:
    Manager(){
        head = NULL;
    }
    void init(struct Manager_data obj){
        Manager_data* newmanager= new Manager_data();
        newmanager->ID = obj.ID;
        newmanager->CNIC = obj.CNIC;
        newmanager->name = obj.name;
        newmanager->Organization = obj.Organization;
        if(head == NULL){
            head = end = newmanager;
            return;
        }
        end->next = newmanager;
        end = newmanager;
    }
};