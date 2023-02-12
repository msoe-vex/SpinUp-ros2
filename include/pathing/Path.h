#pragma once

#include <vector>
#include <map>
#include <iostream>
#include "eigen/Eigen/Dense"
#include "pathing/PathPoint.h"
#include "math/Pose.h"
#include "auton/Auton.h"

class Path {
public:
    Path();

    Path(std::vector<PathPoint> pathPoints);

    Pose update(float time);

    std::vector<PathPoint> getPathPoints();

    void setAutonNodes(std::map<std::string, AutonNode*> auton_nodes);
    
    bool isComplete();

private:
    std::vector<PathPoint> m_pathPoints;
    PathPoint m_last_point;
    std::map<std::string, AutonNode*> m_auton_nodes;
    bool m_is_complete;
};