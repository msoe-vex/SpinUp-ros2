#include "lib-rr/nodes/system_nodes/ConnectionCheckerNode.h"

// By default, this constructor calls the constructor for the Node object in
// NodeManager.h
ConnectionCheckerNode::ConnectionCheckerNode(NodeManager* node_manager) : Node(node_manager, 500) {
    obj1 = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(obj1, 600, 400);
    lv_obj_set_style(obj1, &lv_style_plain_color);

    notConnectedStyle = (lv_style_t *)malloc( sizeof( lv_style_t ));
    connectedStyle = (lv_style_t *)malloc( sizeof( lv_style_t ));
    lv_style_copy(notConnectedStyle, &lv_style_plain_color);
    lv_style_copy(connectedStyle, notConnectedStyle);

    notConnectedStyle->body.main_color = LV_COLOR_RED;
    notConnectedStyle->body.grad_color = LV_COLOR_RED;
    connectedStyle->body.main_color = LV_COLOR_GREEN;
    connectedStyle->body.grad_color = LV_COLOR_GREEN;
}

void ConnectionCheckerNode::m_checkStatus() {
    if(Node::m_handle->connected()) {
        lv_obj_set_style(obj1, connectedStyle);
    } else {
        lv_obj_set_style(obj1, notConnectedStyle);
    }
    lv_obj_refresh_style(obj1);
}

void ConnectionCheckerNode::initialize() {
    lv_obj_set_style(obj1, notConnectedStyle);
}

void ConnectionCheckerNode::teleopPeriodic() {
    m_checkStatus();
}

void ConnectionCheckerNode::autonPeriodic() {
    m_checkStatus();
}

ConnectionCheckerNode::~ConnectionCheckerNode() { 

}