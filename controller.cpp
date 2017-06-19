//
// Created by 김유광 on 2017. 6. 17..
//

#include "controller.h"
#include "view.h"

#include <iostream>
#include <mysql++/mysql++.h>
using namespace std;
using namespace mysqlpp;

#define DBNAME "sys"
#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""

//UserController
UserController* UserController::ucInstance = NULL;
UserController* UserController::getInstance(){
    if(ucInstance == NULL) {
        ucInstance = new UserController();
    } else
        return ucInstance;
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
        ucInstance->currentUser = new User(userName);
        ucInstance->currentUser->authenticateUser();

        UserViewUI UserViewUI;
        UserViewUI.showLoginResultMessage();
    }
    else {
        cout << "로그인 정보가 올바르지 않습니다" << endl;
        return;
    }

}

User* UserController::getCurrentUser() {
    return currentUser;
}

void UserController::deleteUserSession(int userID){
    User User;
    User.changeUserStatus();
    ApplicationController::getInstance()->terminateProcess();
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
        //cout << temp << endl;

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

void UserController::deleteUser(string userName){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "delete from user where userName = '";
        temp += userName;
        temp += "'";
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

    cout << "회원 탈퇴가 완료 되었습니다" << endl;

}


//GroupController
GroupController* GroupController::gcInstance = NULL;
GroupController* GroupController::getInstance(){
    if(gcInstance == NULL)
        gcInstance = new GroupController();
    else
        return gcInstance;
}

//getGroupInfo 시퀀스와 일치하지 않음
void GroupController::showAllGroup(){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        Query query = con.query("select * from sys.group");
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
            // Display header
            cout.setf(ios::left);
            cout << "  groupID" << setw(19) << " " << "groupName" << setw(19) << " " << "groupCreatorID" << endl << endl;

            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) {
                cout << "  " << res[i]["groupID"] <<  setw(20) << "   " << res[i]["groupName"] << setw(20) << "   " << res[i]["groupCreatorID"]<< endl;
            }
            cout << "==========================" << endl;
        }
        else {
            cerr << query.error() << endl;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}

//userjoingroup 함수 없음
void GroupController::joinGroup(string userName, int groupID){
    User* currentUser = UserController::getInstance()->getCurrentUser();
    if (currentUser == NULL) {
        cout << "로그인을 먼저 해주세요" << endl;
        return;
    }
}

void GroupController::createGroup(){
    GroupViewUI GroupViewUI;
    GroupViewUI.groupDataInput();
    return;
}

bool GroupController::getOverlapCheck(string groupName){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "select * from sys.group where groupName = '";
        temp += groupName;
        temp += "'";
        //cout << temp << endl;

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

void GroupController::setGroupData(string creatorName, int groupID, string groupName){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "insert into sys.group(groupName, groupCreatorID) values('";
        temp += groupName;
        temp += "', '";
        temp += creatorName;
        temp += "')";
        //cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();
        cout << "second query" << endl;
        string temp2 = "update sys.user set user_groupID = '";
        temp2 += groupName;
        temp2 += "' where userName = '";
        temp2 += creatorName;
        temp2 += "'";
        Query query2 = con.query(temp2);
        mysqlpp::StoreQueryResult res2 = query2.store();

        if (res) {

        } else {
            cerr << query.error() << endl;
        }
    }  catch (Exception &e) {
        cout << e.what() << endl;
    }
}


//VoteController
VoteController* VoteController::vcInstance = NULL;
VoteController* VoteController::getInstance(){
    if(vcInstance == NULL) {
        vcInstance = new VoteController();
    } else
        return vcInstance;
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
ApplicationController* ApplicationController::acInstance = NULL;
ApplicationController* ApplicationController::getInstance(){
    if(acInstance == NULL)
        acInstance = new ApplicationController();
    else
        return acInstance;
}
ApplicationController::ApplicationController() {
}

void ApplicationController::terminateProcess(){
    cout << "프로그램을 종료합니다." << endl;
    exit(0);
}
void ApplicationController::deleteVote(){

}
