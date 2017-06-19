//
// Created by 김유광 on 2017. 6. 17..
//

#include "controller.h"
#include "view.h"

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <mysql++/mysql++.h>
using namespace std;
using namespace mysqlpp;

#define DBNAME "sys"
#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""

//UserController
UserController UserController::getInstance(){
    UCInstance = new UserController;
    return *UCInstance;
}

bool UserController::isValidUser(string userName, string password){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "select * from user where userName = '";
        temp += userName;
        temp += "' and password = '";
        temp += password;
        temp += "'";
        //cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
            if(res.num_rows() == 0) {
                return false;
            }
            else {
                return true;
            }
        }
        else {
            cerr << query.error() << endl;
            return false;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}

void UserController::validateUserInfo(string userName, string password) {
    bool ivu;
    ivu = isValidUser(userName,password);
    if(ivu == true){
        User User;
        User.authenticateUser();
        UserViewUI UserViewUI;
        UserViewUI.showLoginResultMessage();
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
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "select * from user where userName = '";
        temp += userName;
        temp += "'";
        cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
            if(res.num_rows() != 0) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            cerr << query.error() << endl;
            return false;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}

void UserController::setUserData(string userID, string userName, string password, string userRealName,string email, string address, string idCardNumber){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "insert into user(userName,password,address,email,idCardNumber,userRealName) values('";
        temp += userName;
        temp += "', '";
        temp += password;
        temp += "', '";
        temp += address;
        temp += "', '";
        temp += email;
        temp += "', '";
        temp += idCardNumber;
        temp += "', '";
        temp += userRealName;
        temp += "')";
        //cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {

        } else {
            cerr << query.error() << endl;
        }
    }  catch (Exception &e) {
            cout << e.what() << endl;
    }

}

void UserController::setUser() {
    currentUser = new User();
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
    return Vote;
}
list<Vote> VoteController::showScheduleVote(){
    list<Vote> Vote;
    return Vote;
}

list<Vote> VoteController::showTerminatedVote(){
    list<Vote> Vote;
    return Vote;
}

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

void VoteController::showVoteData(){
    AddVoteUI AddVoteUI;
    AddVoteUI.createNewVote();
} // 시퀀스 다이어 그램에 있으나 클래스 다이어 그램에 빠져있음
void VoteController::addNewVote(){} // 시퀀스 다이어 그램에 있으나 클래스 다이어 그램에 빠져있음

bool Timer::checkEndTime(){ return true;}

//ApplicationController
ApplicationController ApplicationController::getInstance(){
    if(acInstance == null)
        acInstance = new ApplicationController();
    else
        return *acInstance;
}
ApplicationController::ApplicationController() {}
void ApplicationController::terminateProcess(){
    exit(0);
}
void ApplicationController::deleteVote(){}
