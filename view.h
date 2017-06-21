//
// Created by 최준성 on 2017. 6. 16..
//

#ifndef SEHW4_VIEW_H
#define SEHW4_VIEW_H

class VoteViewUI{
public:
    void selectOngoingVote();
    void selectScheduleVote();
    void selectTerminatedVote();
    void selectVote();
    void displayUI();
    void userInput();

};

class GroupViewUI{
public:
    void leaveGroup();
    void updateUI();
    void viewMyGroup();
    void showAllGroupList();
    void joinGroup();
    void requestCreateGroup();
    void groupDataInput();
    void overlapError();
    void displayUI();
    void userInput();
};

class VoteDetailUI{
public:
    void selectItem();
    void selectDelete();
    void displayUI();
    void userInput();
};

class AddVoteUI{
public:
    void createNewVote();
    void selectSuggestVote();
    void displayUI();
    void userInput();
};

class UserViewUI{
public:
    void login();
    void logout();
    void showLoginResultMessage();
    void requestCreateUser();
    void userDataInput();
    void overlapError();
    void requestDeleteUser();
    void displayUI();
    void userInput();
};

class TimerViewUI{
public:
    void selectCheckTime();
    void selectSetTime();
    void selectLocalTime();
};

#endif //SEHW4_VIEW_H
