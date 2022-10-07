#include "lib-rr/auton/auton_actions/LiftVelocityAction.h"

LiftVelocityAction::LiftVelocityAction(ILiftNode* liftNode, float velocity, double time) : 
        m_liftNode(liftNode), 
        m_velocity(velocity), 
        m_time(time) {
    
}

void LiftVelocityAction::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus LiftVelocityAction::Action() {
    if (m_time <= 0) {
        m_liftNode->setLiftVelocity(m_velocity);
        return END;
    } else {
        // Run until elapsed time is reached
        if (m_timer.Get() < m_time) {
            m_liftNode->setLiftVelocity(m_velocity);
            return CONTINUE;
        } else {
            m_liftNode->setLiftVelocity(0);
            return END;
        }
    }
}

void LiftVelocityAction::ActionEnd() {
    
}