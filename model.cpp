//
// Created by 김유광 on 2017. 6. 17..
//

#include "model.h"

//Vote
Vote::Vote() {}

Vote Vote::getVote(int voteID) {
    Vote Vote;
    return Vote;
}

void Vote::deleteVote(int voteID) {

}

void Vote::saveItemData(int index){}
int Vote::getVoteID(){return voteID;}
char* Vote::getStartTime(){return getStartTime();}
char* Vote::getEndTime(){return getEndTime();}
bool Vote::checkVote(){return true;}


//User
User::User(){}

void User::authenticateUser(){
    loginStatus == true;
}
bool User::checkUserName(char* userName){
    if (userName == "kyk")
        return true;
    else
        return false;
}
bool User::changeUserStatus(){
    if( userID == 123 )
        return true;
    else
        return false;
}
bool User::checkUserPermission(){
    int groupID;
    GroupMember GroupMember;
    groupID = GroupMember.getGroupID();
    if (groupID == 2)
        return true;
    else
        return false;
}
void User::userJoinGroup(int groupID){}
int User::getUserID(){ return userID;}

//GroupMember
void GroupMember::removeGroupFromUser(){

}
int GroupMember::getGroupID(){ return groupID;}

//Group
void Group::removeUserFromGroup(int userID){}
list<int> Group::getGroupInfo(){ return getGroupInfo();}
int Group::getGroupId(){return groupID; }
string Group::getGroupName(){ return groupName; }