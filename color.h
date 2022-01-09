#ifndef COLOR_H
#define COLOR_H

#include "rtraytracinggem.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color, int sample_per_pixel)
{
	// write rgb color from [0, 1] => [0, 255]
	// static_cast < new_type > ( expression )	
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	auto scale = 1.0 / sample_per_pixel;
	r = sqrt(r * scale);
	b = sqrt(b * scale);
	g = sqrt(g * scale);

	out << static_cast<int>(256 * clamp(r, 0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(g, 0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(b, 0, 0.999)) << '\n';
}

#endif