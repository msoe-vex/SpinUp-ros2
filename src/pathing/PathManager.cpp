#include "lib-rr/pathing/PathManager.h"

PathManager* PathManager::m_instance = nullptr;

PathManager * PathManager::GetInstance() {
    if(!m_instance) {
        m_instance = new PathManager;
    }

    return m_instance;
}

int PathManager::NumPaths() {
    return m_paths.size();
}

bool PathManager::LoadPathsText(string text) {
    json loadedJson;

    try {
        loadedJson = json::parse(text);
    } catch (const exception& e) {
        Logger::logInfo("Could not parse paths file:" + string(e.what()));
        return false;
    }

    return LoadPaths(loadedJson);
}

bool PathManager::LoadPaths(json loadedJson) {
    m_paths.clear();

    try {
        for (auto pathJson : loadedJson["paths"]) {
            string name = pathJson["name"];
            vector<PathPoint> pathPoints;

            Logger::logInfo("Path name: " + name, true);
            for (auto point : pathJson["points"]) {
                Vector2d linear_velocity(point["vx"], point["vy"]);
                float time = point["time"];
                float rotational_velocity = point["omega"];
                Rotation2Dd rotation(toRadians(point["theta"]));
                Vector2d position(point["x"], point["y"]);
                pathPoints.push_back(PathPoint(time, Pose(position, rotation), linear_velocity, rotational_velocity));
                Logger::logInfo(" Time: " + std::to_string(time) +  " Pose: " + std::to_string(position.x()) + " " + std::to_string(position.y()) + " velocity: " + std::to_string(linear_velocity.x()) +  " " + std::to_string(linear_velocity.y()));
            }
            Path newPath(pathPoints);
            m_paths[name] = newPath;
        }
    } catch (const exception& e) {
        Logger::logInfo("Error reading json path! " + string(e.what()), true);
        return false;
    }

    return true;
}

bool PathManager::LoadPathsFile(string filePath) {
    ifstream pathsFile;
    try {
        pathsFile.open(filePath);
        if(!pathsFile.is_open()) {
            Logger::logInfo("Could not open paths file at " + filePath, true);
            return false;
        }
    } catch (const exception& e) {
        Logger::logInfo("Could not open paths file at " + filePath + " : " + string(e.what()), true);
        return false;
    }

    json loadedJson;
    try {
        pathsFile >> loadedJson;
    } catch (const exception& e) {
        Logger::logInfo("Could not parse paths file:" + string(e.what()), true);
        pathsFile.close();
        return false;
    }

    pathsFile.close();
    return LoadPaths(loadedJson);
}

unordered_map<string, Path> PathManager::GetPaths() {
    return m_paths;
}

Path PathManager::GetPath(string name) {
    if (m_paths.find(name) == m_paths.end()) {
        Logger::logInfo("Path with key: " + name + " not found!", true);
        return m_paths[m_paths.begin()->first];
    } else {
        return m_paths[name];
    }   
}