#include "lib-rr/auton/auton_actions/DriveToPoseAction.h"

DriveToPoseAction::DriveToPoseAction(IDriveNode* drive_node, OdometryNode* odom_node, IPosePursuit* pursuit, Pose end_pose) :
        m_drive_node(drive_node),
        m_odom_node(odom_node), 
        m_pursuit(pursuit),
        m_end_pose(end_pose){

}

void DriveToPoseAction::ActionInit() {
    m_pursuit->startPursuit();
}

AutonAction::actionStatus DriveToPoseAction::Action() {
    IPursuit::TargetVelocity target_velocity = m_pursuit->getTargetVelocity(m_odom_node->getCurrentPose());

    m_drive_node->setDriveVelocity(target_velocity.linear_velocity.x(), target_velocity.linear_velocity.y(), target_velocity.rotational_velocity);

    if (m_timer.Get() == 0 && target_velocity.is_within_end_tolerance) {
        m_timer.Start();
    } else if (m_timer.Get() > 0 && !target_velocity.is_within_end_tolerance) {
        m_timer.Reset();
    } else if (m_timer.Get() > 0.5) {
        return END;
    }

    return CONTINUE;
}

void DriveToPoseAction::ActionEnd() {
    m_drive_node->setDriveVelocity(0, 0, 0);
}