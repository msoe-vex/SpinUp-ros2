#include "auton/auton_routines/tipping_point/OdomTest.h"
#include "pathing/Path.h"
#include "pathing/PathManager.h"
#include "pursuit/path_pursuit/HolonomicPathPursuit.h"
#include "auton/auton_actions/FollowPathAction.h"

#define DRIVE_CONFIG {900., 5./3., M_PI * 3.25}

OdomTest::OdomTest(IDriveNode* drive_node, OdometryNode* odom_node, InertialSensorNode* inertial_sensor_node) : 
        Auton("Test Turn Node"), 
        m_drive_node(drive_node),
        m_odom_nodedom_node),
        m_inertial_:wsensor_node(inertial_sensor_node) {
    
}

void OdomTest::AddNodes() {
    //AutonNode* test = new AutonNode(100, new testOdometry(m_drive_node, m_odom_node));
    AutonNode* forward = new AutonNode(2, new DriveStraightAction(m_drive_node, m_odom_node, DRIVE_CONFIG, 24, 70, 80));
    DriveStraightAction::DriveStraightParams driveParams = {
        900.,
        5. / 3.,
        M_PI * 3.25
    };

    Auton::AddFirstNode(forward);
    
    Path dragMiddleNeutral = PathManager::GetInstance()->GetPath("RipNeutral");
    AutonNode* goalDragToColorGoal = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new HolonomicPathPursuit(dragMiddleNeutral), 
            dragMiddleNeutral, 
            false
        )
    );

}