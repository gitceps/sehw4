#include <iostream>
#include "model.h"
#include "controller.h"
#include "view.h"

using namespace std;

void mainviewUI();

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
                    UIUI.userInput();
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
            Timer Timer;
            switch(action){
                case 1:
                    Timer.checkEndTime();
                    break;
            }
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
            cout << "3.1 투표제안" << endl;
            cout << "*입력 선택 : ";
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
            cout << "*입력 선택 : ";
            cin >> action;
            mainmenuController(num, action);
            break;
        case 7:
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
    cout << "7. 종료" << endl;
    cout << "*입력 선택 : ";
    cin >> menunum;
    try{
        if(menunum == 0) throw menunum;
        innermainveiwUI(menunum);
    }catch(int exception){
        cout << "메인메뉴에 없는 항목입니다" << endl;
    }
}


int main() {
    mainviewUI();
}