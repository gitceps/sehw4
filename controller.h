//
// Created by 최준성 on 2017. 6. 16..
//

#ifndef SEHW4_CONTROLLER_H
#define SEHW4_CONTROLLER_H

static class ApplicationController {
private:
    ApplicationController *ApplicationController;
    //ApplicationController();

public:
    static ApplicationController getApplicationControllerInstance();

};

class VoteController{};
class UserController{};
class GroupController{};
class Timer{};

ApplicationController::ApplicationController() {
}

static ApplicationController* ApplicationController::getApplicationControllerInstance() {
    if(ApplicationController == NULL) {
        ApplicationController = new ApplicationController();
    } else {
        return ApplicationController;
    }
}
#endif //SEHW4_CONTROLLER_H
