#include "pathing/Path.h"

Path::Path() : 
        m_is_complete(false),
        m_last_point(0, Pose(), Vector2d(0., 0.), 0.) {
    
}

Path::Path(std::vector<PathPoint> pathPoints) : 
        m_pathPoints(pathPoints),
        m_is_complete(false),
        m_last_point(pathPoints.back()) {
}

Pose Path::update(float time) {
    if (m_pathPoints.size() == 0 || m_pathPoints.size() == 1) {
        m_is_complete = true;
        return m_last_point.getPose();
    } else {
        // Remove any points that have been passed
        for (auto it = m_pathPoints.begin(); it != --m_pathPoints.end() && it != m_pathPoints.end(); it++) {
            if (time > (it + 1)->getTime()) { // Point has been passed
                std::vector<std::string> actions = (*it).getAutonActionNames();
                for (auto action : actions) {
                    if (m_auton_nodes.count(action) > 0) {
                        m_auton_nodes.at(action)->AddCondition([](){return true;});                        
                    }
                }
                m_pathPoints.erase(it);
            } else { // Point not yet reached 
                break;
            }
        }

        //auto path_point = m_pathPoints.begin()->interpolateTo(*(m_pathPoints.begin() + 1), time);
        //return path_point.getPose();
        return (m_pathPoints.begin() + 1)->getPose(); // Temporary fix until interpolation works
    }
}

std::vector<PathPoint> Path::getPathPoints() {
    return m_pathPoints;
}

void Path::setAutonNodes(std::map<std::string, AutonNode*> auton_nodes) {
    //m_auton_actions.insert(m_auton_actions.end(), auton_actions.begin(), auton_actions.end());
    m_auton_nodes = auton_nodes;
}

bool Path::isComplete() {
    return m_is_complete;
}