#pragma once

#include "nodes/NodeManager.h"
#include "auton/AutonManagerNode.h"
#include "nodes/actuator_nodes/MotorNode.h"
#include "nodes/sensor_nodes/ADIAnalogInNode.h"
#include "nodes/sensor_nodes/ADIDigitalInNode.h"
#include "nodes/sensor_nodes/ADIEncoderNode.h"
#include "nodes/sensor_nodes/ADIGyroNode.h"
#include "nodes/sensor_nodes/ADIUltrasonicNode.h"
#include "nodes/sensor_nodes/ADIPotentiometerNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "nodes/sensor_nodes/ControllerNode.h"
#include "nodes/system_nodes/CompetitionStatusNode.h"
#include "nodes/system_nodes/ProsTimeNode.h"
#include "nodes/system_nodes/BatteryNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "nodes/system_nodes/ConnectionCheckerNode.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/subsystems/IConveyorNode.h"
#include "nodes/subsystems/IRollerIntakeNode.h"
#include "auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/FollowPathAction.h"
#include "eigen/Eigen/Dense"
#include "pathing/PathManager.h"
#include "pathing/PathSelector.h"
#include "auton/AutonSelector.h"
#include "nodes/subsystems/HolonomicDriveNode.h"
#include "nodes/subsystems/TankDriveNode.h"
#include "nodes/subsystems/IntakeNode.h"
#include "nodes/subsystems/ShooterNode.h"
#include "nodes/subsystems/ClawNode.h"
#include "nodes/subsystems/RollerNode.h"

class IRobot {
public:
    /* Controllers */
    ControllerNode *primary_controller;
    
    virtual void initialize() = 0;
    virtual void disabled() = 0;
    virtual void competition_initialize() = 0;
    virtual void autonomous() = 0;
    virtual void opcontrol() = 0;
};
