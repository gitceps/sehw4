//
// Class : Vote, User, Group
// Description : 투표 정보를 나타낼 수 있는 Vote, 현재 회원 정보를 나타내는 User, 그룹 정보를 나타내는 Group 등의
//               Entity 클래스들이 정의되어있다
// Created : 2017. 6. 16..
// Author : 최준성
//

#ifndef SEHW4_MODEL_H
#define SEHW4_MODEL_H
#include <clocale>
#include <string>
#include <list>

using namespace std;

class Vote {
private:
    int voteID;
    int groupID;
    int voteCreatorID;
    string title;
    list<string> option;
    list<int> count;
    char* startTime, endTime;

public :
    Vote();
    Vote getVote(int voteID);
    void deleteVote(int voteID);
    void saveItemData(int index);
    int getVoteID();
    char* getStartTime();
    char* getEndTime();
    bool checkVote();
};

class User {
private:
    int userID;
    string userName;
    string userRealName;
    string email;
    string address;
    string idCardNumber;
    bool loginStatus = false;

public:
    User();
    User(string userName);
    void authenticateUser();
    bool checkUserName(string userName);
    bool changeUserStatus();
    bool checkUserPermission();
    void userJoinGroup(int groupID);
    string getUserName();
    int getUserID();
};

class GroupMember : public User {
private:
    int groupID = 0;
    bool isCreator = false;

public:
    void removeGroupFromUser();
    int getGroupID();
};

class Group{
private:
    int groupID;
    int groupCreatorID;
    list<int> groupMemberList;
    string groupName;

public:
    Group(int groupID);
    void removeUserFromGroup(int userID);
    list<int> getGroupInfo();
    int getGroupId();
    string getGroupName();

};



#endif //SEHW4_MODEL_H
