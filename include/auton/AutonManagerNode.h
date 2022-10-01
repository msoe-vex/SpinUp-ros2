#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "lib-rr/pathing/PathManager.h"
#include "lib-rr/auton/Auton.h"

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
