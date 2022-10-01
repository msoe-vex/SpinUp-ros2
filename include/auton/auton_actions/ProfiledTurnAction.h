#pragma once

#include <math.h>
#include "lib-rr/auton/Auton.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/eigen/Eigen/Dense"

class ProfiledTurnAction : public AutonAction {
private:
    IDriveNode* m_drive_node;
    Timer m_timer;
    Eigen::Rotation2Dd m_angle;
    double m_max_velocity;
    double m_max_accel;
    double m_lastSpeed;
    double m_lastTime;
    double m_feedForward;
    InertialSensorNode* m_imu;

public:
    ProfiledTurnAction(IDriveNode* drive_node, InertialSensorNode* imu, Eigen::Rotation2Dd angle, double max_velocity, 
        double max_accel);

    void ActionInit();
    actionStatus Action();
    void ActionEnd();
};