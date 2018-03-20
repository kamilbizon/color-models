#pragma once
#include "ColorCircle.h"


class RGBCircle: public ColorCircle
{
public:
	RGBCircle();
	~RGBCircle();

	virtual void fill_texture(unsigned char blue);
};

