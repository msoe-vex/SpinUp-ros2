#pragma once

#include <vector>

#include "api.h"
#include "ros_lib/ros.h"
#include "lib-rr/util/Constants.h"

class Node;

// The NodeManager class handles multiple things:
// 1) What nodes need to be called
// 2) When each node needs to be called
//
// Nodes are automatically added to the manager on creation as long as they
// inherit from the Node class below. This means you never should be calling
// addNode() explicitly!
class NodeManager {
private:
    struct NodeStructure {
        Node* node;
        uint32_t trigger_millis;
        uint32_t last_executed_millis;
    };

    std::vector<NodeStructure> m_node_structures;

    uint32_t(*m_get_millis)(void);

protected:

public:
    ros::NodeHandle* m_handle;
    NodeManager(uint32_t(*get_milliseconds)(void));

    ros::NodeHandle* addNode(Node* node, uint32_t interval_milliseconds);

    void initialize();

    void reset();

    void executeTeleop();

    void executeAuton();

    ~NodeManager();
};

// The Node class is the parent object of all Nodes on the robot. It outlines
// what a node should have, and gives us a common interface on how to interact
// with nodes.
//
// The constructor of the node object takes in a pointer to the node manager,
// which AUTOMATICALLY ADDS IT to the manager on creation. This means that you
// don't need to add nodes on your own!
//
// The interval at which a node is called is set within the Node's CPP file, in
// the superclass constructor (should look like :Node([manager], [time]))
class Node {
public:
    Node(NodeManager* node_manager, uint32_t interval_milliseconds) {
        m_handle = node_manager->addNode(this, interval_milliseconds);
    }

    ros::NodeHandle* m_handle;

    virtual void initialize() = 0;
    virtual void teleopPeriodic() {}
    virtual void autonPeriodic() {}
    virtual ~Node() {}
};