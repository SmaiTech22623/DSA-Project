#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <iterator>
#include <cstring>
#include <ios>

struct chatinfo{
    std::string key, value;
};

struct Chat{
    std::vector<chatinfo> chat;
    Chat(){}
    void printchat(){
        for(int i = 0; i < chat.size(); i++){
            std::cout << chat[i].key << ": " << chat[i].value << std::endl;
        }
    }
    void write(){
        std::ofstream out("Chat.txt", std::ios::out);
            for(int i = 0; i < chat.size(); i++){
                if(i == chat.size() - 1)
                out << chat[i].key << "\n" << chat[i].value;
                else
                out << chat[i].key << "\n" << chat[i].value << std::endl;
            }
        }
    void recoverchat(std::string title, std::string msg){
        chatinfo temp;
        temp.key = title;
        temp.value = msg;
        chat.push_back(temp);
    }
    void init(std::string title){
        int i = 0;
        this->printchat();
        chatinfo temp;
        temp.key = title;
        chatstart:
        std::string msg;
        std::cout << "Enter message: ";
        if(i == 0){std::cin.ignore(); i++;}
        getline(std::cin, msg);
        if(msg.compare("close chat") == 0){ system("clear"); return; }
        if(msg.compare("delete chat") == 0){
            system("clear");
            for(int i = 0; i < chat.size(); i++){
                if(chat[i].key == title){
                    std::cout << chat[i].key << ": " << chat[i].value << std::endl; 
                }
                else{
                    continue;
                }
            }
        }
        temp.value = msg;
        chat.push_back(temp);
        system("clear");
        this->printchat();
        this->write();
        goto chatstart;
    }
};