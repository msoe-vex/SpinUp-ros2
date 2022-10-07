#pragma once

#include "api.h"

/**
 * Contains a configuration for encoders, using measurements in 
 * ticks and meters
 */
struct EncoderConfig {
    double initial_ticks;
    double ticks_per_wheel_revolution;
    double wheel_diameter;
};