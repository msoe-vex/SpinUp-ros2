#include "lib-rr/auton/auton_actions/TurnToAngleAction.h"

TurnToAngleAction::TurnToAngleAction(IDriveNode* drive_node, InertialSensorNode* inertial_sensor, 
        Eigen::Rotation2Dd target_angle) : 
        m_drive_node(drive_node), 
        m_inertial_sensor(inertial_sensor), 
        m_target_angle(target_angle), 
        m_turning_pid(0.2, 0., 0., 0.1) {
}

void TurnToAngleAction::ActionInit() {
    m_turn_timer.Reset();
}

AutonAction::actionStatus TurnToAngleAction::Action() {    
    Eigen::Rotation2Dd current_angle(m_inertial_sensor->getYaw());

    double delta_angle = (m_target_angle.inverse() * current_angle).smallestAngle();

    double turning_power = delta_angle / M_PI * -1;

    float total_turn_input = m_turning_pid.calculate(turning_power);

    m_drive_node->setDriveVoltage(0, (int)(total_turn_input * MAX_MOTOR_VOLTAGE));

    if (m_inertial_sensor->isAtAngle(m_target_angle) && m_turn_timer.Get() == 0) {
        m_turn_timer.Start();
    } else {
        m_turn_timer.Stop();
    }

    if (m_turn_timer.Get() < 0.5) {
        return CONTINUE;
    } else {
        return END;
    }
}

void TurnToAngleAction::ActionEnd() {
    m_drive_node->setDriveVoltage(0, 0);
}