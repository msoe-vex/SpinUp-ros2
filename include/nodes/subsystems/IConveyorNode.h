#pragma once

#include "lib-rr/nodes/NodeManager.h"

class IConveyorNode : public Node {
private:
    NodeManager* m_node_manager;
    std::string m_handle_name;

public:
    IConveyorNode(NodeManager* node_manager, std::string handle_name): Node(node_manager, 10), m_node_manager(node_manager), m_handle_name(handle_name) {};

    virtual void setConveyorVoltage(int voltage) = 0;

    virtual void setConveyorVelocity(float velocity) = 0;

    virtual void initialize() = 0;

    virtual void teleopPeriodic() {};

    virtual void autonPeriodic() {};

    virtual ~IConveyorNode() {};
};
