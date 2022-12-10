#pragma once
#include "Citizens_div.h"
#include <cstring>


struct Res_Data{
    int hour, min;
    bool flag;
   std::string CNIC, name;
    Res_Data* next;
    Res_Data(){ next = NULL; }
};
struct ResList{
    Res_Data* head, *end;
public:
    ResList(){
        head = end = NULL;
    }
    void init(int h, int m){
        Res_Data* newdata = new Res_Data();
        newdata->flag = false;
        newdata->hour = h;
        newdata->min = m;
        if(head == NULL){
            head = end = newdata;
            return;
        }
        end->next = newdata;
        end = newdata;
    }
    void reservation(int h, int m, std::string CNIC, std::string name){
        Res_Data* curr = head;
        while(curr != NULL){
            if(curr->hour == h && curr->min == m){
                curr->CNIC = CNIC;
                curr->name = name;
                curr->flag = true;
            }
        }
    }
    void print(){
        Res_Data* curr = head;
        while(curr != NULL){
            if(curr->flag == false){
                std::cout << curr->hour << " : " << curr->min <<std::endl;
            }
        }
    }
};