#include "lib-rr/auton/auton_actions/LiftVoltageAction.h"

LiftVoltageAction::LiftVoltageAction(ILiftNode* liftNode, int voltage, double time) : 
        m_liftNode(liftNode), 
        m_voltage(voltage), 
        m_time(time) {
    
}

void LiftVoltageAction::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus LiftVoltageAction::Action() {
    if (m_time <= 0) {
        m_liftNode->setLiftVoltage(m_voltage);
        return END;
    } else {
        // Run until elapsed time is reached
        if (m_timer.Get() < m_time) {
            m_liftNode->setLiftVoltage(m_voltage);
            return CONTINUE;
        } else {
            m_liftNode->setLiftVoltage(0);
            return END;
        }
    }
}

void LiftVoltageAction::ActionEnd() {
    
}