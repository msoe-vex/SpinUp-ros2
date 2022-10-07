#include <iostream>
#include "lib-rr/util/Timer.h"

using namespace std::chrono;

double Timer::Get() {
    if(m_started && !m_stopped) {
        return getTime() - m_startTime;
    } else if(m_started && m_stopped) {
        return m_stopTime - m_startTime;
    }
    Logger::logInfo("Error: Get called on timer which was not started");
    return 0;
}

void Timer::Reset() {
    m_started = false;
    m_startTime = getTime();
}

void Timer::Stop() {
    if(!m_started) {
        Logger::logInfo("Error: Timer stopped without starting");
    } else {
        m_stopped = true;
        m_stopTime = getTime();
    }
}

void Timer::Start() {
    m_started = true;
    m_startTime = getTime();
}

double Timer::getTime() {
  return pros::millis() / 1000.0;
}

bool Timer::isStarted() {
    return m_started;
}