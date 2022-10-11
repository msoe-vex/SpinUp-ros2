#pragma once

#include "auton/Auton.h"
#include "util/Timer.h"
#include "util/Constants.h"
#include "nodes/subsystems/IRollerIntakeNode.h"

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