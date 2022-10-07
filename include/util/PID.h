#pragma once

#include "lib-rr/util/Timer.h"
#include "lib-rr/util/Logger.h"

//
// Created by Jonathan T. Phung on 3/4/2021.
//

class PID {
private:
    float m_kP;
    float m_kI;
    float m_kD;
    float m_feed_forward;
    float m_previous_error;
    float m_total_error;
    Timer m_timer;

public:
    PID(float kP, float kI, float kD, float feed_forward=0.);

    /**
     * This function returns the percentage of input to give to a
     * mechanism, based off the supplied constants and feedforward
     * values
     * @param current_error Current error of the mechanism
     * @returns percentage of input to give to the mechanism
     */
    float calculate(float current_error);
};
