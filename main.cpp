#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include "RGBCircle.h"
#include "CMYCircle.h"
#include "HSLCircle.h"
#include "HSVCircle.h"
#include "FPS.h"
#include "Printer.h"
#include "Bar.h"

int main()
{
	sf::Clock clock;
	sf::Time time = sf::Time::Zero;
	FPS fps;
	Printer printer;

	sf::RenderWindow window(sf::VideoMode(800, 650), "GFK Lab 01", sf::Style::Titlebar | sf::Style::Close);

	ColorCircle* rgb = new RGBCircle;
	ColorCircle* cmy = new CMYCircle;
	ColorCircle* hsl = new HSLCircle;
	ColorCircle* hsv = new HSVCircle;

	Bar* bar = new Bar();

	bool is_left_mouse_button_clicked = false;
	bool has_circles_changed = true;

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
					{
						bar->set_marker_position(event.mouseMove.y);
						has_circles_changed = true;
					}
				}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (is_left_mouse_button_clicked)
				{
					is_left_mouse_button_clicked = false;

					if (bar->is_inside_bar(event.mouseButton.x, event.mouseButton.y))
					{
						bar->set_marker_position(event.mouseButton.y);
						has_circles_changed = true;
					}
				}
			}
		}

		//tu wyrysowaæ wszystko na ekran
		if (has_circles_changed)
		{
			rgb->fill_texture(bar->get_marker_position());
			cmy->fill_texture(bar->get_marker_position());
			hsl->fill_texture(bar->get_marker_position());
			hsv->fill_texture(bar->get_marker_position());

			has_circles_changed = false;
		}

		window.draw(*rgb);
		printer.print(window, "RGB", 400, 350);
		window.draw(*cmy);
		printer.print(window, "CMY", 50, 350);
		window.draw(*hsl);
		printer.print(window, "HSL", 50, 50);
		window.draw(*hsv);
		printer.print(window, "HSV", 400, 50);
		window.draw(*bar);

		//tu wypisaæ na ekran wartoœæ FPS
		if (clock.getElapsedTime().asSeconds() >= 1.0f)
		{
			fps.set_FPS(clock.getElapsedTime().asSeconds());
			clock.restart();
			fps.set_zero_counter();

		}
		fps.increment_counter();
		printer.print(window, "FPS = " + std::to_string(fps.get_FPS()), 700, 350);

		window.display();
	}

	delete rgb;
	delete cmy;
	delete hsl;
	delete hsv;
	delete bar;

	return 0;
}