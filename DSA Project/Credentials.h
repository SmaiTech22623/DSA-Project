#pragma once

struct Credentials{
    std::string username, password;
    Credentials(){
        username = password = '\0';
    }
};