#include "ColorCircle.h"


ColorCircle::ColorCircle()
{
	_color_texture = new sf::Texture;
	_color_circle = new sf::Sprite;
	_colors_pixels = new sf::Uint8[256 * 256 * 4];

	_color_texture->create(256, 256);
	_color_circle->setTexture(*_color_texture);
}

ColorCircle::~ColorCircle()
{
	delete _color_texture;
	delete _color_circle;
	delete _colors_pixels;
}

void ColorCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*_color_circle);
}

inline void ColorCircle::draw_to_color_pixels(unsigned int x, unsigned int y,
											  unsigned char r, unsigned char g, unsigned char b, unsigned char alfa)
{
	_colors_pixels[4 * (y * 256 + x) + 0] = r;
	_colors_pixels[4 * (y * 256 + x) + 1] = g;
	_colors_pixels[4 * (y * 256 + x) + 2] = b,
	_colors_pixels[4 * (y * 256 + x) + 3] = alfa;
}
