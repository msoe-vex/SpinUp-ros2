#include "lib-rr/auton/auton_actions/ProfiledTurnAction.h"

ProfiledTurnAction::ProfiledTurnAction(IDriveNode* drive_node, InertialSensorNode* imu, Eigen::Rotation2Dd angle, double max_velocity, 
        double max_accel) :
        m_drive_node(drive_node), 
        m_imu(imu), 
        m_angle(angle), 
        m_max_velocity(max_velocity), 
        m_max_accel(max_accel), 
        m_lastSpeed(0), 
        m_feedForward(3.) {

}

void ProfiledTurnAction::ActionInit() {
    m_timer.Start();
}

ProfiledTurnAction::actionStatus ProfiledTurnAction::Action() {
    double dt = m_timer.Get() - m_lastTime;
    double speed = m_max_velocity;

    double accel = (m_max_velocity - m_lastSpeed) / dt;

    if (accel < -m_max_accel) {
        speed = m_lastSpeed - m_max_accel * dt;
    } else if (accel > m_max_accel) {
        speed = m_lastSpeed + m_max_accel * dt;
    }

    Eigen::Rotation2Dd m_actual = m_imu->getYaw();

    // Subtract the found offset of 3 inches to shorten the path
    double remainingAngle = (m_actual.inverse() * m_angle).smallestAngle();

    Logger::logInfo("Remaining angle: " + std::to_string(remainingAngle));

    double maxAllowedSpeed = sqrt(2 * m_max_accel * remainingAngle);
    if (fabs(speed) > maxAllowedSpeed) {
        speed = std::copysign(maxAllowedSpeed, speed);
    }

    speed = max(speed, m_feedForward);

    m_lastSpeed = speed;
    m_lastTime = m_timer.Get();

    if (remainingAngle < 0.5) {
        return END;
    } else {
        if (remainingAngle > 0) {
            m_drive_node->setDriveVelocity(0, 0, -speed);
        } else {
            m_drive_node->setDriveVelocity(0, 0, speed);
        }
        
        return CONTINUE;
    }
}

void ProfiledTurnAction::ActionEnd() {
    m_drive_node->setDriveVelocity(0, 0, 0);
}