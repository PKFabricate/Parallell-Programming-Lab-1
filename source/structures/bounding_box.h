#pragma once

#include <string>
#include "vector2d.h"


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
			if (index == 0) {
				return BoundingBox(x_min, x_max / 2, y_min, y_max / 2);
			}
			else if (index == 1) {
				return BoundingBox(x_max / 2, x_max, y_min, y_max / 2);
			}
			else if (index == 2) {
				return BoundingBox(x_min, x_max / 2, y_max / 2, y_max);
			}
			else if (index == 3) {
				return BoundingBox(x_max / 2, x_max, y_max / 2, y_max);
			}
			else throw std::exception("index out of bounds");



		}
};