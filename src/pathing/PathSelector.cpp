#include "lib-rr/pathing/PathSelector.h"

std::string stripDotJSON(std::string s) {
    return s.substr(0, s.size() - 5);
}

void selectPathJSON(ControllerNode* controllerNode, AutonManagerNode* autonManagerNode) {
    std::ifstream file("/usd/paths/filenames.txt");

    if (file.is_open()) {
    
        // get list of files from filenames.txt
        std::vector<std::string> files;
        std::string line;
        while (std::getline(file, line)) {
            if (line.find(".json") != std::string::npos) {
                files.push_back(line);
            }
        }
        file.close();
        
        // vector that will store file names without .json
        std::vector<std::string> filenames(files);
        // https://stackoverflow.com/a/4807862
        std::transform(filenames.begin(), filenames.end(), filenames.begin(), stripDotJSON);

        autonManagerNode->setPathsFile(files.at(controllerNode->selectorMenu(filenames)));

    } else {
        controllerNode->getController()->set_text(0, 0, "filenames not read");
        pros::delay(2000);
    }

}