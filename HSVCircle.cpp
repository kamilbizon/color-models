#include "HSVCircle.h"
#include <iostream>



HSVCircle::HSVCircle()
{
	fill_texture(0);
	_color_circle->setPosition(400, 50);
}


HSVCircle::~HSVCircle()
{
}

void HSVCircle::fill_texture(unsigned char value)
{
	parameter = (float)value / 255.0f;

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
				float value_normalized = (float)((float)value / 255.0); // <0, 1>

				// convert hsv to rgb
				unsigned char red, green, blue;

				if (saturation == 0)
				{
					red = (unsigned char)(value_normalized * 255.0);
					green = (unsigned char)(value_normalized * 255.0);
					blue = (unsigned char)(value_normalized * 255.0);
				}
				else
				{
					float tmp_hue = hue * 6.0f;
					if (tmp_hue >= 5.999999)
						tmp_hue = 0;     //hue must be < 1

					int int_hue = (int)(tmp_hue);
					float tmp1 = value_normalized * (1.0f - saturation);
					float tmp2 = value_normalized * (1.0f - saturation * (tmp_hue - (float)int_hue));
					float tmp3 = value_normalized * (1.0f - saturation * (1.0f - (tmp_hue - (float)int_hue)));

					float tmp_red, tmp_green, tmp_blue;

					if (int_hue == 0) 
					{ 
						tmp_red = value_normalized; 
						tmp_green = tmp3; 
						tmp_blue = tmp1;
					}
					else if (int_hue == 1) 
					{ 
						tmp_red = tmp2;
						tmp_green = value_normalized;
						tmp_blue = tmp1;
					}
					else if (int_hue == 2)
					{
						tmp_red = tmp1; 
						tmp_green = value_normalized; 
						tmp_blue = tmp3;
					}
					else if (int_hue == 3) 
					{ 
						tmp_red = tmp1; 
						tmp_green = tmp2; 
						tmp_blue = value_normalized;
					}
					else if (int_hue == 4) 
					{ 
						tmp_red = tmp3; 
						tmp_green = tmp1; 
						tmp_blue = value_normalized;
					}
					else 
					{ 
						tmp_red = value_normalized; 
						tmp_green = tmp1;
						tmp_blue = tmp2;
					}

					red = (unsigned char)(tmp_red * 255.0);
					green = (unsigned char)(tmp_green * 255.0);
					blue = (unsigned char)(tmp_blue * 255.0);
				}

				draw_to_color_pixels(x, y, red, green, blue, 255);
			}
		}

	_color_texture->update(_colors_pixels);
}
