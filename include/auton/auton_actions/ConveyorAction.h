#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/nodes/subsystems/IConveyorNode.h"

class ConveyorAction : public AutonAction {
private:
    IConveyorNode* m_conveyor_node;
    Timer m_timer;
    int m_voltage;
    double m_time; // Time in seconds

public:
    ConveyorAction(IConveyorNode* conveyor_node, int voltage=MAX_MOTOR_VOLTAGE, double time=0);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};