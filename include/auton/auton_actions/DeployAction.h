#pragma once

#include "auton/Auton.h"
#include "util/Timer.h"

class DeployAction : public AutonAction {
private:
    Timer m_timer;

public:
    DeployAction();

    void ActionInit();

    actionStatus Action();
    
    void ActionEnd();
};
