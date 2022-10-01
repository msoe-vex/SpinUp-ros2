#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/nodes/subsystems/IRollerIntakeNode.h"

class RollerIntakeAction : public AutonAction {
private:
    IRollerIntakeNode* m_intake_node;
    Timer m_timer;
    int m_voltage;
    double m_time; // Time in seconds

public:
    RollerIntakeAction(IRollerIntakeNode* intake_node, int voltage=MAX_MOTOR_VOLTAGE, double time=0);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};