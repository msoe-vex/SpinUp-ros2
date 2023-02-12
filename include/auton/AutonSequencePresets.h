#pragma once

//#include "api.h"
#include "Constants.h"
#include "auton/Auton.h"
#include "auton/AutonSequence.h"
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


/**
 * This function is used to generate a sequence to score balls in a goal.
 * This should follow the node that makes the robot drive into the goal
 */
AutonNode* getPreloadsSequence(AutonNode* initial_node, IDriveNode* drive_node, OdometryNode* odom_node);

// AutonNode* getDoubleGoalScoringSequence(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* getMiddleGoalScoringSequence(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal4ToGoal1(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal1ToGoal2(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal2ToGoal3(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal3ToGoal6(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal6ToGoal9(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal9ToGoal8(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal8ToGoal7(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);

// AutonNode* addActionsToPath_Goal7ToGoal5(AutonNode* initial_node, IntakeNode* intake_node, ConveyorNode* conveyor_node);