#pragma once
class Organization{
    struct Organization_Data* head, *end;
public:
    Organization(){
        head = NULL;
        end = NULL;
    }
    void init(Organization_Data& data){
        struct Organization_Data* newdata = new Organization_Data(data);
        if(head == NULL && end == NULL){
            head = newdata;
            end = newdata;
            return;
        }
        end->next = newdata;
        end = newdata;
        return;
    }
    bool search(std::string n){
        struct Organization_Data* curr = head;
        while(curr != NULL){
            if(n.compare(curr->name) == 0){
                return true;
            }
            curr = curr->next;
        }
        return false;
    }
    std::string searchPass(std::string n){
        struct Organization_Data* curr = head;
        while(curr != NULL){
            if(n.compare(curr->name) == 0){
                return curr->ctrd.password;
            }
            curr = curr->next;
        }
        return "";
    }
    void printOrg(){
        Organization_Data* curr = head;
        int i = 1;
        int counter = 1;
        while(curr != NULL){
            std::cout << i << "- " << curr->name << std::endl;
            i++;
            curr = curr->next;
        }
        std::cout << "Enter name: ";
        std::string tempname; std::cin >> tempname;
        curr = head;
        while(curr->name != tempname){
            curr = curr->next;
            counter++;
        }
        std::cout << "Available time slots: \n";
        curr = head;
        /*while(curr != NULL){
            if(curr->li == false){
                std::cout << curr->hour << " : " << curr->min <<std::endl;
            }
        }*/
    }
};
