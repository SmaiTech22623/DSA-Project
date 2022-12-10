#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <ncurses.h>

#include "Credentials.h"
#include "Citizens_div.h"
#include "Citizens.h"
#include "Organization_Data.h"
#include "Organization.h"
#include "Manager.h"
#include "Manager_data.h"
#include "chat.h"

#if _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

Citizens_div* initC(Citizens_div* root, Citizens_div &obj){
    Citizens_div* head = root;
    if(root == NULL){
        root = new Citizens_div();
        root->age = obj.age;
        root->symptoms = obj.symptoms;
        root->name = obj.name;
        root->CNIC = obj.CNIC;
        return root;
    }
    if(obj.age > root->age){
        root->less = initC(root->less, obj);
    }
    else if(obj.age <= root->age){
        root->greater = initC(root->greater, obj);
    }
    return root;
}
Citizens_div* search(Citizens_div* root, int age, std::string CNIC){
    if(root == NULL){ return NULL; }
    if(root->age == age && root->CNIC == CNIC){
        return root;
    }
    else if(age > root->age){
        return search(root->greater, age, CNIC);
    }
    else if(age <= root->age){
        return search(root->less, age, CNIC);
    }
    return root;
}
int main(){
    int programcheck;
    Organization orgs;
    Citizens citi;
    Credentials ctrd;
    Manager managers;
    Chat chatting;
    std::ifstream firstcheck;
    firstcheck.open("programcheck.txt", std::ios::in);
        firstcheck >> programcheck;
        firstcheck.close();
        if(programcheck == 1){
            std::cout << "Program is running first time on your system\n" << "We will need some information for registeration will not happen on second run\n";
            usleep(3000*1000);
            system("clear");
            std::cout << "What are your usage of program: ";
            mainmenu:
            std::cout << "\n1-Organization\n2-Citizen\n3-Apply for manager of organization\nEnter your choice: ";
            int choice;
            std::cin >> choice;
            switch(choice){
                case 1:{
                    system("clear");
                    Organization_Data data;
                    data.input(data);
                    orgs.init(data);
                    usleep(5000*1000);
                    system("clear");
                    break;
                }
                case 2:{
                    Citizens_div obj;
                    obj.input();
                    Citizens_div* root = citi.getroot();
                    root = initC(root, obj);
                    usleep(5000*1000);
                    system("clear");
                    break;
                }
                case 3:{
                    Manager_data data;
                    data.input(orgs);
                    managers.init(data);
                    usleep(3000*1000);
                    system("clear");
                }
                default:{
                    system("clear");
                    std::cout << "Wrong choice Entered\nEnter again: ";
                    goto mainmenu;
                }
            }
            std::ofstream out("programcheck.txt", std::ios::trunc);
            programcheck++;
            out << programcheck;
        }
        else
        {
            std::ifstream in;
            in.open("Organizations.txt", std::ios::in);
            if(in){
            Organization_Data dataO;
            while(!in.eof()){
            in >> dataO.name;
            in >> dataO.Location;
            in >> dataO.ID;
            in >> dataO.ctrd.password;
            orgs.init(dataO);
            }
            }
            in.close();
            in.open("Citizens.txt", std::ios::in);
            Citizens_div dataC;
            Citizens_div* root = citi.getroot();
            if(in){
            while(!in.eof()){
                in >> dataC.name;
                in >> dataC.CNIC;
                in >> dataC.age;
                in >> dataC.symptoms;
                in >> dataC.vacc;
                root = initC(root, dataC);
            }
            }
            in.close();
            in.open("Manager.txt", std::ios::in);
            if(in){
            Manager_data dataM;
            while(!in.eof()){
                in >> dataM.name;
                in >> dataM.CNIC;
                in >> dataM.Organization;
                in >> dataM.ID;
                managers.init(dataM);
            }
            }
            in.close();
            in.open("Chat.txt", std::ios::in);
            if(in){
            std::string t, m;
            while(!in.eof()){
                std::getline(in, t);
                std::getline(in, m);
                if(t != "\n")
                chatting.recoverchat(t, m);
            }
            }
            main:
            std::cout << "1-Organization Login\n2-Citizen Login\n3-Manager Login\nEnter your choice: ";
            int choice;
            std::cin >> choice;
            switch(choice){
                case 1:{
                    Orgslogin:
                    usleep(3000*1000);
                    system("clear");
                    std::cout << "Enter username: ";
                    std::cin >> ctrd.username;
                    std::string cpass = orgs.searchPass(ctrd.username);
                    if(cpass.compare("")==0){
                        system("clear");
                        std::cout << "No such Organization found in data\n1-Register this organization\n2-Try Again\nEnter choice: ";
                        int choice1; 
                        std::cin >> choice1;
                        switch(choice1){
                            case 2:{
                                system("clear");
                                goto Orgslogin;
                                break;
                            }
                            case 1:{
                                system("clear");
                                Organization_Data data;
                                data.input(data);
                                orgs.init(data);
                                usleep(5000*1000);
                                system("clear");
                                break;
                            }
                        }
                        goto main;
                    }
                    else{
                        passwd:
                        std::cout << "Enter password: ";
                        std::cin >> ctrd.password;
                        if(ctrd.password.compare(cpass) != 0){
                            std::cout << "Wait while your account is loading!!!!\n";
                            usleep(2000*1000);
                            system("clear");
                            std::cout << "Welcome!\n";
                            orgmenu:
                            std::cout << "1-See all reservation\n2-Chat\n3-Logout\nEnter yout choice: ";
                            int orgch; std::cin >> orgch;
                            switch(orgch){
                                case 2:{
                                    system("clear");
                                    chatting.init(ctrd.username);
                                    goto orgmenu;
                                }
                                case 3:{
                                    goto main;
                                }
                            }
                        }
                        else{
                            std::cout << "Wrong password entered\n";
                            usleep(2000*1000);
                            system("clear");
                            goto passwd;
                        }
                    }
                }
                case 2:{
                    system("clear");
                    CitiLogin:
                    std::cout << "Enter your name: ";
                    std::cin.ignore();
                    std::getline(std::cin, ctrd.username);
                    std::cout << "Enter your age that you gave to us: ";
                    int age; std::cin >> age;
                    std:: cout << "Enter your CNIC: ";
                    std::cin.ignore(); 
                    std::getline(std::cin, ctrd.password);
                    Citizens_div* temp = search(root, age, ctrd.password);
                    if(temp == NULL){ 
                        std::cout << "No such citizen found\nWant to register ?(Y/N): ";
                        char citichoice; std::cin >> citichoice;
                        switch(citichoice){
                            case 'y':
                            case 'Y':{
                                Citizens_div obj;
                                obj.name = ctrd.username;
                                obj.CNIC = ctrd.password;
                                obj.age = age;
                                std::cout << "Are you showing any symptoms of COVID-19 (Y/N): "; choice: char ch; std::cin >> ch;
                                switch(ch){
                                    case 'y':
                                    case 'Y':{
                                        obj.symptoms = true;
                                        break;
                                    }
                                    case 'n':
                                    case 'N':{
                                        obj.symptoms = false;
                                        break;
                                    }
                                }
                                std::cout << "Are you vaccinated: ";
                                char ch1; std::cin >> ch1;
                                switch(ch1){
                                    case 'y':
                                    case 'Y':{
                                        obj.vacc = true;
                                        break;
                                    }
                                    case 'n':
                                    case 'N':{
                                        obj.vacc = false;
                                        break;
                                    }
                                }
                                //obj.input();
                                root = initC(root, obj);
                                obj.write();
                                usleep(5000*1000);
                                system("clear");
                                goto main;
                            }
                            case 'n':
                            case 'N':
                            {
                                goto main;
                            }
                        }
                    }
                    else{
                        system("clear");
                        std::cout << "Wait while we load your account!!!\n";
                        usleep(2000*1000);
                        system("clear");
                        citimenu:
                        std::cout << "Welcome\n";
                        if(temp->vacc == false){
                            std::cout << "You are not yet vaccinated\n";
                            std::cout << "1-Chat\n2-Reserve a center\nEnter choice: ";
                            int citich; std::cin >> citich;
                            switch(citich){
                                case 1:{
                                    system("clear");
                                    chatting.init(ctrd.username);
                                    goto citimenu;
                                }
                                case 2:{
                                    system("clear");
                                    std::cout << "Available centers: \n";
                                    orgs.printOrg();
                                }
                            }
                        }
                    }
                }
            }
        }
}