#include "auton/auton_actions/SetBackClawStateAction.h"

SetBackClawStateAction::SetBackClawStateAction(BackClawNode* backClaw, BackClawNode::BackClawState state) : 
        m_backClaw(backClaw), 
        m_state(state)  {
    
}

void SetBackClawStateAction::ActionInit() {

}

AutonAction::actionStatus SetBackClawStateAction::Action() {
    m_backClaw->setState(m_state);
    return END;
}

void SetBackClawStateAction::ActionEnd() {
    
}