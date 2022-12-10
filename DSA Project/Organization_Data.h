#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <ios>
#include "Credentials.h"
#include <map>
#include "Citizens.h"
#include "Citizens_div.h"
#include "Reservation_data.h"

#define Passlength 6


struct Organization_Data{
    ResList list;
    std::string name, Location, ID;
    Credentials ctrd;
    Organization_Data* next;
    int no_of_app;
    Organization_Data(){
        next = NULL;
    }
    Organization_Data(Organization_Data& obj){
        name = obj.name;
        Location = obj.Location;
        ID = obj.ID;
        ctrd.username = obj.ctrd.username;
        next = NULL;
    }
    void input(Organization_Data& obj){
        std::cout << "Enter name of your organization: ";
        std::cin >> obj.name;
        std::cout << "Enter Location/Address of your organization: ";
        std::cin >> obj.Location;
        std::cout << "Enter Goverment issued ID of your organization: ";
        std::cin >> obj.ID;
        std::cout << "How many appointments dealt in one day ?: ";
        std::cin >> no_of_app;
        int h, m;
        for(int i = 0; i < no_of_app; i++){
            std::cout << "Enter hour and min in one sentence with space(24hrs format): ";
            std::cin >> h >> m;
            list.init(h, m);
        }
        std::cout << "Kindly Create your password(No spaces!!): ";
        std::cin >> obj.ctrd.password;
        obj.ctrd.username = obj.name;
        std::cout << obj.ctrd.password << std::endl;
        std::ofstream out;
        out.open("Organizations.txt", std::ios::app);
        out << obj.name << "\t" << obj.Location << "\t" << obj.ID << "\t" << obj.ctrd.password << std::endl;
        out.close();
    }
};