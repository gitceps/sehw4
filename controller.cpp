//
// Created by 김유광 on 2017. 6. 17..
//

#include "controller.h"
#include "view.h"
#include <iostream>

using namespace std;

//UserController
UserController UserController::getInstance(){
    UCInstance = new UserController;
    return *UCInstance;
}

bool UserController::isValidUser(int userID, string password){
    if (userID == 123 && password == "1")
        return true;
    else
        return false;
}

void UserController::validdateUserInfo(int userID, string password){
    bool ivu;
    ivu = isValidUser(userID,password);
    if(ivu == true){
        User User;
        User.User();
        User.authenticateUser();
    }
    else
        return;

}

void UserController::deleteUserSession(int userID){
    User User;
    User.changeUserStatus();
}

void UserController::createUser(){
    UserViewUI UserViewUI;
    UserViewUI.userDataInput();
    return;
}

bool UserController::getOverlapCheck(string userName){
    if (userName == "kyk")
        return true;
    else
        return false;
}

void UserController::setUserData(string userID, string userName, string userRealName,string emali, string address, string idCardNumber){

}
void UserController::deleteUser(int userID){

}


//GroupController
GroupController GroupController::getInstance(){
    GCInstance = new GroupController;
    return *GCInstance;
}

//getGroupInfo 시퀀스와 일치하지 않음
void GroupController::showAllGroup(){

}

//userjoingroup 함수 없음
void GroupController::joinGroup(int userID, int groupID){

}
void GroupController::createGroup(){
    GroupViewUI GroupViewUI;
    GroupViewUI.groupDataInput();
    return;
}

bool GroupController::getOverlapCheck(string groupName){
    if (groupName == "kyk")
        return true;
    else
        return false;
}

void GroupController::setGroupData(int creatorID, int groupID, string groupName){}


//VoteController
VoteController VoteController::getInstance(){
    VCInstance = new VoteController;
    return *VCInstance;
}
list<Vote> VoteController::showOngoingVote(){
    list<Vote> Vote;
    return Vote;}
list<Vote> VoteController::showScheduleVote(){
    list<Vote> Vote;
    return Vote;}
list<Vote> VoteController::showTerminatedVote(){
    list<Vote> Vote;
    return Vote;}
Vote VoteController::getVote(int voteID){
    Vote Vote;
    return Vote;
}
void VoteController::saveItemData(int voteID, int index){}
void VoteController::deleteVote(int voteID){}
list<Vote> VoteController::getTerminatedVoteDetails(){
    list<Vote> Vote;
    return Vote;
}
list<Vote> VoteController::getOngoingVoteDetails(){
    list<Vote> Vote;
    return Vote;
}
list<Vote> VoteController::getScheduledVoteDetails(){
    list<Vote> Vote;
    return Vote;
}
void VoteController::checkVote(){}

bool Timer::checkEndTime(){ return true;}

//ApplicationController
ApplicationController ApplicationController::getInstance(){
    ACInstance = new ApplicationController;
    return *ACInstance;
}
void ApplicationController::terminateProcess(){}
void ApplicationController::deleteVote(){}
