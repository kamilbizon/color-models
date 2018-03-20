#pragma once
#include <SFML/Graphics.hpp>

class FPS
{
public:
	FPS();
	~FPS();

	unsigned int get_frame_counter() { return _frame_counter; }
	unsigned int get_FPS() { return _FPS; }

	void set_zero_counter() { _frame_counter = 0; }
	void increment_counter() { _frame_counter++; }

	void set_FPS(float time) { _FPS = (unsigned int)((float)_frame_counter / time); }

private:
	unsigned int _FPS, _frame_counter;
};

