#ifndef CAMERA_H
#define CAMERA_H

#include "rtraytracinggem.h"

class camera
{
private:
	vec3 horizontal;
	vec3 vertical;
	point3 origin;
	point3 lower_left_corner;

public:
	camera()
	{
		auto aspect_ratio = 16.0 / 9.0;
		auto viewport_height = 2.0;
		auto viewport_width = viewport_height * aspect_ratio;
		auto focal_length = 1.0;

		origin = point3(0, 0, 0);
		vertical = vec3(0, viewport_height, 0);
		horizontal = vec3(viewport_width, 0, 0);
		lower_left_corner = origin - vertical / 2.0 - horizontal / 2.0 - vec3(0, 0, focal_length);
	}

	ray get_ray(double u, double v)
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
};

#endif // !CAMERA_H
