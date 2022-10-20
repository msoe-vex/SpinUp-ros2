#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"

class DeployAction : public AutonAction {
private:
    Timer m_timer;

public:
    DeployAction();

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};
