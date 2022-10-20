#include "auton/auton_routines/tipping_point/odomTest.h"

odomTest::odomTest(IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_node(odom_node),
        m_inertial_sensor_node(inertial_sensor_node) {
    
}

void odomTest::AddNodes() {
    AutonNode* test = new AutonNode(100, new testOdometry(m_drive_node, m_odom_node));
    Auton::AddFirstNode(test);

}