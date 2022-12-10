#pragma once
#include <cstring>
#include <iostream>
#include <fstream>
#include "Credentials.h"
#include "Organization.h"
#include "Organization_Data.h"


struct Manager_data{
    std::string name, CNIC, Organization, ID;
    Manager_data* next;
    void write(){
        std::ofstream out("Manager.txt", std::ios::app);
        out << name << "\t" << CNIC << "\t" << Organization << "\t" << ID << std::endl;
        out.close();
    }
    void input(struct Organization obj){
        std::cout << "Enter Name: "; std::cin >> name;
        std::cout << "Enter CNIC: "; std::cin >> CNIC;
        std::cout << "Enter name of organization you want to apply for: "; choice: std::cin.ignore(); getline(std::cin, Organization);
        if(obj.search(Organization)){
            this->write();
        }
        else{
            std::cout << "No Such Organization Found in records\nWant to try again ? (Y/N): ";
            char ch;
            std::cin >> ch;
            switch(ch){
                case 'y':
                case 'Y':{
                    std::cout << "Enter again: ";
                    goto choice;
                }
            }
        }
    }
};