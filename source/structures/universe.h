#pragma once
#include <cstdint>
#include <vector>
#include "vector2d.h"
#include "bounding_box.h"


class Universe {
	public:
		std::uint32_t num_bodies = 0;
		std::uint32_t current_simulation_epoch = 0;
		std::vector<double> weights = std::vector<double>();
		std::vector < Vector2d<double >> forces = std::vector<Vector2d<double >>();
		std::vector < Vector2d<double >> velocities = std::vector<Vector2d<double >>();
		std::vector < Vector2d<double >> positions = std::vector<Vector2d<double >>();
	
		Universe() = default;

		BoundingBox get_bounding_box(){
			if (num_bodies == 0) {
				return BoundingBox(0, 0, 0, 0);
			}
		
			//Initializing at the first body
			double min_x = positions[0][0];
			double max_x = positions[0][0];;
			double min_y = positions[0][1];;
			double max_y = positions[0][1];;
			for (Vector2d<double> body : positions) {
				if (body[0] < min_x) min_x = body[0];
				if (body[0] > max_x) max_x = body[0];
				if (body[1] < min_y) min_y = body[1];
				if (body[1] > max_y) max_y = body[1];

			}
			return BoundingBox(min_x, max_x, min_x, max_y);
	
	}

};