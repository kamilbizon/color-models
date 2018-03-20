#include "Bar.h"
#include <iostream>


Bar::Bar()
{
	_bar_texture = new sf::Texture();
	_bar_texture->create(_x_bar_size, _y_bar_size);

	_bar = new sf::RectangleShape(sf::Vector2f((float)_x_bar_size, (float)_y_bar_size));
	_bar->setPosition(_x_bar_position, _y_bar_position);
	_bar->setTexture(_bar_texture);

	_bar_pixels = new sf::Uint8[_x_bar_size * _y_bar_size * 4];
	fill_bar_texture();

	_marker_position = 130;

}


Bar::~Bar()
{
}

void Bar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(*_bar);
}

unsigned char Bar::get_marker_position()
{
	return _marker_position;
}

void Bar::set_marker_position(const int y)
{
	_marker_position = y - _y_bar_position;
	std::cout << (unsigned int)_marker_position << std::endl;
}

bool Bar::is_inside_bar(const int x, const int y)
{
	if (x > _x_bar_position && x < _x_bar_position + _x_bar_size)
		if (y >= _y_bar_position && y < _y_bar_position + _y_bar_size)
			return true;

	return false;
}

void Bar::fill_bar_texture()
{
	for (int y = 1; y < _y_bar_size; y++)
	{
		// draw right and left borders
		draw_to_color_pixels(0, y, 0, 0, 0, 255);
		draw_to_color_pixels(_x_bar_size - 1, y, 0, 0, 0, 255);

		// draw left white zone
		for (int x = 1; x < 4; x++)
			draw_to_color_pixels(x, y, 0, 0, 0, 0);
	}

	// upper border
	for (int x = 0; x < _x_bar_size; x++)
		draw_to_color_pixels(x, 0, 0, 0, 0, 255);

	// draw main colors of bar from black to white
	for (int x = 4; x < _x_bar_size - 1; x++)
		for (int y = 1; y < _y_bar_size; y++)
			draw_to_color_pixels(x, y, y, y, y, 255);

	_bar_texture->update(_bar_pixels);
}

inline void Bar::draw_to_color_pixels(unsigned int x, unsigned int y,
	unsigned char r, unsigned char g, unsigned char b, unsigned char alfa)
{
	_bar_pixels[4 * (y * _x_bar_size + x) + 0] = r;
	_bar_pixels[4 * (y * _x_bar_size + x) + 1] = g;
	_bar_pixels[4 * (y * _x_bar_size + x) + 2] = b,
	_bar_pixels[4 * (y * _x_bar_size + x) + 3] = alfa;
}

