#pragma once
#include "ColorCircle.h"
class HSLCircle :public ColorCircle
{
public:
	HSLCircle();
	~HSLCircle();

	virtual void fill_texture(unsigned char lightness);
};

