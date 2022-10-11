#pragma once

#include "auton/Auton.h"
#include "util/PID.h"
#include "util/Timer.h"
#include "util/Constants.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "eigen/Eigen/Dense"

class TurnToAngleAction : public AutonAction {
private:
    IDriveNode* m_drive_node;
    InertialSensorNode* m_inertial_sensor;
    Eigen::Rotation2Dd m_target_angle;
    Timer m_turn_timer;
    PID m_turning_pid;

public:
    TurnToAngleAction(IDriveNode* drive_node, InertialSensorNode* inertial_sensor, 
        Eigen::Rotation2Dd target_angle);

    void ActionInit();

    actionStatus Action();

    void ActionEnd();
};