//
// Created : 2017. 6. 16..
// Author : 김유광, 최준성, 김지현, 백지홍
//

#include <iostream>
#include "model.h"
#include "controller.h"
#include "view.h"
#include <ctime>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

using namespace std;

void mainviewUI();

void initControllers();
void autoDelete();

void mainmenuController(int num, int action){
    switch(action){
        case 0:
            mainviewUI();
            break;
    }
    switch(num){
        case 1:
            UserViewUI UIUI;
            switch(action){
                case 1:
                    UIUI.requestCreateUser();
                    break;
                case 2:
                    UIUI.requestDeleteUser();
                    break;
            }
            break;
        case 2:
            UserViewUI UserViewUI;
            switch(action){
                case 1:
                    UserViewUI.login();
                    break;
                case 2:
                    UserViewUI.logout();
                    break;
            }
            break;
        case 3:
            AddVoteUI AddVoteUI;
            switch(action) {
                case 1:
                    AddVoteUI.selectSuggestVote();
                    break;
                default:
                    break;
            }
            break;
        case 4:
            VoteViewUI VoteViewUI;
            VoteDetailUI VoteDetailUI;
            switch(action){
                case 1:
                    VoteViewUI.selectOngoingVote();
                    break;
                case 2:
                    VoteDetailUI.selectItem();
                    break;
                case 3:
                    VoteViewUI.selectScheduleVote();
                    break;
                case 4:
                    VoteViewUI.selectTerminatedVote();
                    break;
            }
            break;
        case 5:
            GroupViewUI GroupViewUI;
            switch(action){
                case 1:
                    GroupViewUI.showAllGroupList();
                    break;
                case 2:
                    GroupViewUI.joinGroup();
                    break;
                case 3:
                    GroupViewUI.requestCreateGroup();
                    break;
                case 4:
                    GroupViewUI.viewMyGroup();
                    break;
                case 5:
                    GroupViewUI.leaveGroup();
                    break;
            }
            break;
        case 6:
            TimerViewUI TimerViewUI;
            switch(action){
                case 1:
                    TimerViewUI.selectSetTime();
                    break;
                case 2:
                    TimerViewUI.selectCheckTime();
                    break;
                case 3:
                    TimerViewUI.selectLocalTime();
                    break;
            }
            break;
        case 7:
            switch(action) {
                case 1:
                    //UserViewUI *userViewUI = new UserViewUI();
                    UserViewUI.login();
                    break;
                case 2:
                    if(UserController::getInstance()->getCurrentUser() == NULL) {
                        cout << "로그인을 먼저 해주세요" << endl;
                        break;
                    } else {
                        UserViewUI.logout();
                        cout << "Guest Session으로 변경되었습니다" << endl;
                    }
                    break;
            }
            break;
        case 8:
            ApplicationController::getInstance()->terminateProcess();
            break;
        default:
            ApplicationController::getInstance()->terminateProcess();
            break;
    }
}

void innermainveiwUI(int num){
    int action;
    switch(num){
        case 1:
            cout << "1.1 회원가입" << endl;
            cout << "1.2 회원탈퇴" << endl;
            cout << "0. 메인 메뉴로 돌아가기" << endl;
            cout << "*입력 선택 : ";
            cin >> action;
            mainmenuController(num, action);
            break;
        case 2:
            cout << "2.1 로그인" << endl;
            cout << "2.2 로그아웃" << endl;
            cout << "0. 메인 메뉴로 돌아가기" << endl;
            cout << "*입력 선택 : ";
            cin >> action;
            mainmenuController(num, action);
            break;
        case 3:
            AddVoteUI AddVoteUI;
            AddVoteUI.displayUI();
            cin >> action;
            mainmenuController(num, action);
            break;
        case 4:
            VoteViewUI VoteViewUI;
            VoteViewUI.displayUI();
            cin >> action;
            mainmenuController(num, action);
            break;
        case 5:
            GroupViewUI GroupViewUI;
            GroupViewUI.displayUI();
            cin >> action;
            mainmenuController(num, action);
            break;
        case 6:
            cout << "6.1 현재시간 설정" << endl;
            cout << "6.2 현재시간 확인" << endl;
            cout << "6.3 localtime" << endl;
            cout << "*입력 선택 : ";
            cin >> action;
            mainmenuController(num, action);
            break;
        case 7:
            cout << "7.1 Session 선택/변경" << endl;
            cout << "7.2 guest Session으로 변경" << endl;
            cout << "*입력 선택 : ";
            cin >> action;
            mainmenuController(num, action);
            break;
        case 8:
            mainmenuController(num, -1);
            break;
    }
}

void mainviewUI(){
    int menunum;
    cout << "1. 회원가입/탈퇴" << endl;
    cout << "2. 로그인/로그아웃" << endl;
    cout << "3. 투표제안" << endl;
    cout << "4. 투표관리" << endl;
    cout << "5. 그룹관리" << endl;
    cout << "6. 현재시간 설정" << endl;
    cout << "7. session변경" << endl;
    cout << "8. 종료" << endl;
    cout << "*입력 선택 : ";
    cin >> menunum;
    try{
        if(menunum == 0) throw menunum;
        innermainveiwUI(menunum);
    }catch(int exception){
        cout << "메인메뉴에 없는 항목입니다" << endl;
    }
}

void initControllers() {
    UserController::getInstance();
    VoteController::getInstance();
    GroupController::getInstance();
    Timer::getInstance();
    ApplicationController::getInstance();
}

void autoDelete() {
    Timer* timer = Timer::getInstance();
    if(timer->getLocalOn())
        timer->setLocalTime();

    ApplicationController* ac = ApplicationController::getInstance();
    ac->deleteVote();
}

int main() {
    initControllers();

    while (true) {
        autoDelete();
        mainviewUI();
    }
}




