#pragma once

#include "auton/Auton.h"
#include "auton/AutonSequencePresets.h"
#include "nodes/subsystems/IDriveNode.h"
#include "nodes/odometry_nodes/OdometryNode.h"
#include "nodes/sensor_nodes/InertialSensorNode.h"
#include "auton/auton_actions/DriveStraightAction.h"
#include "auton/auton_actions/UseClawAction.h"
#include "auton/auton_actions/MoveLiftToPositionAction.h"
#include "auton/auton_actions/LiftVelocityAction.h"
#include "auton/auton_actions/FollowPathAction.h"
#include "pursuit/path_pursuit/TankPathPursuit.h"
#include "auton/auton_actions/RollerIntakeAction.h"
#include "pathing/PathManager.h"
#include "math/Pose.h"
#include "util/Constants.h"
#include "eigen/Eigen/Dense"
#include "nodes/subsystems/BackClawNode.h"
#include "auton/auton_actions/DeployAction.h"
#include "auton/auton_actions/SetBackClawStateAction.h"

class RightShortAuton : public Auton {
public:
    RightShortAuton(IDriveNode* driveNode, OdometryNode* odomNode, IClawNode* frontClawNode, IClawNode* wingArm, BackClawNode* rearClawNode, ILiftNode* liftNode, IRollerIntakeNode* intakeNode);

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