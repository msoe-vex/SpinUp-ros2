#pragma once

#include "nodes/NodeManager.h"

class IShooterNode : public Node {
private:
    NodeManager* m_node_manager;
    std::string m_handle_name;

public:
    IShooterNode(NodeManager* node_manager, std::string handle_name): Node(node_manager, 10), m_node_manager(node_manager), m_handle_name(handle_name) {};

    virtual void initialize() = 0;

    virtual void setShootVoltage(int voltage) = 0;

    virtual void setShootVelocity(float velocity) = 0;

    virtual void openIntakes(int open) {};

    virtual void teleopPeriodic() {};

    virtual void autonPeriodic() {};

    virtual ~IShooterNode() {};
};
