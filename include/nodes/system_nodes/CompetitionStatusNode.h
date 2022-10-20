#pragma once

#include "nodes/NodeManager.h"
#include "api.h"
#include "pros/misc.h"

class CompetitionStatusNode : public Node {
private: 
    std::string m_handle_name;

public:
    CompetitionStatusNode(NodeManager* node_manager, std::string handle_name);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~CompetitionStatusNode();
};