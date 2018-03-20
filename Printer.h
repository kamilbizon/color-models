#pragma once
#include <SFML/Graphics.hpp>
#include <string>


class Printer
{
public:
	Printer();
	~Printer();

	void print(sf::RenderTarget& target, std::string tex_to_print, int x_position, int y_position);

private:
	sf::Font font;
	sf::Text text;
};

