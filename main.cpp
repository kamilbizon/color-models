#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "RGBCircle.h"
#include "CMYCircle.h"
#include "Bar.h"

int main()
{
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	unsigned int FPS = 0, frame_counter = 0;

	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);

	ColorCircle* rgb = new RGBCircle;
	ColorCircle* cmy = new CMYCircle;
	Bar* bar = new Bar();

	bool is_left_mouse_button_clicked = false;

	int x_mouse = 0;
	int y_mouse = 0;

	//inicjalizacja 
	clock.restart().asMilliseconds();
	while (window.isOpen())
	{
		sf::Event event;
		window.clear(sf::Color::White);

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.mouseButton.button == sf::Mouse::Left)
					is_left_mouse_button_clicked = true;

			if (event.type == sf::Event::MouseMoved)
				if (is_left_mouse_button_clicked)
				{
					if (bar->is_inside_bar(event.mouseMove.x, event.mouseMove.y))
						bar->set_marker_position(event.mouseMove.y);
				}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (is_left_mouse_button_clicked)
				{
					is_left_mouse_button_clicked = false;

					if (bar->is_inside_bar(event.mouseButton.x, event.mouseButton.y))
						bar->set_marker_position(event.mouseButton.y);
				}
			}
		}
		//tu wyrysowaæ wszystko na ekran
		rgb->fill_texture(bar->get_marker_position());
		cmy->fill_texture(bar->get_marker_position());

		window.draw(*rgb);
		window.draw(*cmy);
		window.draw(*bar);

		//tu wypisaæ na ekran wartoœæ FPS
		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			FPS = (unsigned int)((float)frame_counter / clock.getElapsedTime().asSeconds());
			clock.restart();
			frame_counter = 0;
		}
		frame_counter++;

		window.display();
	}

	delete rgb;
	delete cmy;
	delete bar;

	return 0;
}