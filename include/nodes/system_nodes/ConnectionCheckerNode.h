#pragma once

#include "lib-rr/nodes/NodeManager.h"
#include "api.h"
#include "ros_lib/ros.h"

class ConnectionCheckerNode : public Node {
private:
    lv_style_t *notConnectedStyle;
    lv_style_t *connectedStyle;
    lv_obj_t * obj1;

    void m_checkStatus();

public:
    ConnectionCheckerNode(NodeManager* node_manager);

    void initialize();

    void teleopPeriodic();

    void autonPeriodic();

    ~ConnectionCheckerNode();
};
