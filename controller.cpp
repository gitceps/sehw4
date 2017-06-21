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
#define PASSWORD "shin0707"

void setTimeFormat(int ftime);

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
                ucInstance->currentUser = new User(userName);
                ucInstance->currentUser->authenticateUser();
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
            cout << "============================" << endl;
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
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "select groupName from sys.group where groupID = '";
        temp += to_string(groupID);
        temp += "'";
        cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        //Row row;
        if (res) {
            if(res.num_rows() != 0) {

            }
            else {
                cout << "해당하는 그룹 ID가 없습니다" << endl;
                return;
            }
        }
        else {
            cerr << query.error() << endl;
            return;
        }

        string temp2 = "update sys.user set user_groupID = '";
        temp2  += res[0]["groupName"].data();
        temp2  += "' where userName = '";
        temp2 += userName;
        temp2 += "'";
        cout << temp2 << endl;

        Query query2 = con.query(temp2);
        mysqlpp::StoreQueryResult res2 = query2.store();
        if (res2) {

        } else {
            cerr << query2.error() << endl;
            return;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
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

//TODO 현재 그룹에서의 투표만 조회할 수 있다
void VoteController::showOngoingVote(){
    VoteViewUI VoteViewUI;
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);

        UserController* userController = UserController::getInstance();
        string userName = userController->getCurrentUser()->getUserName();
        if(userController->getCurrentUser() == NULL) {
            cout << "로그인을 먼저 해주세요" << endl;
            return;
        }
        Timer* timer = Timer::getInstance();

        int row_check = 0;

        string temp = "select distinct groupID from sys.user, sys.group where (user_groupID = groupName) and userName = '";
        temp += userName;
        temp += "'";

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();
        if (res) {
            if(res.num_rows() == 0)
                return;

        } else {
            cerr << query.error() << endl;
        }

        string temp2 = "select * from sys.vote where groupID = '";
        temp2 += res[0]["groupID"].data();
        temp2 += "'";

        Query query2 = con.query(temp2);
        mysqlpp::StoreQueryResult res2 = query2.store();

        if (res2) {
            // Display header
            cout.setf(ios::left);
            cout << setw(15) << "voteID" << setw(20) << "Title" << setw(15) << "Creator" << setw(15) << "options" << endl << endl;

            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res2.num_rows(); ++i) {
                if (!timer->checkStartTime(res2[i]["startTime"]) && !timer->checkEndTime(res2[i]["endTime"])) {
                    cout << setw(15) << res2[i]["voteID"] << setw(20) << res2[i]["title"] << setw(15)
                         << res2[i]["voteCreatorID"] << setw(15) << res2[i]["optionNum"] << endl;
                    row_check++;
                }
            }
            cout << "============================" << endl;

            if(row_check == 0)
                return;
            else
                VoteViewUI.selectVote();
        }
        else {
            cerr << query2.error() << endl;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}
void VoteController::showScheduleVote(){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);

        UserController* userController = UserController::getInstance();
        string userName = userController->getCurrentUser()->getUserName();
        if(userController->getCurrentUser() == NULL) {
            cout << "로그인을 먼저 해주세요" << endl;
            return;
        }
        Timer* timer = Timer::getInstance();

        string temp = "select distinct groupID from sys.user, sys.group where (user_groupID = groupName) and userName = '";
        temp += userName;
        temp += "'";

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();
        if (res) {
            if(res.num_rows() == 0)
                return;

        } else {
            cerr << query.error() << endl;
        }

        string temp2 = "select * from sys.vote where groupID = '";
        temp2 += res[0]["groupID"].data();
        temp2 += "'";

        Query query2 = con.query(temp2);
        mysqlpp::StoreQueryResult res2 = query2.store();

        if (res2) {
            // Display header
            cout.setf(ios::left);
            cout << setw(15) << "voteID" << setw(15) << "Title" << setw(15) << "Creator" << setw(15) << "options" << endl << endl;

            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res2.num_rows(); ++i) {
                if (timer->checkStartTime(res2[i]["startTime"])) {
                    cout << setw(15) << res2[i]["voteID"] << setw(15) << res2[i]["title"] << setw(15)
                         << res2[i]["voteCreatorID"] << setw(15) << res2[i]["optionNum"] << endl;
                }
            }
            cout << "============================" << endl;
        }
        else {
            cerr << query2.error() << endl;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}

void VoteController::showTerminatedVote(){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);

        UserController* userController = UserController::getInstance();
        string userName = userController->getCurrentUser()->getUserName();
        if(userController->getCurrentUser() == NULL) {
            cout << "로그인을 먼저 해주세요" << endl;
            return;
        }
        Timer* timer = Timer::getInstance();

        string temp = "select distinct groupID from sys.user, sys.group where (user_groupID = groupName) and userName = '";
        temp += userName;
        temp += "'";

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();
        if (res) {
            if(res.num_rows() == 0)
                return;

        } else {
            cerr << query.error() << endl;
        }

        string temp2 = "select * from sys.vote where groupID = '";
        temp2 += res[0]["groupID"].data();
        temp2 += "'";

        Query query2 = con.query(temp2);
        mysqlpp::StoreQueryResult res2 = query2.store();

        if (res2) {
            // Display header
            cout.setf(ios::left);
            cout << setw(15) << "voteID" << setw(15) << "Title" << setw(15) << "Creator" << setw(15) << "options" << endl << endl;

            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res2.num_rows(); ++i) {
                if (timer->checkEndTime(res2[i]["endTime"])) {
                    cout << setw(15) << res2[i]["voteID"] << setw(15) << res2[i]["title"] << setw(15)
                         << res2[i]["voteCreatorID"] << setw(15) << res2[i]["optionNum"] << endl;
                }
            }
            cout << "============================" << endl;
        }
        else {
            cerr << query2.error() << endl;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}

Vote VoteController::getVote(int voteID){
    Vote Vote;
    return Vote;
}

void VoteController::saveItemData(int voteID, int index){
    Connection con(true);
    try {
        //TODO voteItemID를 user에게 어떻게 알려 줄것인지?
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        string temp = "update sys.voteItem set count = count + 1 where voteID = '";
        temp += to_string(voteID);
        temp += "' and voteItemID = '";
        temp += to_string(index);
        temp += "'";
        cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
        } else {
            cerr << query.error() << endl;
        }

    } catch (Exception &e) {
            cout << e.what() << endl;
    }

}

void VoteController::deleteVote(int voteID){
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //cout << "connected to database" << endl;

        string temp = "delete from sys.vote where voteID = '";
        temp += to_string(voteID);
        temp += "'";
        cout << temp << endl;

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
        } else {
            cerr << query.error() << endl;
        }
    }  catch (Exception &e) {
        cout << e.what() << endl;
    }

    cout << "투표 삭제가 완료 되었습니다" << endl;
}

void setTimeFormat(int ftime) {
    int ymd1 = ftime / 10000;
    int ymd2 = ftime % 10000;

    int year = ymd1 / 10000;
    int a = ymd1 % 10000;
    int month = a / 100;
    int day = a % 100;

    int hour = ymd2 / 100;
    int min = ymd2 % 100;

    cout << (year + 2000) << "-" << month << "-" << day << " ";
    if (hour < 10)
        cout << "0";
    cout << hour << ":";
    if (min < 10)
        cout << "0";
    cout << min << endl;
}

list<Vote> VoteController::getTerminatedVoteDetails(){
    list<Vote> Vote;
    return Vote;
}
void VoteController::getOngoingVoteDetails(int voteID) {
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        string temp = "select * from sys.vote where voteID = '";
        temp += to_string(voteID);
        temp += "'";

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
            cout << endl;
            cout << "투표 ID : " << voteID << endl;
            cout << "투표 주제 : " << res[0]["title"] << endl;
            cout << "----------------------------" << endl;

            string temp2 = "select * from sys.voteItem where voteID = '";
            temp2 += to_string(voteID);
            temp2 += "'";

            Query query2 = con.query(temp2);
            mysqlpp::StoreQueryResult res2 = query2.store();

            if (res2) {
                for (size_t i = 0; i < res2.num_rows(); ++i) {
                    cout << i+1 << "번 : " << res2[i]["itemName"] << endl;
                }
                cout << "----------------------------" << endl;
            } else {
                cerr << query2.error() << endl;
            }

            cout << "투표 마감시간 : ";
            setTimeFormat(res[0]["endTime"]);
            cout << endl;
        } else {
            cerr << query.error() << endl;
        }
    } catch (Exception &e) {
        cout << e.what() << endl;
    }
}
list<Vote> VoteController::getScheduledVoteDetails(){
    list<Vote> Vote;
    return Vote;
}
void VoteController::checkVote(){

}

void VoteController::showVoteData(){
    AddVoteUI AddVoteUI;
    AddVoteUI.createNewVote();
} // 시퀀스 다이어 그램에 있으나 클래스 다이어 그램에 빠져있음
void VoteController::addNewVote(string voteTitle, int optionNum, list<string> option, int stime, int etime){
    UserController* userController = UserController::getInstance();
    User* currentUser = userController->getCurrentUser();
    string userName = currentUser->getUserName();

    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);
        //TODO 여러개의 쿼리문 구현
        string temp = "select distinct groupID from sys.user, sys.group where (user_groupID = groupName) and userName = '";
        temp += userName;
        temp += "'";

        Query query = con.query(temp);
        mysqlpp::StoreQueryResult res = query.store();
        if (res) {
            if(res.num_rows() == 0)
                return;

        } else {
            cerr << query.error() << endl;
        }

        //genderate random vote ID
        srand(time(NULL));
        int voteID = (rand() % 1000);

        string temp2 = "insert into sys.vote(voteID, groupID, voteCreatorID, startTime, title, optionNum, endTime) values ('";

        temp2 += to_string(voteID);
        temp2 += "', '";
        temp2 += res[0]["groupID"].data();;
        temp2 += "', '";
        temp2 += userName;
        temp2 += "', '";
        temp2 += to_string(stime);
        temp2 += "', '";
        temp2 += voteTitle;
        temp2 += "', '";
        temp2 += to_string(optionNum);
        temp2 += "', '";
        temp2 += to_string(etime);
        temp2 += "')";

        Query query2 = con.query(temp2);
        mysqlpp::StoreQueryResult res2 = query2.store();
        if (res2) {

        } else {
            cerr << query2.error() << endl;
        }

        for(int i = 0; i < optionNum; i++) {
            //TODO 반복 쿼리문 구현
            string temp3 = "insert into voteItem(voteID, itemName) values('";
            temp3 += to_string(voteID);
            temp3 += "', '";
            temp3 += option.front();
            temp3 += "')";

            Query query3 = con.query(temp3);
            mysqlpp::StoreQueryResult res3 = query3.store();
            option.pop_front();
            if (res3) {

            } else {
                cerr << query3.error() << endl;
            }
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }

} // 시퀀스 다이어 그램에 있으나 클래스 다이어 그램에 빠져있음

Timer* Timer::tInstance = NULL;
Timer* Timer::getInstance() {
    if(tInstance == NULL)
        tInstance = new Timer();
    else
        return tInstance;
}

Timer::Timer() {
    local_On = true;
    currentTime1 = time(0);
    currentTime3 = localtime(&currentTime1);
}

bool Timer::getLocalOn() {return local_On;}

void Timer::setCurrentTime(int ymd, int hm) {
    int year = ymd / 10000;
    currentTime2.tm_year = year + 100;
    int n_year = ymd % 10000;
    int month = n_year / 100;
    currentTime2.tm_mon = month - 1;
    int day = n_year % 100;
    currentTime2.tm_mday = day;

    int hour = hm / 100;
    currentTime2.tm_hour = hour;
    int min = hm % 100;
    currentTime2.tm_min = min;
    currentTime2.tm_sec = 1;

    local_On = false;
    currentTime1 = mktime(&currentTime2);
    currentTime3 = localtime(&currentTime1);

    char tmbuf[4096];
    strftime(tmbuf, 4096, "%F %R", currentTime3);
    cout << tmbuf << " 으로 설정되었습니다." << endl;
}

void Timer::checkCurrentTime() {
    char tmbuf[4096];
    strftime(tmbuf, 4096, "%F %R", currentTime3);
    cout << tmbuf << endl;
}

void Timer::setLocalTime() {
    local_On = true;
    currentTime1 = time(0);
    currentTime3 = localtime(&currentTime1);
}

bool Timer::checkAutoEndTime(int ctime) {
    time_t time1;
    struct tm time2;

    int ymd1 = ctime / 10000;
    int ymd2 = ctime % 10000;

    int year = ymd1 / 10000;
    time2.tm_year = year + 100;
    int a = ymd1 % 10000;
    int month = a / 100;
    time2.tm_mon = month - 1;
    int day = a % 100;
    time2.tm_mday = day;

    int hour = ymd2 / 100;
    time2.tm_hour = hour;
    int min = ymd2 % 100;
    time2.tm_min = min;
    time2.tm_sec = 1;

    time1 = mktime(&time2);

    if((currentTime1-time1) >= 2419200) {
        return true;
    }
    else{
        return false;
    }
}

bool Timer::checkStartTime(int stime) {
    time_t time1;
    struct tm time2;

    int ymd1 = stime / 10000;
    int ymd2 = stime % 10000;

    int year = ymd1 / 10000;
    time2.tm_year = year + 100;
    int a = ymd1 % 10000;
    int month = a / 100;
    time2.tm_mon = month - 1;
    int day = a % 100;
    time2.tm_mday = day;

    int hour = ymd2 / 100;
    time2.tm_hour = hour;
    int min = ymd2 % 100;
    time2.tm_min = min;
    time2.tm_sec = 1;
    time2.tm_isdst = 0;

    time1 = mktime(&time2);

    if(currentTime1 < time1) {
        return true;
    }
    else{
        return false;
    }
}

bool Timer::checkEndTime(int etime) {
    time_t time1;
    struct tm time2;

    int ymd1 = etime / 10000;
    int ymd2 = etime % 10000;

    int year = ymd1 / 10000;
    time2.tm_year = year + 100;
    int a = ymd1 % 10000;
    int month = a / 100;
    time2.tm_mon = month - 1;
    int day = a % 100;
    time2.tm_mday = day;

    int hour = ymd2 / 100;
    time2.tm_hour = hour;
    int min = ymd2 % 100;
    time2.tm_min = min;
    time2.tm_sec = 1;
    time2.tm_isdst = 0;

    time1 = mktime(&time2);

    if(currentTime1 >= time1) {
        return true;
    }
    else{
        return false;
    }
}

bool Timer::checkRightTime(int stime, int etime) {
    time_t time1, time3;
    struct tm time2, time4;

    int ymd1 = stime / 10000;
    int ymd2 = stime % 10000;
    int ymd3 = etime / 10000;
    int ymd4 = etime % 10000;

    int year = ymd1 / 10000;
    time2.tm_year = year + 100;
    int a = ymd1 % 10000;
    int month = a / 100;
    time2.tm_mon = month - 1;
    int day = a % 100;
    time2.tm_mday = day;

    int hour = ymd2 / 100;
    time2.tm_hour = hour;
    int min = ymd2 % 100;
    time2.tm_min = min;
    time2.tm_sec = 1;
    time2.tm_isdst = 0;

    time1 = mktime(&time2);

    int year2 = ymd3 / 10000;
    time4.tm_year = year2 + 100;
    int a2 = ymd3 % 10000;
    int month2 = a2 / 100;
    time4.tm_mon = month2 - 1;
    int day2 = a2 % 100;
    time4.tm_mday = day2;

    int hour2 = ymd4 / 100;
    time4.tm_hour = hour2;
    int min2 = ymd4 % 100;
    time4.tm_min = min2;
    time4.tm_sec = 1;
    time4.tm_isdst = 0;

    time3 = mktime(&time4);

    if(time3 > time1) {
        return true;
    }
    else{
        return false;
    }
}

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
    Timer* Timer = Timer::getInstance();
    VoteController* VoteController = VoteController::getInstance();
    Connection con(true);
    try {
        con.connect(DBNAME, SERVER, USER, PASSWORD);

        Query query = con.query("select endTime from sys.vote");
        mysqlpp::StoreQueryResult res = query.store();

        if (res) {
            // Get each row in result set, and print its contents
            for (size_t i = 0; i < res.num_rows(); ++i) {
                if(Timer->checkAutoEndTime(res[i]["endTime"])) {
                    string temp2 = "select voteID from sys.vote where endTime = '";
                    temp2 += res[i]["endTime"].data();
                    temp2 += "'";

                    Query query2 = con.query(temp2);
                    mysqlpp::StoreQueryResult res2 = query2.store();

                    string temp3 = "delete from sys.voteItem where voteID = '";
                    temp3 += res2[0]["voteID"].data();
                    temp3 += "'";

                    Query query3 = con.query(temp3);
                    mysqlpp::StoreQueryResult res3 = query3.store();

                    string temp4 = "delete from sys.vote where voteID = '";
                    temp4 += res2[0]["voteID"].data();
                    temp4 += "'";

                    Query query4 = con.query(temp4);
                    mysqlpp::StoreQueryResult res4 = query4.store();
                }
            }
        }
        else {
            cerr << query.error() << endl;
        }
    } catch(Exception &e) {
        cout << e.what() << endl;
    }
}
