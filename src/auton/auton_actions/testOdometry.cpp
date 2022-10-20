#include "auton/auton_actions/testOdometry.h"

testOdometry::testOdometry(IDriveNode* drive_node, OdometryNode* odom_node) :
    m_drive_node(drive_node), 
    m_odom_node(odom_node) {
}

void testOdometry::ActionInit() {
    m_timer.Start();
    m_odom_node->initialize();

}

AutonAction::actionStatus testOdometry::Action() {
    Pose current_pose = m_odom_node->getCurrentPose();
    float current_x  = current_pose.position.x();
    float current_y  = current_pose.position.y();
    cout << "current X:" << current_x << endl;
    cout << "current Y:" << current_y << endl;
    return CONTINUE;
}

void testOdometry::ActionEnd() {
    m_timer.Stop();
}