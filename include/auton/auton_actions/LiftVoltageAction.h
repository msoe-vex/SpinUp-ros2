#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"

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