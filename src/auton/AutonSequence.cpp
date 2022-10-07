#include "lib-rr/auton/AutonSequence.h"

AutonSequence::AutonSequence(AutonNode* initialNode) {
    m_auton_sequence = { initialNode, initialNode };
}

void AutonSequence::AddNext(AutonNode* source, AutonNode* node) {
    source->AddNext(node);
}

void AutonSequence::AddAction(AutonAction* action) {
    m_auton_sequence.tailNode->AddAction(action);
}

void AutonSequence::SetTailNode(AutonNode* tail) {
    m_auton_sequence.tailNode = tail;
}

AutonSequence::AutonSequenceList AutonSequence::GetSequence() {
    return m_auton_sequence;
}

AutonSequence::~AutonSequence() {
    
}