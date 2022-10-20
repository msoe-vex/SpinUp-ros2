#include "auton/AutonSequencePresets.h"

AutonNode* getPreloadsSequence(AutonNode* initial_node, IDriveNode* drive_node, OdometryNode* odom_node) {
    AutonNode* forward = new AutonNode(1.5, new DriveStraightAction(drive_node, odom_node, DRIVE_CONFIG, 15, 10, 80));
    initial_node->AddNext(forward);

    AutonNode* backward = new AutonNode(1.5, new DriveStraightAction(drive_node, odom_node, DRIVE_CONFIG, -15, 10, 80));
    forward->AddNext(backward);

    return backward;
}