#include "Printer.h"
#include "font.h"


Printer::Printer()
{
	font.loadFromMemory(font_data, font_data_size);
	text.setFont(font);
	text.setCharacterSize(15);
	text.setFillColor(sf::Color::Black);
}


Printer::~Printer()
{
}

void Printer::print(sf::RenderTarget& target, std::string text_to_print, int x_position, int y_position)
{
	text.setString(text_to_print);
	text.setPosition((float)x_position, (float)y_position);
	target.draw(text);
}
