#pragma once
#include "Citizens_div.h"

class Citizens{
    Citizens_div* root;
public:
    Citizens(){
        root = NULL;
    }
    Citizens_div* getroot(){ return root; }
};