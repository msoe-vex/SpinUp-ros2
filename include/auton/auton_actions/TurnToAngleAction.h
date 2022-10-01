#pragma once

#include "lib-rr/auton/Auton.h"
#include "lib-rr/util/PID.h"
#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/eigen/Eigen/Dense"

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