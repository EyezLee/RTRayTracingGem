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
	vec3 cam_front, cam_up, cam_right;
	vec3 lens_radius;

public:
	camera(
		const point3 look_from, 
		const point3 look_at, 
		const vec3 up,
		double vfov,
		double aspect_ratio,
		double aperture,
		double focus_distance)
	{
		auto focal_length = 1.0;
		auto theta = degrees_to_radians(vfov);
		auto half_h = tan(theta / 2.0) * focal_length;
		auto viewport_height = 2.0 * half_h;
		auto viewport_width = viewport_height * aspect_ratio;

		cam_front = unit_vector(look_from - look_at);
		cam_right = unit_vector(cross(up, cam_front));
		cam_up = unit_vector(cross(cam_front, cam_right));

		origin = look_from;
		vertical = viewport_height * cam_up * focus_distance;
		horizontal = viewport_width * cam_right * focus_distance;
		lower_left_corner = origin - vertical / 2.0 - horizontal / 2.0 - cam_front * focal_length * focus_distance;

		lens_radius = aperture / 2.0;
	}

	ray get_ray(double u, double v)
	{
		auto rd = lens_radius * random_in_unit_disk();
		auto offset = cam_right * rd.x() + cam_up * rd.y();
		auto ray_origin = origin + offset;
		return ray(ray_origin, lower_left_corner + u * horizontal + v * vertical - ray_origin);
	}
};

#endif // !CAMERA_H
