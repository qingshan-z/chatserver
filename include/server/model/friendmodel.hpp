#ifndef FRIENDMODEL_H
#define FRIENDMODEL_H

#include "user.hpp"
#include <vector>

using namespace std;
//维护好友信息地操作接口方法
class Friendmodel
{
private:
    /* data */
public:
    //添加好友关系
    void insert(int userid, int friendid);

    //返回用户好友列表  通过用户id，找到好友列表
    vector<User> query(int userid);
};

#endif