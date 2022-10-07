#include "lib-rr/util/PID.h"

//
// Created by Jonathan T. Phung on 3/4/2021.
//

PID::PID(float kP, float kI, float kD, float feed_forward) {
    m_kP = kP;
    m_kI = kI;
    m_kD = kD;
    m_feed_forward = feed_forward;
    m_previous_error = 0;
    m_total_error = 0;
}

float PID::calculate(float current_error) {
    // Calculate change in time
    float delta_time = m_timer.Get();

    // Proportional (current_error)

    // Integral
    m_total_error += (current_error * delta_time);

    // Derivative (make sure it doesn't break when dt = 0)
    const float delta_error = delta_time == 0 ? 
        0 : ((current_error - m_previous_error) / delta_time);

    // Update previous error
    m_previous_error = current_error;

    // Compute the total input
    float total_input = (m_kP * current_error) + (m_kI * m_total_error) + (m_kD * delta_error);

    // Restart the timer so it can be used next loop
    m_timer.Start();

    // Return the total input plus a feed forward value, with a limit
    return std::copysign(std::min(fabs(total_input) + m_feed_forward, 1.0f), total_input);
}
