#include "auton/auton_routines/spin_up/PathTriggerTestAuton.h"

#define DRIVE_CONFIG {900., 5./3., M_PI * 3.25}

PathTriggerTestAuton::PathTriggerTestAuton(IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node) : 
        Auton("Test Turn Node", "/usd/paths/pathMatchAuton2-15.json"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_inertial_sensor_node(inertial_sensor_node) {
    
}

void PathTriggerTestAuton::AddNodes() {
    //AutonNode* test = new AutonNode(100, new testOdometry(m_drive_node, m_odom_node));
    /*AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, DRIVE_CONFIG, 24, 70, 80));
    DriveStraightAction::DriveStraightParams driveParams = {
        900.,
        5. / 3.,
        M_PI * 3.25
    };*/

    Path dragMiddleNeutral = PathManager::GetInstance()->GetPath("RipNeutral");
    
    AutonNode* wingReleaseDelay = new AutonNode(0.7, new WaitAction(0.7));
    wingReleaseDelay->AddCondition([](){return false;});

    std::map<std::string, AutonNode*> dragMiddleNeutralNodes = {
        {"1", wingReleaseDelay}
    };
    dragMiddleNeutral.setAutonNodes(dragMiddleNeutralNodes);

    AutonNode* goalDragToColorGoal = new AutonNode(
        45, 
        new FollowPathAction(
            m_drive_node, 
            m_odom_node, 
            new HolonomicPathPursuit(dragMiddleNeutral), 
            dragMiddleNeutral, 
            false
        )
    );

    Auton::AddFirstNode(goalDragToColorGoal);
}