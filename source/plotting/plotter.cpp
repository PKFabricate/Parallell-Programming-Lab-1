#include "plotting/plotter.h"
#include "io/image_parser.h"

#include <exception>

void Plotter::write_and_clear() {
    // create plot serial number string
    std::string serial_number_string = std::to_string(image_serial_number);
    while (serial_number_string.length() < 9) {
        serial_number_string = "0" + serial_number_string;
    }

    std::string file_name = filename_prefix + "_" + serial_number_string + ".bmp";
    ImageParser::write_bitmap(output_folder_path / file_name, image);
    clear_image();
    image_serial_number += 1;
}

BitmapImage::BitmapPixel Plotter::get_pixel(std::uint32_t x, std::uint32_t y) {
    return image.get_pixel(y, x);
}

void Plotter::mark_pixel(std::uint32_t x, std::uint32_t y, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    if (x > plot_width || y > plot_height || x < 0 || y < 0) {
        throw std::invalid_argument("Pixel not in Image");
    }
    if (x > 0) { x = x - 1; }
    if (y > 0) { y = y - 1; }
    image.set_pixel(y, x, BitmapImage::BitmapPixel{ red, green, blue });
}

void Plotter::mark_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    if (plot_bounding_box.contains(position)) {
        double x_perc = (position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min);
        double y_perc = (position[1] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min);
        try
        {
            mark_pixel(plot_width * x_perc,plot_height * y_perc  , red, green, blue);
        }
        catch (std::exception){};
    }
}

void Plotter::add_bodies_to_image(Universe& universe) {
    for (const auto& position : universe.positions) {
        mark_position(position, 255, 255, 255);
    }
}

void Plotter::highlight_position(Vector2d<double> position, std::uint8_t red, std::uint8_t green, std::uint8_t blue) {
    if (plot_bounding_box.contains(position)) {
        for (int i = plot_bounding_box.x_min; i <= plot_bounding_box.x_max; i++) {
            double y_real = plot_height * (position[0] - plot_bounding_box.y_min) / (plot_bounding_box.y_max - plot_bounding_box.y_min);
            try
            {
                mark_pixel(i, y_real, red, green, blue);
            }
            catch (std::exception) {};
        }
        for (int i = plot_bounding_box.y_min; i <= plot_bounding_box.y_max; i++) {
            double x_real = plot_width * (position[0] - plot_bounding_box.x_min) / (plot_bounding_box.x_max - plot_bounding_box.x_min);
            try
            {
                mark_pixel(x_real, i, red, green, blue);
            }
            catch (std::exception) {};
        }
    }
}