#pragma once

template <typename T>
static Vector2d<T> calculate_acceleration(const Vector2d<T> force, const T mass) {
    if (mass == 0) {
        throw std::invalid_argument("Mass cant be Zero");
    }
    else {
        return force/mass;
    }
}


template <typename T>
static Vector2d<T> calculate_velocity(const Vector2d<T> velocity0, const Vector2d<T> acceleration, const T time) {
    return velocity0+(acceleration*time);
}