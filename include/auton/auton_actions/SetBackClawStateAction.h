#pragma once

#include "api.h"
#include "auton/Auton.h"
#include "util/Timer.h"
#include "util/Constants.h"
#include "nodes/subsystems/BackClawNode.h"

class SetBackClawStateAction : public AutonAction {
private:
    BackClawNode* m_backClaw;
    BackClawNode::BackClawState m_state;

public:
    SetBackClawStateAction(BackClawNode* backClaw, BackClawNode::BackClawState state);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};