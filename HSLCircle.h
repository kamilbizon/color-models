#pragma once
#include "ColorCircle.h"
class HSLCircle :public ColorCircle
{
public:
	HSLCircle();
	~HSLCircle();

	virtual void fill_texture(unsigned char lightness);

private:
	float hue_to_rgb(float tmp1, float tmp2, float tmp_hue);
};

