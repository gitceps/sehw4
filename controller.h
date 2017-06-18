//
// Created by 최준성 on 2017. 6. 16..
//

#ifndef SEHW4_CONTROLLER_H
#define SEHW4_CONTROLLER_H

#include <MacTypes.h>
#include <string>
#include "model.h"
#include <list>

using namespace std;

class UserController{
private:
    UserController *UCInstance;
public:
    UserController getInstance();
    bool isValidUser(int userID, string password);
    void validdateUserInfo(int userID, string password);
    void deleteUserSession(int userID);
    void createUser();
    bool getOverlapCheck(string userName);
    void setUserData(string userID, string userName, string userRealName,string emali, string address, string idCardNumber);
    void deleteUser(int userID);
};

class GroupController{
private:
    GroupController *GCInstance;
public:
    GroupController getInstance();
    void showAllGroup();
    void joinGroup(int userID, int groupID);
    void createGroup();
    bool getOverlapCheck(string groupName);
    void setGroupData(int creatorID, int groupID, string groupName);
};

class VoteController{
private:
    VoteController *VCInstance;
    Vote voteList;
public:
    VoteController getInstance();
    list<Vote> showOngoingVote();
    list<Vote> showScheduleVote();
    list<Vote> showTerminatedVote();
    Vote getVote(int voteID);
    void saveItemData(int voteID, int index);
    void deleteVote(int voteID);
    list<Vote> getTerminatedVoteDetails();
    list<Vote> getOngoingVoteDetails();
    list<Vote> getScheduledVoteDetails();
    void checkVote();

};

class Timer{
public:
    bool checkEndTime();
};

class ApplicationController {
private:
    ApplicationController *ACInstance;

public:
    ApplicationController getInstance();

    void terminateProcess();

    void deleteVote();
};

#endif //SEHW4_CONTROLLER_H
