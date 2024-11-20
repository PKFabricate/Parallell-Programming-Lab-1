#pragma once
#include <filesystem>
#include <fstream>
#include <iomanip>

static void save_universe(const std::filesystem::path& save_universe_path, const Universe& universe) {

    std::ofstream universe_file(save_universe_path);
    if (!universe_file.is_open()) {
        throw std::invalid_argument("Could not save universe to given file!");
    }

    universe_file << std::fixed << std::setprecision(6);

    universe_file << "### Bodies\n";
    universe_file << universe.num_bodies << "\n";

    universe_file << "### Positions\n";
    for (const auto& position : universe.positions) {
        universe_file << position[0] << " " << position[1] << "\n";
    }

    universe_file << "### Weights\n";
    for (const auto& weight : universe.weights) {
        universe_file << weight << "\n";
    }

    universe_file << "### Velocities\n";
    for (const auto& velocity : universe.velocities) {
        universe_file << velocity[0] << " " << velocity[1] << "\n";
    }

    universe_file << "### Forces\n";
    for (const auto& force : universe.forces) {
        universe_file << force[0] << " " << force[1] << "\n";
    }

}
