//
// Created by 최준성 on 2017. 6. 16..
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
    void authenticateUser();
    bool checkUserName(string userName);
    bool changeUserStatus();
    bool checkUserPermission();
    void userJoinGroup(int groupID);
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
    void removeUserFromGroup(int userID);
    list<int> getGroupInfo();
    int getGroupId();
    string getGroupName();

};



#endif //SEHW4_MODEL_H
