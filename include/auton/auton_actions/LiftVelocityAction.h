#pragma once

#include "auton/Auton.h"
#include "util/Timer.h"
#include "util/Constants.h"
#include "nodes/subsystems/ILiftNode.h"

class LiftVelocityAction : public AutonAction {
private:
    ILiftNode* m_liftNode;
    Timer m_timer;
    float m_velocity;
    double m_time; // Time in seconds

public:
    LiftVelocityAction(ILiftNode* liftNode, float velocity=MAX_VELOCITY, double time=0);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};