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
    //Iterating through each body in the universe represented by their index in the variable "body"
    for (std::uint32_t body = 0; body < universe.num_bodies; body++) {
        double x_force = 0;
        double y_force = 0;
        double body_mass = universe.weights[body];
        Vector2d body_pos = universe.positions[body];
        for (std::uint32_t other = 0; other < universe.num_bodies; other++) {
            //prevents body for calculating gravity to itself. The given formula specifies a sum of every force but x to itself.
            if (body != other) {
                //Forces are only based on cardinals
                x_force += gravitational_force(body_mass, universe.weights[other], abs(body_pos[0] - universe.positions[other][0]));
                y_force += gravitational_force(body_mass, universe.weights[other], abs(body_pos[1] - universe.positions[other][1]));
            }
        }
        universe.forces[body] = Vector2d(x_force, y_force);

    }



};

