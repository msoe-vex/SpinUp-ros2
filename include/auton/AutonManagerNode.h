#pragma once

#include "nodes/NodeManager.h"
#include "pathing/PathManager.h"
#include "auton/Auton.h"

class AutonManagerNode : public Node {
private:
    std::string pathJSON;

public:
    AutonManagerNode(NodeManager* node_manager, std::vector<Auton*> autons);

    Auton* selected_auton;
    std::vector<Auton*> m_autons;

    void initialize();
    
    void setPathsFile(std::string);

    void autonPeriodic();
};
