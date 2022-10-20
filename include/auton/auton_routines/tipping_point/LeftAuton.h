#pragma once

#include "lib-rr/auton/Auton.h"
#include "Constants.h"
#include "auton/AutonSequencePresets.h"
#include "lib-rr/nodes/subsystems/IDriveNode.h"
#include "lib-rr/nodes/odometry_nodes/OdometryNode.h"
#include "lib-rr/nodes/sensor_nodes/InertialSensorNode.h"
#include "lib-rr/auton/auton_actions/DriveStraightAction.h"
#include "lib-rr/auton/auton_actions/UseClawAction.h"
#include "lib-rr/auton/auton_actions/MoveLiftToPositionAction.h"
#include "lib-rr/auton/auton_actions/LiftVelocityAction.h"
#include "lib-rr/auton/auton_actions/FollowPathAction.h"
#include "lib-rr/pursuit/path_pursuit/TankPathPursuit.h"
#include "lib-rr/auton/auton_actions/RollerIntakeAction.h"
#include "lib-rr/pathing/PathManager.h"
#include "lib-rr/math/Pose.h"
#include "lib-rr/util/Constants.h"
#include "lib-rr/eigen/Eigen/Dense"
#include "nodes/BackClawNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "auton/auton_actions/SetBackClawStateAction.h"

class LeftAuton : public Auton {
public:
    LeftAuton(IDriveNode* driveNode, OdometryNode* odomNode, IClawNode* frontClawNode, IClawNode* wingArm, BackClawNode* rearClawNode, ILiftNode* liftNode, IRollerIntakeNode* intakeNode);

    void AddNodes();

private:
    IDriveNode* m_driveNode;
    OdometryNode* m_odomNode;
    IClawNode* m_frontClawNode;
    IClawNode* m_wingArm;
    BackClawNode* m_backClawNode;
    ILiftNode* m_liftNode;
    IRollerIntakeNode* m_intakeNode;
};