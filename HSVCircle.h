#pragma once
#include "ColorCircle.h"


class HSVCircle :public ColorCircle
{
public:
	HSVCircle();
	~HSVCircle();

	virtual void fill_texture(unsigned char value);
};

