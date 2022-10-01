#pragma once

#include "lib-rr/nodes/NodeManager.h"

class IRollerIntakeNode : public Node {
private:
    NodeManager* m_node_manager;
    std::string m_handle_name;

public:
    IRollerIntakeNode(NodeManager* node_manager, std::string handle_name): Node(node_manager, 10), m_node_manager(node_manager), m_handle_name(handle_name) {};

    virtual void initialize() = 0;

    virtual void setIntakeVoltage(int voltage) = 0;

    virtual void setIntakeVelocity(float velocity) = 0;

    virtual void openIntakes(int open) {};

    virtual void teleopPeriodic() {};

    virtual void autonPeriodic() {};

    virtual ~IRollerIntakeNode() {};
};
