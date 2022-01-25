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
	camera(double vfov, double aspect_ratio, const point3 look_from, const point3 look_at, vec3 up)
	{
		auto focal_length = 1.0;
		auto theta = degrees_to_radians(vfov);
		auto half_h = tan(theta / 2) * focal_length;
		auto viewport_height = 2.0 * half_h;
		auto viewport_width = viewport_height * aspect_ratio;

		auto cam_front = unit_vector(look_from - look_at);
		auto cam_right = unit_vector(cross(up, cam_front));
		auto cam_up = unit_vector(cross(cam_front, cam_right));

		origin = look_from;
		vertical = viewport_height * cam_up;
		horizontal = viewport_width * cam_right;
		lower_left_corner = origin - vertical / 2.0 - horizontal / 2.0 - cam_front * focal_length;
	}

	ray get_ray(double u, double v)
	{
		return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
	}
};

#endif // !CAMERA_H
