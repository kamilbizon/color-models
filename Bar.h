#pragma once

#include <SFML/Graphics.hpp>

class Bar: public sf::Drawable
{
public:
	Bar();
	~Bar();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int get_x_bar_position() const
	{
		return _x_bar_position;
	}
	int get_y_bar_position() const
	{
		return _y_bar_position;
	}
	int get_x_bar_size() const
	{
		return _x_bar_size;
	}
	int get_y_bar_size() const
	{
		return _y_bar_size;
	}

	unsigned char get_marker_position();
	void set_marker_position(const int y);

	bool is_inside_bar(const int x, const int y);
	

private:
	sf::RectangleShape *_bar;
	sf::Texture *_bar_texture;
	sf::Uint8 *_bar_pixels;

	unsigned char _marker_position;

	const int _x_bar_size = 40;
	const int _y_bar_size = 256;

	const int _x_bar_position = 700;
	const int _y_bar_position = 50;

	void fill_bar_texture();
	inline void draw_to_color_pixels(unsigned int x, unsigned int y,
		unsigned char r, unsigned char g, unsigned char b, unsigned char alfa);
};

