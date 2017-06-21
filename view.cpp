//
// Created by 김유광 on 2017. 6. 17..
//

#include "view.h"
#include "model.h"
#include "controller.h"
#include <iostream>

using namespace std;

bool check_email(string const& address) {
    size_t at_index = address.find_first_of('@', 0);
    return at_index != string::npos
           && address.find_first_of('.', at_index) != std::string::npos;
}

//VoteViewUI
void VoteViewUI::selectOngoingVote(){
    VoteController* voteController = VoteController::getInstance();
    voteController->showOngoingVote();
}
void VoteViewUI::selectScheduleVote(){
    VoteController* voteController = VoteController::getInstance();
    voteController->showScheduleVote();
}
void VoteViewUI::selectTerminatedVote(){
    VoteController* voteController = VoteController::getInstance();
    voteController->showTerminatedVote();
}

void VoteViewUI::selectVote() {
    int voteID;
    cout << endl << "조회할 투표의 ID를 선택해주세요 : ";
    cin >> voteID;

    VoteController *voteController = VoteController::getInstance();
    voteController->getOngoingVoteDetails(voteID);
}

void VoteViewUI::displayUI(){
    cout << "4.1 현재 진행 중인 투표 리스트" << endl;
    cout << "4.2 투표" << endl;
    cout << "4.3 향후 진행 예정인 투표 리스트" << endl;
    cout << "4.4 종료된 투표리스트" << endl;
    cout << "*입력 선택 : ";
}
void VoteViewUI::userInput(){}


//GroupViewUI
//User 객체를 생성하는 것 보단 GroupMember 객체를 생성하는 것이 좋아보임
//시퀀스 그림 이상 코드의 흐름과 불일치
void GroupViewUI::leaveGroup(){

    UserController* userController = UserController::getInstance();
    if(userController->getCurrentUser() == NULL) {
        cout << "로그인을 먼저 해주세요" << endl;
        return;
    }
    userController->removeUserFromGroup();
    GroupController* groupController = GroupController::getInstance();
    groupController->setCurrentUserGroup(-1);
    cout << "그룹 탈퇴가 완료되었습니다" << endl;
//    int cUP;
//    GroupMember GroupMember;
//    cUP = GroupMember.checkUserPermission();
//    if(cUP == 1)
//        GroupMember.removeGroupFromUser();
//    else
//        return;
}

void GroupViewUI::updateUI(){}

//User 객체를 생성하는 것이 아닌 GroupMember 객체를 생성해야함
void GroupViewUI::viewMyGroup(){
    UserController* userController = UserController::getInstance();
    if(userController->getCurrentUser() == NULL) {
        cout << "로그인을 먼저 해주세요" << endl;
        return;
    }
    GroupController* groupController = GroupController::getInstance();
    if(groupController->getCurrentUserGroup() == NULL) {
        cout << "가입된 그룹이 없습니다" << endl;
    } else {
        cout << "현재 그룹 : " << groupController->getCurrentUserGroup()->getGroupId() << endl;
    }
//    GroupMember GroupMember;
//    GroupMember.getGroupID();
//    Group Group;
//    Group.getGroupInfo();
}

void GroupViewUI::showAllGroupList(){
    GroupController* groupController = GroupController::getInstance();
    groupController->showAllGroup();
}
void GroupViewUI::joinGroup(){
    UserController* userController = UserController::getInstance();
    if(userController->getCurrentUser() == NULL) {
        cout << "로그인을 먼저 해주세요" << endl;
        return;
    }
    GroupController::getInstance()->showAllGroup();
    string userName = userController->getCurrentUser()->getUserName();
    int groupID = 0;
    cout << "가입할 그룹 ID를 입력해주세요" << endl;
    cin >> groupID;
    GroupController* groupController = GroupController::getInstance();
    groupController->joinGroup(userName, groupID);
}
void GroupViewUI::requestCreateGroup(){
    int num;
    cout << "그룹을 생성하시겠습니까?" << endl;
    cout << "1. 계속 진행" << endl;
    cout << "2. 중단" << endl;
    cout << "*입력 선택 : ";
    cin >> num;
    switch (num){
        case 1: {
            UserController* userController = UserController::getInstance();
            if(userController->getCurrentUser() == NULL) {
                cout << "로그인을 먼저 해주세요" << endl;
                return;
            }
            GroupController* groupController = GroupController::getInstance();
            groupController->createGroup();
            break;
        }
        case 2: {
            break;
        }
        default: {
            break;
        }
    }

}
void GroupViewUI::groupDataInput(){
    string groupName;
    int groupID = 0;
    UserController* userController = UserController::getInstance();
    string creatorName = userController->getCurrentUser()->getUserName();
    int overlapChk;
    cout << "그룹 생성에 필요한 정보를 입력하세요" << endl;
    cout << "그룹이름을 입력하세요" << endl;
    cin >> groupName;

    GroupController* groupController = GroupController::getInstance();
    overlapChk = groupController->getOverlapCheck(groupName);
    if (overlapChk == 0){
        groupController->setGroupData(creatorName,groupID,groupName);
        cout << "그룹 생성이 완료되었습니다" << endl;
    }
    else
        overlapError();

}
void GroupViewUI::overlapError(){
    cout << "중복된 그룹명입니다." << endl;
    return;
}

void GroupViewUI::displayUI(){
    cout << "5.1 전체그룹 조회" << endl;
    cout << "5.2 그룹 가입" << endl;
    cout << "5.3 그룹 생성" << endl;
    cout << "5.4 가입그룹 조회" << endl;
    cout << "5.5 그룹 탈퇴" << endl;
    cout << "*입력 선택 : ";
}
void GroupViewUI::userInput(){}

void VoteDetailUI::selectItem(){
    int voteID, index;

    VoteController* voteController = VoteController::getInstance();
    voteController->showOngoingVote();
    cout << "투표할 안건을 선택하세요" << endl;
    cin >> voteID;
    cout << "투표할 선택지 번호를 입력하세요" << endl;
    cin >> index;
    voteController->saveItemData(voteID, index);
}
void VoteDetailUI::selectDelete(){}
void VoteDetailUI::displayUI(){}
void VoteDetailUI::userInput(){}

void UserViewUI::login(){
    string userName;
    string psw;
    cout << "ID를 입력하세요" << endl;
    cin >> userName;
    cout << "Password를 입력하세요" << endl;
    cin >> psw;
    UserController *userController = UserController::getInstance();
    userController->validateUserInfo(userName,psw);

}

void UserViewUI::logout(){
    int userID;
    User User;
    userID = User.getUserID();
    UserController *userController = UserController::getInstance();
    userController->deleteUserSession(userID);
}
void UserViewUI::showLoginResultMessage(){
    cout << "로그인되었습니다" << endl;
}

void UserViewUI::requestCreateUser(){
    int num;
    cout << "회원가입을 하시겠습니까?" << endl;
    cout << "1. 계속 진행" << endl;
    cout << "2. 중단" << endl;
    cout << "*입력 선택 : ";
    cin >> num;
    switch (num){
        case 1: {
            UserController* userController = UserController::getInstance();
            userController->createUser();
            break;
        }
        case 2: {
            break;
        }
    }
}

void UserViewUI::userDataInput(){
    string userID;
    string userName;
    string userRName;
    string psw;
    string icn;
    string email;
    string address;
    bool overlapChk;
    cout << "회원가입에 필요한 정보를 입력하세요" << endl;
    cout << "ID를 입력하세요" << endl;
    cin >> userName;
    cout << "Password를 입력하세요" << endl;
    cin >> psw;
    cout << "이름을 입력하세요" << endl;
    cin >> userRName;
    cout << "주민번호를 입력하세요" << endl;
    cin >> icn;
    cout << "이메일 주소를 입력하세요" << endl;
    cin >> email;

    if(!check_email(email)) {
        cout << "올바른 이메일 형식이 아닙니다" << endl;
    }

    cout << "주소를 입력하세요" << endl;
    cin >> address;

    UserController* userController = UserController::getInstance();
    overlapChk = userController->getOverlapCheck(userName);
    //overlapchk가 1이면 중복
    if (!overlapChk){
        cout << "회원가입이 완료되었습니다" << endl;
        userController->setUserData(userID, userName, psw, userRName,email,address,icn);
    }
    else
        overlapError();

}
void UserViewUI::overlapError(){
    cout << "중복된 아이디 입니다." << endl;
    return;
}

void UserViewUI::requestDeleteUser(){
    int num;
    UserController *uc = UserController::getInstance();

    if (uc->getCurrentUser() == NULL) {
        cout << "로그인을 먼저 해주세요" << endl;
        return;
    }

    string userName = uc->getCurrentUser()->getUserName();

    cout << "current UserName : " << userName << endl;

    cout << "회원탈퇴를 계속 잔행하시겠습니까?" << endl;
    cout << "1. 계속 진행" << endl;
    cout << "2. 중단" << endl;
    cout << "*입력 선택 : ";
    cin >> num;
    switch (num) {
        case 1: {
            uc->deleteUser(userName);
            ApplicationController::getInstance()->terminateProcess();
            break;
        }
        case 2: {
            break;
        }
        default: {
            break;
        }
    }

}

void UserViewUI::displayUI(){}
void UserViewUI::userInput(){}

//AddVoteUI
void AddVoteUI::createNewVote(){
    UserController* userController = UserController::getInstance();
    if(userController->getCurrentUser() == NULL) {
        cout << "로그인을 먼저 해주세요" << endl;
        return;
    }
    Timer* timer = Timer::getInstance();

    string votetitle;
    int optionnum;
    string opt;
    list<string> option;
    int stime;
    int etime;
    cout << "******투표를 생성해주세요******" << endl;
    cout << "투표 주제를 선택하세요 : ";
    cin >> votetitle;
    cout << "******투표 항목을 생성해 주세요******" << endl;
    cout << "투표 항목 수를 정해주세요 :";
    cin >> optionnum;
    cout << optionnum <<"개 의 투표 항목 이름을 정해주세요"<< endl;
    for (int i = 0; i<optionnum; i++){
        cout << "투표 항목 이름을 정해주세요 :";
        cin >> opt;
        option.push_back(opt);
    }
    cout << "투표 시작시간을 지정해주세요 : ";
    cin >> stime;
    while(!timer->checkStartTime(stime)){
        cout << "올바른 투표 시작시간을 지정해주세요 : ";
        cin >> stime;
    }
    cout << "투표 마감시간을 지정해주세요 :";
    cin >> etime;
    while(!timer->checkRightTime(stime, etime)){
        cout << "올바른 투표 마감시간을 지정해주세요 : ";
        cin >> etime;
    }
    VoteController* voteController = VoteController::getInstance();
    voteController->addNewVote(votetitle, optionnum, option, stime, etime);
}

//VoteController에 showVoteData 누락
void AddVoteUI::selectSuggestVote(){
    VoteController* voteController = VoteController::getInstance();
    voteController->showVoteData();

}
void AddVoteUI::displayUI(){
    cout << "3.1 투표제안" << endl;
    cout << "*입력 선택 : ";
}
void AddVoteUI::userInput(){}

void TimerViewUI::selectCheckTime() {
    Timer* Timer = Timer::getInstance();
    Timer->checkCurrentTime();
}

void TimerViewUI::selectSetTime() {
    int ymd;
    int hm;
    cout << "******현재 시간을 설정해주세요******" << endl;
    cout << "날짜를 입력해주세요 : ";
    cin >> ymd;
    cout << "시간을 입력해주세요 : ";
    cin >> hm;
    Timer* Timer = Timer::getInstance();
    Timer->setCurrentTime(ymd, hm);
}

void TimerViewUI::selectLocalTime() {
    Timer* Timer = Timer::getInstance();
    Timer->setLocalTime();
}