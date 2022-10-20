#include "nodes/system_nodes/CompetitionStatusNode.h"

CompetitionStatusNode::CompetitionStatusNode (NodeManager* node_manager, 
    std::string handle_name) : Node(node_manager, 100) {
    m_handle_name = handle_name.insert(0, "compStatus/");
}

void CompetitionStatusNode::initialize() {
}

void CompetitionStatusNode::teleopPeriodic() {
    
}

void CompetitionStatusNode::autonPeriodic() {
    
}

CompetitionStatusNode::~CompetitionStatusNode () {
}
