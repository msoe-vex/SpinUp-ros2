#pragma once

#include "api.h"
#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "nodes/BackClawNode.h"

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