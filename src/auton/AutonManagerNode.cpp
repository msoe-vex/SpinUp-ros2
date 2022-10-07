#include "lib-rr/auton/AutonManagerNode.h"

AutonManagerNode::AutonManagerNode(NodeManager* node_manager, std::vector<Auton*> autons) : 
    Node(node_manager, 50), m_autons(autons) {
        selected_auton = m_autons.at(0);
        pathJSON = "/usd/paths/path.json";
}

void AutonManagerNode::initialize() {
    PathManager::GetInstance()->LoadPathsFile(pathJSON);
}

void AutonManagerNode::setPathsFile(std::string filename) {
    pathJSON = "/usd/paths/" + filename;
    PathManager::GetInstance()->LoadPathsFile(pathJSON);
}

void AutonManagerNode::autonPeriodic() {
    if(!selected_auton->Complete()) {
        selected_auton->AutonPeriodic();
    }
}