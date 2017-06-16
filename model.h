//
// Created by 최준성 on 2017. 6. 16..
//

#ifndef SEHW4_MODEL_H
#define SEHW4_MODEL_H
#include <clocale>

class Vote {
private:
    int voteID;
    int groupID;
    int voteCreatorID;
    char* startTime, endTime;

public :
    Vote();
    Vote getVote(int voteID);
    void deleteVote(int voteID);
    void saveItemData(int index);
    int getVoteID();
    char* getStartTime();
    char* getEndTime();
    bool checkVote();
};

class User {
private:
    int userID;
    int groupId = 0;
    char* userName;
    char* userRealName;
    char* email;
    char* address;
    char* idCardNumber;
    bool isCreator = false;
    bool loginStatus = false;

public:
    User();
    void authenticateUser();
    bool checkUserName(char* userName);
    bool changeUserStatus();
    bool checkUserPermission();
    void removeGroupFromUser();
    int getGroupID();
    void userJoinGroup(int groupID);
    int getUserID();
};

Vote::Vote() {}

Vote Vote::getVote(int voteID) {
    return NULL;
}

void Vote::deleteVote(int voteID) {

}




#endif //SEHW4_MODEL_H
