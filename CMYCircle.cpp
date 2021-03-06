#include "CMYCircle.h"



CMYCircle::CMYCircle(): ColorCircle()
{
	fill_texture(0);
	_color_circle->setPosition(50, 350);
}


CMYCircle::~CMYCircle()
{
}

void CMYCircle::fill_texture(unsigned char yellow)
{
	parameter = 100.0f * ((float)yellow / 255.0f);

	for (int x = 0; x<256; ++x)
		for (int y = 0; y < 256; ++y)
		{
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

				float cyan = part_of_radius;
				float magenta = part_of_full_circle;
				float yellow_normalized = (float)((float)yellow / 255.0); // <0, 1>

				// convert cmy to rgb
				unsigned char red = (unsigned char)((1 - cyan) * 255);
				unsigned char green = (unsigned char)((1 - magenta) * 255);
				unsigned char blue = (unsigned char)((1 - yellow_normalized) * 255);

				draw_to_color_pixels(x, y, red, green, blue, 255);
			}
		}

	_color_texture->update(_colors_pixels);
}
