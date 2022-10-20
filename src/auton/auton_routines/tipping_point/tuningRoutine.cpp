#include "auton/auton_routines/tuningRoutine.h"

tuningRoutine::tuningRoutine(IDriveNode* drive_node, OdometryNode* odometry_node) : 
        Auton("Tune DriveStraight"), 
        m_drive_node(drive_node),
        m_odometry_node(odometry_node){
    
}

void tuningRoutine::AddNodes() {
    m_forward_node = new AutonNode(10, new DriveStraightAction(m_drive_node, m_odometry_node, DRIVE_CONFIG, 38, 70, 80));
    Auton::AddFirstNode(m_forward_node);
}