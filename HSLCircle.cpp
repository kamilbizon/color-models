#include "HSLCircle.h"



HSLCircle::HSLCircle()
{
	fill_texture(0);
	_color_circle->setPosition(50, 50);
}


HSLCircle::~HSLCircle()
{
}

void HSLCircle::fill_texture(unsigned char lightness)
{
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

				float saturation = part_of_radius;
				float hue = part_of_full_circle;
				float lightness_normalized = (float)((float)lightness / 255.0); // <0, 1>

				// convert hsl to rgb
				unsigned char red, green, blue;
				
				if (saturation <= 1e-10)
				{
					red = (unsigned char)(lightness_normalized * 255.0);
					green = (unsigned char)(lightness_normalized * 255.0);
					blue = (unsigned char)(lightness_normalized * 255.0);
				}
				else
				{
					float tmp1, tmp2;

					if (lightness_normalized < 0.5)
						tmp2 = lightness_normalized * (1.0 + saturation);
					else
						tmp2 = (lightness_normalized + saturation) - (saturation * lightness_normalized);

					tmp1 = 2.0 * lightness_normalized - tmp2;

					red = (unsigned char)(255.0 * hue_to_rgb(tmp1, tmp2, hue + (1.0 / 3.0)));
					green = (unsigned char)(255.0 * hue_to_rgb(tmp1, tmp2, hue));
					blue = (unsigned char)(255.0 * hue_to_rgb(tmp1, tmp2, hue - (1.0 / 3.0)));
				}

				draw_to_color_pixels(x, y, red, green, blue, 255);
			}
		}

	_color_texture->update(_colors_pixels);
}

float HSLCircle::hue_to_rgb(float tmp1, float tmp2, float tmp_hue)
{
	if (tmp_hue < 0)
		tmp_hue += 1.0;

	if (tmp_hue > 1.0)
		tmp_hue -= 1.0;

	if ((6.0 * tmp_hue) < 1.0)
		return (tmp1 + (tmp2 - tmp1) * 6 * tmp_hue);

	if ((2.0 * tmp_hue) < 1.0)
		return (tmp2);

	if ((3.0 * tmp_hue) < 2.0)
		return (tmp1 + (tmp2 - tmp1) * ((2.0 / 3.0) - tmp_hue) * 6.0);

	return (tmp1);
}