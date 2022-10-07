#include "lib-rr/auton/auton_routines/TestTurnAuton.h"

TestTurnAuton::TestTurnAuton(IDriveNode* drive_node, InertialSensorNode* inertial_sensor_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node), 
        m_inertial_sensor_node(inertial_sensor_node) {
    
}

void TestTurnAuton::AddNodes() {
    Eigen::Rotation2Dd target_angle(M_PI_2);

    m_turn_node = new AutonNode(10, new TurnToAngleAction(m_drive_node, m_inertial_sensor_node, target_angle));
    Auton::AddFirstNode(m_turn_node);
}