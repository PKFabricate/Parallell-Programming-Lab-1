#pragma once

#include <string>
#include "vector2d.h"
#include "structures/bounding_box.h"
#include <math.h>
#include <stdexcept>


class BoundingBox{
	public: 
		double x_min; 
		double x_max; 
		double y_min; 
		double y_max;

		BoundingBox(double new_x_min, double new_x_max, double new_y_min, double new_y_max) :
			x_min{ new_x_min },
			x_max{ new_x_max },
			y_min{ new_y_min },
			y_max{ new_y_max } {};
		BoundingBox() = default;

		bool contains(Vector2d<double> obj) {
			return (x_min <= obj[0] && x_max >= obj[0] && y_min <= obj[1] && y_max >= obj[1]);

		}
		BoundingBox get_quadrant(std::uint8_t index) {
			double x_half = (x_max - x_min)/2 + x_min;
			double y_half = (y_max - y_min) / 2 + y_min;
			if (index == 0) {
				return BoundingBox(x_min, x_half, y_half, y_max);
			}
			else if (index == 1) {
				return BoundingBox(x_half, x_max, y_half, y_max);
			}
			else if (index == 2) {
				return BoundingBox(x_min, x_half, y_min, y_half);
			}
			else if (index == 3) {
				return BoundingBox(x_half, x_max, y_min, y_half);
			}
			else throw std::exception("index out of bounds");



		}
		//Implementation in bounding_box.cpp
		std::string get_string();

		double get_diagonal();

		void plotting_sanity_check();

		BoundingBox get_scaled(std::uint32_t scaling_factor);
};