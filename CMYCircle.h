#pragma once
#include "ColorCircle.h"


class CMYCircle :public ColorCircle
{
public:
	CMYCircle();
	~CMYCircle();

	virtual void fill_texture(unsigned char yellow);
};

