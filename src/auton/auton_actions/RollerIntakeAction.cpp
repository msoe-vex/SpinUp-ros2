#include "lib-rr/auton/auton_actions/RollerIntakeAction.h"

RollerIntakeAction::RollerIntakeAction(IRollerIntakeNode* intake_node, int voltage, double time) : 
        m_intake_node(intake_node), 
        m_voltage(voltage), 
        m_time(time) {
    
}

void RollerIntakeAction::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus RollerIntakeAction::Action() {
    if (m_time <= 0) {
        m_intake_node->setIntakeVoltage(m_voltage);
        return END;
    } else {
        // Run until elapsed time is reached
        if (m_timer.Get() < m_time) {
            m_intake_node->setIntakeVoltage(m_voltage);
            return CONTINUE;
        } else {
            m_intake_node->setIntakeVoltage(0);
            return END;
        }
    }
}

void RollerIntakeAction::ActionEnd() {
    
}