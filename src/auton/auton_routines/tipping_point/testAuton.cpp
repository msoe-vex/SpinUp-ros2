#include "auton/auton_routines/testAuton.h"

testAuton::testAuton(ILiftNode* lift_node) : 
        Auton("Test Turn Node"), 
        m_lift_node(lift_node) {
    
}

void testAuton::AddNodes() {
    AutonNode* test = new AutonNode(100, new MoveLiftToPositionAction(m_lift_node, 100, 10));
    Auton::AddFirstNode(test);

}