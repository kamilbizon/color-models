#include "RGBCircle.h"



RGBCircle::RGBCircle(): ColorCircle()
{
	fill_texture(0);
	_color_circle->setPosition(400, 350);
}


RGBCircle::~RGBCircle()
{}

void RGBCircle::fill_texture(unsigned char blue)
{
	for (int x = 0; x<256; ++x)
		for (int y = 0; y < 256; ++y)
		{
			this->blue = blue;

			//transformate SFML coordinates to Cartesian
			float x_cartesian = x - _centre_coordinates;
			float y_cartesian = _centre_coordinates - y;
			float distance_from_centre = (float)sqrt(pow(x_cartesian, 2.0) + pow(y_cartesian, 2.0));

			if (distance_from_centre >= _radius) // if (x, y) not in circle
				draw_to_color_pixels(x, y, 0, 0, 0, 0);
			else
			{
				float cos = x_cartesian / distance_from_centre;
				float angle_radians = acos(cos);
				if (y > 128) // if angle is bigger than PI (acos return <0, PI>)
					angle_radians = (float)(2.0 * M_PI) - angle_radians;

				float part_of_full_circle = angle_radians / (float)(2.0 * M_PI);
				float part_of_radius = distance_from_centre / _radius;

				unsigned char red = (unsigned char)(255 * part_of_radius);
				unsigned char green = (unsigned char)(255 * part_of_full_circle);

				draw_to_color_pixels(x, y, red, green, blue, 255);
			}
		}

	_color_texture->update(_colors_pixels);
}