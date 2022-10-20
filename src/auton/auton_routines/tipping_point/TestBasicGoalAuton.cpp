#include "auton/auton_routines/TestBasicGoalAuton.h"

TestBasicGoalAuton::TestBasicGoalAuton(IDriveNode* drive_node, OdometryNode* odom_node, IClawNode* claw_node) : 
        Auton("Test Path Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_claw_node(claw_node), 
        m_path_manager(PathManager::GetInstance()) {

}

void TestBasicGoalAuton::AddNodes() {
    AutonNode* claw_up = new AutonNode(0.5, new UseClawAction(m_claw_node, true));
    Auton::AddFirstNode(claw_up);
    
    Path path = m_path_manager->GetPath("GrabGoalGoBack");
    TankPathPursuit* pursuit = new TankPathPursuit(path); 
    m_path_node = new AutonNode(20, new FollowPathAction(m_drive_node, m_odom_node, pursuit, path, true));
    claw_up->AddNext(m_path_node);

    AutonNode* wait = new AutonNode(3, new WaitAction(3));
    claw_up->AddNext(wait);

    AutonNode* claw_down = new AutonNode(0.5, new UseClawAction(m_claw_node, false));
    wait->AddNext(claw_down);
}