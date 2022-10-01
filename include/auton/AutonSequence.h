#pragma once

#include "Auton.h"

class AutonSequence {
public:
    struct AutonSequenceList{
        AutonNode* headNode;
        AutonNode* tailNode;
    };

    AutonSequence(AutonNode* initialNode);

    void AddNext(AutonNode* source, AutonNode* node);

    void AddAction(AutonAction* action);

    void SetTailNode(AutonNode* tail);

    AutonSequenceList GetSequence();
    
    ~AutonSequence();

private:
    AutonSequenceList m_auton_sequence;
};