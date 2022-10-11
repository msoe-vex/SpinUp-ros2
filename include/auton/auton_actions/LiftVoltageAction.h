#pragma once

#include "auton/Auton.h"
#include "util/Timer.h"
#include "util/Constants.h"
#include "nodes/subsystems/ILiftNode.h"

class LiftVoltageAction : public AutonAction {
private:
    ILiftNode* m_liftNode;
    Timer m_timer;
    int m_voltage;
    double m_time; // Time in seconds

public:
    LiftVoltageAction(ILiftNode* liftNode, int voltage=MAX_MOTOR_VOLTAGE, double time=0);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};