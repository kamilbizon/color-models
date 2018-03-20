#pragma once

#include <string>
#include<SFML/Graphics.hpp>
#define M_PI 3.141592


class ColorCircle: public sf::Drawable
{
public:
	ColorCircle();
	~ColorCircle();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void fill_texture(unsigned char bar_marker) = 0;

	virtual float get_parameter() const { return parameter; }

protected:
	sf::Texture* _color_texture;
	sf::Sprite* _color_circle;
	sf::Uint8 *_colors_pixels;

	const float _centre_coordinates = 128;
	const float _radius = 128;

	float parameter;

	inline virtual void draw_to_color_pixels(unsigned int x, unsigned int y,
									 unsigned char r, unsigned char g, unsigned char b, unsigned char alfa);
};
