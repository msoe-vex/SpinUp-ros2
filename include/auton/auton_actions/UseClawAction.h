#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/nodes/subsystems/IClawNode.h"

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