#include "nodes/system_nodes/BatteryNode.h"

BatteryNode::BatteryNode (NodeManager* node_manager, std::string handle_name)
     : Node (node_manager, 200) {
    m_handle_name = handle_name.insert(0, "battery/");
}

void BatteryNode::initialize() {
}

void BatteryNode::teleopPeriodic() {
    
}

void BatteryNode::autonPeriodic() {
    
}

BatteryNode::~BatteryNode() {
}