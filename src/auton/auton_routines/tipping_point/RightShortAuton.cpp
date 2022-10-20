#include "auton/auton_routines/RightShortAuton.h"

RightShortAuton::RightShortAuton(IDriveNode* driveNode, OdometryNode* odomNode, IClawNode* frontClawNode, IClawNode* wingArm, BackClawNode* backClawNode, ILiftNode* liftNode, IRollerIntakeNode* intakeNode) : 
        Auton("15in Right Short Auton", "/usd/rightQuickPath.json"), 
        m_driveNode(driveNode),
        m_odomNode(odomNode),
        m_frontClawNode(frontClawNode),
        m_wingArm(wingArm),
        m_backClawNode(backClawNode),
        m_liftNode(liftNode),
        m_intakeNode(intakeNode) {
    
}

void RightShortAuton::AddNodes() {
    // Set the starting position, as measured on the field
    Pose startingPose(Vector2d(33., 15.25), Rotation2Dd(M_PI_2+toRadians(36)));
    m_odomNode->setCurrentPose(startingPose); // was (31.917, 14.25)

    AutonNode* deploy = new AutonNode(0.1, new DeployAction());
    Auton::AddFirstNode(deploy);

    AutonNode* liftDownForCenterDash = new AutonNode(0.1, new MoveLiftToPositionAction(m_liftNode, 270, 10));

    AutonNode* wingArmDeploy = new AutonNode(0.1, new UseClawAction(m_wingArm, false));

    //Original Parameters 41.5, 65,90
    AutonNode* forward = new AutonNode(5, new DriveStraightAction(m_driveNode, m_odomNode, DRIVE_CONFIG, 41, 70, 90, .5));

    deploy->AddNext(forward);
    deploy->AddNext(liftDownForCenterDash);
    deploy->AddNext(wingArmDeploy);

    //AutonNode* backward = new AutonNode(1.5, new DriveStraightAction(m_driveNode, m_odomNode, -20, 70, 80));

    AutonNode* wingArmRetractGrab = new AutonNode(0.1, new UseClawAction(m_wingArm, true));

    //forward->AddNext(backward);
    forward->AddNext(wingArmRetractGrab);

    AutonNode* wingReleaseDelay = new AutonNode(0.7, new WaitAction(0.7));
    // // Helpful at dragging goal to side

    AutonNode* wingArmDeployRelease = new AutonNode(0.1, new UseClawAction(m_wingArm, false));
    AutonNode* backClawOpen = new AutonNode(0.1, new SetBackClawStateAction(m_backClawNode, BackClawNode::PIVOT_DOWN_CLAW_OPEN));

    Path dragMiddleNeutral = PathManager::GetInstance()->GetPath("RipNeutral");
    AutonNode* goalDragToColorGoal = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(dragMiddleNeutral), 
            dragMiddleNeutral, 
            false
        )
    );

    forward->AddNext(goalDragToColorGoal);
    goalDragToColorGoal->AddNext(wingReleaseDelay);
    goalDragToColorGoal->AddNext(backClawOpen);


    wingReleaseDelay->AddNext(wingArmDeployRelease);

    Path toBlueGoal = PathManager::GetInstance()->GetPath("ToBlue");
    AutonNode* ToBlueGoal = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(toBlueGoal), 
            toBlueGoal, 
            false
        )
    );

    wingArmDeployRelease->AddNext(ToBlueGoal);

    AutonNode* backClawCloseColor = new AutonNode(0.1, new SetBackClawStateAction(m_backClawNode, BackClawNode::PIVOT_BACK));

    ToBlueGoal->AddNext(backClawCloseColor);

    AutonNode* clawOpen = new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));
    
    ToBlueGoal->AddNext(clawOpen);

    Path blueToNeutralLeft = PathManager::GetInstance()->GetPath("ToNeutralLeft");
    AutonNode* toNeutralLeft = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(blueToNeutralLeft), 
            blueToNeutralLeft, 
            false
        )
    );

    ToBlueGoal->AddNext(toNeutralLeft);
    
    AutonNode* clawOpen2 = new AutonNode(0.5, new UseClawAction(m_frontClawNode, true));
    toNeutralLeft->AddNext(clawOpen2);

    //LiftForNeutral

    Path liftForNeutral = PathManager::GetInstance()->GetPath("LiftForNeutral");
    AutonNode* LiftForNeutral = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(liftForNeutral), 
            liftForNeutral, 
            false
        )
    );

    toNeutralLeft->AddNext(LiftForNeutral);

    AutonNode* clawClose = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));
    LiftForNeutral->AddNext(clawClose);

    AutonNode* liftUp = new AutonNode(0.5, new MoveLiftToPositionAction(m_liftNode, 1800, 10, true));
    clawClose->AddNext(liftUp);

    AutonNode* wingArmRetract = new AutonNode(0.1, new UseClawAction(m_wingArm, true));
    clawClose->AddNext(wingArmRetract);

    AutonNode* wait = new AutonNode(1.0, new WaitAction(1.0));
    wingArmRetract->AddNext(wait);

    AutonNode* liftDown = new AutonNode(0.5, new MoveLiftToPositionAction(m_liftNode, 700, 10));
    wait->AddNext(liftDown);

    Path neutralGoalGrabToReversePath = PathManager::GetInstance()->GetPath("NeutralGoalGrabToReverse");
    AutonNode* neutralGoalGrabToReverse = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(neutralGoalGrabToReversePath), 
            neutralGoalGrabToReversePath, 
            false
        )
    );

    liftDown->AddNext(neutralGoalGrabToReverse);

    Path reversePointToCornerPath = PathManager::GetInstance()->GetPath("ReversePointToCorner");
    AutonNode* reversePointToCorner = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(reversePointToCornerPath), 
            reversePointToCornerPath, 
            false
        )
    );

    reversePointToCorner->AddAction(new RollerIntakeAction(m_intakeNode));

    neutralGoalGrabToReverse->AddNext(reversePointToCorner);

    AutonNode* releaseGoal = new AutonNode(0.1, new UseClawAction(m_frontClawNode, true));
    reversePointToCorner->AddNext(releaseGoal);

    Path ToHandCollect = PathManager::GetInstance()->GetPath("ToCollectHandRings");
    AutonNode* toHandCollect = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(ToHandCollect), 
            ToHandCollect, 
            false
        )
    );

    releaseGoal->AddNext(toHandCollect);

    AutonNode* preloads2 = getPreloadsSequence(toHandCollect, m_driveNode, m_odomNode);
   
    AutonNode* forward1 = new AutonNode(1.5, new DriveStraightAction(m_driveNode, m_odomNode, DRIVE_CONFIG, 15, 10, 80));
    preloads2->AddNext(forward1);

    AutonNode* wait3 = new AutonNode(5., new WaitAction(5.));
    
    forward1->AddNext(wait3);
 
    AutonNode* backward1 = new AutonNode(1.5, new DriveStraightAction(m_driveNode, m_odomNode, DRIVE_CONFIG, -15, 10, 80));
    wait3->AddNext(backward1);
 
    AutonNode* preloads3 = getPreloadsSequence(backward1, m_driveNode, m_odomNode);

    AutonNode* conveyorStop2 = new AutonNode(0.1, new RollerIntakeAction(m_intakeNode, 0));

    preloads3->AddNext(conveyorStop2);

    AutonNode* liftDown2 = new AutonNode(0.5, new MoveLiftToPositionAction(m_liftNode, 275, 10));

    Path ReturnToCornerGoalPath = PathManager::GetInstance()->GetPath("ReturnToCornerGoal");
    AutonNode* ReturnToCornerGoal = new AutonNode(
        45, 
        new FollowPathAction(
            m_driveNode, 
            m_odomNode, 
            new TankPathPursuit(ReturnToCornerGoalPath), 
            ReturnToCornerGoalPath, 
            false
        )
    );

    AutonNode* waitForRearGoalDrop = new AutonNode(0.5, new WaitAction(0.5));

    conveyorStop2->AddNext(liftDown2);
    conveyorStop2->AddNext(ReturnToCornerGoal);
    conveyorStop2->AddNext(waitForRearGoalDrop);

    AutonNode* rearGoalDrop = new AutonNode(0.5, new SetBackClawStateAction(m_backClawNode, BackClawNode::PIVOT_DOWN_CLAW_OPEN));

    waitForRearGoalDrop->AddNext(rearGoalDrop);

    AutonNode* clawClose2 = new AutonNode(0.5, new UseClawAction(m_frontClawNode, false));
    ReturnToCornerGoal->AddNext(clawClose2);
}