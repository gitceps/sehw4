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
    User *currentUser = NULL;
    static UserController *ucInstance;
    UserController(){};
public:
    static UserController* getInstance();
    User* getCurrentUser();
    bool isValidUser(string userID, string password);
    void validateUserInfo(string userName, string password);
    void deleteUserSession(int userID);
    void createUser();
    bool getOverlapCheck(string userName);
    void setUserData(string userID, string userName, string password, string userRealName,string email, string address, string idCardNumber);
    void deleteUser(string userName);
};

class GroupController{
private:
    static GroupController *gcInstance;
    GroupController(){};
public:
    static GroupController* getInstance();
    void showAllGroup();
    void joinGroup(string userName, int groupID);
    void createGroup();
    bool getOverlapCheck(string groupName);
    void setGroupData(string creatorName, int groupID, string groupName);
};

class VoteController{
private:
    static VoteController *vcInstance;
    Vote voteList;
    VoteController(){};
public:
    static VoteController* getInstance();
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
    void showVoteData(); // 시퀀스 다이어 그램에 있으나 클래스 다이어 그램에 빠져있음
    void addNewVote(); // 시퀀스 다이어 그램에 있으나 클래스 다이어 그램에 빠져있음
};

class Timer{
public:
    bool checkEndTime();
};

class ApplicationController {
private:
    static ApplicationController *acInstance;
    ApplicationController();

public:
    static ApplicationController* getInstance();
    void terminateProcess();
    void deleteVote();
};

#endif //SEHW4_CONTROLLER_H
