#include "lib-rr/util/Logger.h"

Logger::LoggingLevel Logger::m_console_logging_level;
NodeManager* Logger::m_node_manager = nullptr;

void Logger::giveNodeManager(NodeManager* node_manager) {
    m_node_manager = node_manager;
}

void Logger::logInfo(string message, bool sysLog) {
    if(m_node_manager != nullptr) {
        string msg = message;
        m_node_manager->m_handle->logwarn(msg.c_str());
    }

    if (sysLog) {
        std::cout << message << std::endl;
    }
}

void Logger::setConsoleLoggingLevel(Logger::LoggingLevel level) {
    m_console_logging_level = level;
}
