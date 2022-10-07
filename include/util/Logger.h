#pragma once

#include <vector>
#include <queue>
#include <string>
#include <memory>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include "lib-rr/nodes/NodeManager.h"

using namespace std;

class Logger {
public:
    enum LoggingLevel {
        INFO,
        WARNING,
        ERROR
    };
    static void logInfo(string message, bool sysLog=false);
    static void setConsoleLoggingLevel(LoggingLevel level);
    static void giveNodeManager(NodeManager * node_manager);
private:
    static LoggingLevel m_console_logging_level;
    static NodeManager * m_node_manager;
};
