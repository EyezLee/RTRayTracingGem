#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

double hit_sphere(const point3& center, double radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(r.direction(), oc);
	auto c = dot(oc, oc) - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant < 0) return -1;
	else return (-half_b - sqrt(discriminant)) / a;
}

color ray_color(const ray& r)
{
	point3 center = vec3(0, 0, -0.85);
	auto t = hit_sphere(center, 0.5, r);
	if (t > 0.0)
	{
		vec3 N = unit_vector(r.at(t) - center);
		return 0.5 * (color(N.x() + 1, N.y() + 1, N.z() + 1));
	}

	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	// image config
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);

	// camera
	auto viewport_height = 3.0;
	auto viewport_width = viewport_height * aspect_ratio;
	auto focal_length = 1;

	auto origin = point3(0);
	auto horizontal = vec3(viewport_width, 0, 0);
	auto vertical = vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// PPM render 
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; i++)
		{
			auto u = double(i) / (image_width - 1);
			auto v = double(j) / (image_height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color sky_color = ray_color(r);
			write_color(std::cout, sky_color);
			//write_color(std::cout, color(1, 0, 0));
		}
	}

	std::cerr << "\nDone.\n";

	return 1;
}