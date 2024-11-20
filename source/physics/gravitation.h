#pragma once

#include <cmath>

static double  gravitational_constant = 6.67430e-11;

static double gravitational_force(const double mass1, const double mass2, const double distance) {
    if (distance == 0) {
        throw std::invalid_argument("Distance cant be Zero");
    }
    else {
        return gravitational_constant * ((mass1 * mass2) / pow(distance, 2));
    }
}