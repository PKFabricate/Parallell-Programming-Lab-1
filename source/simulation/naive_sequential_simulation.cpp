#include "simulation/naive_sequential_simulation.h"
#include "simulation/constants.h"
#include "physics/gravitation.h"
#include "physics/mechanics.h"

#include <cmath>



void NaiveSequentialSimulation::simulate_epochs(Plotter& plotter, Universe& universe, std::uint32_t num_epochs, bool create_intermediate_plots, std::uint32_t plot_intermediate_epochs) {
    for (int i = 0; i < num_epochs; i++) { simulate_epoch(plotter, universe, create_intermediate_plots, plot_intermediate_epochs); }
};
void NaiveSequentialSimulation::simulate_epoch(Plotter& plotter, Universe& universe, bool create_intermediate_plots, std::uint32_t plot_intermediate_epochs) {
    calculate_forces(universe);
    calculate_velocities(universe);
    calculate_positions(universe);
    universe.current_simulation_epoch++;
    if (universe.current_simulation_epoch % plot_intermediate_epochs == 0 && create_intermediate_plots) {
        plotter.write_and_clear();
    }
};
void NaiveSequentialSimulation::calculate_forces(Universe& universe) {
    for (std::uint32_t body = 0; body < universe.num_bodies; body++) {
        double x_force = 0;
        double y_force = 0;
        double body_mass = universe.weights[body];
        Vector2d body_pos = universe.positions[body];
        for (std::uint32_t other = 0; other < universe.num_bodies; other++) {
            if (body != other) {
                double dx = body_pos[0] - universe.positions[other][0];
                double dy = body_pos[1] - universe.positions[other][1];

                double r = sqrt(dx * dx + dy * dy);

                double force_full = gravitational_force(body_mass, universe.weights[other], r);

                double force_x = force_full * dx / r;
                double force_y = force_full * dy / r;

                x_force += force_x;
                y_force += force_y;
            }
        }
        universe.forces[body] = Vector2d(-x_force, -y_force);

    }
};

void NaiveSequentialSimulation::calculate_velocities(Universe& universe) {
    for (std::uint32_t body = 0; body < universe.num_bodies; body++) {
        Vector2d<double> v0 = universe.velocities[body];
        Vector2d<double> force = universe.forces[body];
        double mass = universe.weights[body];
        universe.velocities[body] = calculate_velocity(v0, calculate_acceleration(force, mass), epoch_in_seconds);
    }
}

void NaiveSequentialSimulation::calculate_positions(Universe& universe) {
    for (std::uint32_t body = 0; body < universe.num_bodies; body++) {
        Vector2d<double> pos0 = universe.positions[body];
        Vector2d<double> movement = universe.velocities[body] * epoch_in_seconds;
        universe.positions[body] = pos0 + movement;
    }
}