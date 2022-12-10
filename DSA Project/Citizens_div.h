#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#include "Credentials.h"

struct Citizens_div{
    double age;
    std::string name, CNIC;
    bool symptoms, vacc;
    struct Credentials ctrd;
    struct Citizens_div* less;
    struct Citizens_div* greater;
    Citizens_div(){
        less = greater = NULL;
    }
    void input(){
        std::cout << "Enter name: "; std::cin >> name;
        std::cout << "Enter CNIC without dashes(-): "; std::cin >> CNIC;
        std::cout << "Enter age: "; std::cin >> age;
        std::cout << "Are you showing any symptoms of COVID-19 (Y/N): "; choice: char ch; std::cin >> ch;
        std::cout << "Are you vaccinated: ";
        char ch1; std::cin >> ch1;
        switch(ch1){
            case 'y':
            case 'Y':{
                vacc = true;
                break;
            }
            case 'n':
            case 'N':{
                vacc = false;
                break;
            }
        }
        ctrd.password = CNIC;
        ctrd.username = name;
        switch(ch){
            case 'y':
            case 'Y':{
                symptoms = true;
                break;
            }
            case 'n':
            case 'N':{
                symptoms = false;
                break;
            }
            default:
            {
                std::cout << "Wrong choice entered, Enter again: ";
                goto choice;
            }
        }
        std::ofstream out;
        out.open("Citizens.txt", std::ios::app);
        out << name << "\t" << CNIC << "\t" << age << "\t" << symptoms << "\t"<< vacc << std::endl;
    }
    void write(){
        std::ofstream out;
        out.open("Citizens.txt", std::ios::app);
        out << name << "\t" << CNIC << "\t" << age << "\t" << symptoms << "\t"<< vacc << std::endl;
    }
};