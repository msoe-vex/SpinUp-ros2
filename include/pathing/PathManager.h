#pragma once

#include <memory>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "lib-rr/pathing/Path.h"
#include "lib-rr/pathing/PathPoint.h"
#include "lib-rr/3rdparty/json.hpp"
#include "lib-rr/math/Math.h"
#include "lib-rr/util/Logger.h"

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