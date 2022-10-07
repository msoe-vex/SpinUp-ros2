#include "lib-rr/auton/auton_actions/ConveyorAction.h"

ConveyorAction::ConveyorAction(IConveyorNode* conveyor_node, int voltage, double time) : 
        m_conveyor_node(conveyor_node), 
        m_voltage(voltage), 
        m_time(time) {
    
}

void ConveyorAction::ActionInit() {
    m_timer.Start();
}

AutonAction::actionStatus ConveyorAction::Action() {
    if (m_time <= 0) {
        m_conveyor_node->setConveyorVoltage(m_voltage);
        return END;
    } else {
        // Run until elapsed time is reached
        if (m_timer.Get() < m_time) {
            m_conveyor_node->setConveyorVoltage(m_voltage);
            return CONTINUE;
        } else {
            m_conveyor_node->setConveyorVoltage(0);
            return END;
        }
    }
}

void ConveyorAction::ActionEnd() {
    
}