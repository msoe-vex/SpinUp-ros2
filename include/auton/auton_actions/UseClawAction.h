#pragma once

#include "api.h"
#include "auton/Auton.h"
#include "util/Timer.h"
#include "util/Constants.h"
#include "nodes/subsystems/IClawNode.h"

class UseClawAction : public AutonAction {
private:
    IClawNode* m_claw_node;
    bool m_position;

public:
    UseClawAction(IClawNode* claw_node, bool position);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};