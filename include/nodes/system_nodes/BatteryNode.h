#pragma once

#include "nodes/NodeManager.h"
#include "api.h"

class BatteryNode : public Node {
private:
    std::string m_handle_name;

public:
    BatteryNode(NodeManager* node_manager, std::string handle_name);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~BatteryNode();
};