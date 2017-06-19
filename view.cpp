//
// Created by 김유광 on 2017. 6. 17..
//

#include "view.h"
#include "model.h"
#include "controller.h"
#include <iostream>

using namespace std;

//VoteViewUI
void VoteViewUI::selectOngoingVote(){
    VoteController VoteController;
    VoteController.showOngoingVote();
}
void VoteViewUI::selectScheduleVote(){
    VoteController VoteController;
    VoteController.showScheduleVote();
}
void VoteViewUI::selectTerminatedVote(){
    VoteController VoteController;
    VoteController.showTerminatedVote();
}

void VoteViewUI::selectVote(){
    VoteController VoteController;
    VoteController.getOngoingVoteDetails();
}

void VoteViewUI::displayUI(){
    cout << "4.1 현재 진행 중인 투표 리스트" << endl;
    cout << "4.2 회원탈퇴" << endl;
    cout << "4.3 향후 진행 예정인 투표 리스트" << endl;
    cout << "4.4 종료된 투표리스트" << endl;
    cout << "*입력 선택 : ";
}
void VoteViewUI::userInput(){}


//GroupViewUI
//User 객체를 생성하는 것 보단 GroupMember 객체를 생성하는 것이 좋아보임
//시퀀스 그림 이상 코드의 흐름과 불일치
void GroupViewUI::leaveGroup(){
    int cUP;
    GroupMember GroupMember;
    cUP = GroupMember.checkUserPermission();
    if(cUP == 1)
        GroupMember.removeGroupFromUser();
    else
        return;
}

void GroupViewUI::updateUI(){}

//User 객체를 생성하는 것이 아닌 GroupMember 객체를 생성해야함
void GroupViewUI::viewMyGroup(){
    GroupMember GroupMember;
    GroupMember.getGroupID();
    Group Group;
    Group.getGroupInfo();
}

void GroupViewUI::showAllGroupList(){
    GroupController GroupController;
    GroupController.showAllGroup();
}
void GroupViewUI::joinGroup(){
    int userID;
    int groupID;
    GroupController GroupController;
    GroupController.joinGroup(userID, groupID);
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
            GroupController GroupController;
            GroupController.createGroup();
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
    int createID;
    int groupID;
    int overlapChk;
    cout << "그룹 생성에 필요한 정보를 입력하세요" << endl;
    cout << "그룹이름을 입력하세요";
    cin >> groupName;

    GroupController GroupController;
    overlapChk = GroupController.getOverlapCheck(groupName);
    if (overlapChk == 0){
        cout << "회원가입이 완료되었습니다" << endl;
        GroupController.setGroupData(createID,groupID,groupName);
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

void VoteDetailUI::selectItem(){}
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
    UserController UserController;
    UserController.validateUserInfo(userName,psw);

}

void UserViewUI::logout(){
    int userID;
    User User;
    userID = User.getUserID();
    UserController UserController;
    UserController.deleteUserSession(userID);

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
            UserController UserController;
            UserController.createUser();
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
    cout << "주소를 입력하세요" << endl;
    cin >> address;

    UserController UserController;
    overlapChk = UserController.getOverlapCheck(userName);
    //overlapchk가 1이면 중복
    if (!overlapChk){
        cout << "회원가입이 완료되었습니다" << endl;
        UserController.setUserData(userID, userName, psw, userRName,email,address,icn);
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
    int userID = 1;
    UserController UserController;
    UserController.getInstance();
    cout << "회원탈퇴를 계속 잔행하시겠습니까?" << endl;
    cout << "1. 계속 진행" << endl;
    cout << "2. 중단" << endl;
    cout << "*입력 선택 : ";
    cin >> num;
    switch (num){
        case 1: {
            UserController.deleteUser(userID);
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
    string votetitle;
    int optionnum;
    string opt;
    list<string> option;
    string stime;
    string etime;
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
    cout << "투표 마감시간을 지정해주세요 :";
    cin >> etime;
    VoteController VoteController;
    VoteController.addNewVote();

}

//VoteController에 showVoteData 누락
void AddVoteUI::selectSuggestVote(){
    VoteController VoteController;
    VoteController.showVoteData();

}
void AddVoteUI::displayUI(){
    cout << "3.1 투표제안" << endl;
    cout << "*입력 선택 : ";
}
void AddVoteUI::userInput(){}