#pragma once

#include <memory>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "pathing/Path.h"
#include "pathing/PathPoint.h"
#include "3rdparty/json.hpp"
#include "math/Math.h"
#include "util/Logger.h"

using namespace nlohmann;
using namespace std;

class PathManager {
public:
    static PathManager* GetInstance();

    bool LoadPathsText(string text);
    bool LoadPaths(json pathJson);
    bool LoadPathsFile(string filePath);

    int NumPaths();

    unordered_map<string, Path> GetPaths();

    Path GetPath(string name);

private:
    PathManager() = default;
    unordered_map<string, Path> m_paths;
    static PathManager* m_instance;
};