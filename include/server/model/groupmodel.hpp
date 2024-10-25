#ifndef GROUPMODEL_HPP
#define GROUPMODEL_HPP
#include "group.hpp"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
class GroupModel
{ 
public:
    //创建群组
    bool createGroup(Group &group);
    //加入群组
    void addGroup(int userid, int groupid,string role);
    //查询用户所在群组,这里返回的这个vector<Group>，里面的每一个group对象中有一个vector<GroupUser> users，里面存放的是这个群组中所有成员对象信息
    vector<Group> queryGroups(int userid);
    //根据指定的groupid查询群组用户id列表，除user自己，主要用户群聊业务给群组其他成员群发消息
    vector<int> queryGroupUsers(int groupid, int userid);

private:
   

   
};


#endif