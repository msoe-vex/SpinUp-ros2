#include "auton/auton_routines/tipping_point/OdomTest.h"

#define DRIVE_CONFIG {900., 5./3., M_PI * 3.25}

OdomTest::OdomTest(IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_inertial_sensor_node(inertial_sensor_node) {
    
}

void OdomTest::AddNodes() {
    //AutonNode* test = new AutonNode(100, new testOdometry(m_drive_node, m_odom_node));
    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, DRIVE_CONFIG, 24, 70, 80));
    DriveStraightAction::DriveStraightParams driveParams = {
        900.,
        5. / 3.,
        M_PI * 3.25
    };

    Auton::AddFirstNode(forward);

}