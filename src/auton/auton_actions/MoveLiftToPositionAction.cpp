#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"

MoveLiftToPositionAction::MoveLiftToPositionAction(ILiftNode* lift_node, int position, int tolerance, bool waitForCompletion) : 
        m_lift_node(lift_node), 
        m_position(position),
        m_tolerance(tolerance),
        m_waitForCompletion(waitForCompletion) {
    
}

void MoveLiftToPositionAction::ActionInit() {

}

AutonAction::actionStatus MoveLiftToPositionAction::Action() {
    m_lift_node->setLiftPosition(m_position, m_tolerance);

    if (!m_waitForCompletion) {
        return END;
    } else {
        int currentPos = m_lift_node->getPosition();
        int lowerBound = m_position - m_tolerance;
        int upperBound = m_position + m_tolerance;

        if (currentPos < lowerBound || currentPos > upperBound) {
            return CONTINUE;
        } else {
            return END;
        }
    }
    
}

void MoveLiftToPositionAction::ActionEnd() {
    
}