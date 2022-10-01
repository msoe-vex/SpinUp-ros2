#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/ILiftNode.h"

class MoveLiftToPositionAction : public AutonAction {
private:
    ILiftNode* m_lift_node;
    int m_position;
    int m_tolerance;
    bool m_waitForCompletion;

public:
    MoveLiftToPositionAction(ILiftNode* lift_node, int position, int tolerance=20, bool waitForCompletion=false);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};