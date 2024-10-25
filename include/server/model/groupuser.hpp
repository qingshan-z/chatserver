#ifndef GROUPUSER_HPP
#define GROUPUSER_HPP
#include "user.hpp"

//派生类 多了一个role角色信息，从user类直接继承，复用user的其他信息
class GroupUser: public User
{
public:
    void setRole(string role){
        this->role = role;
    }

    string getRole(){
        return this->role;
    }
private:
    string role;  
};






#endif