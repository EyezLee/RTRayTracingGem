#include "color.h"
#include "ray.h"
#include "vec3.h"

#include "sphere.h"
#include "hittable_list.h"
#include <iostream>

color ray_color(const ray& r, const hittable_list& world)
{
	hit_record rec;

	if (world.hit(r, 0, 100000, rec))
	{
		return 0.5 * (rec.normal + color(1));
		//return color(1, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	double t = 0.5 * (unit_direction.y() + 1.0);
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

	// world
	hittable_list world;
	world.add(make_shared<sphere>(point3(0.25, 0, -1), 0.5));
	world.add(make_shared <sphere>(point3(-0.25, 0.2, -0.85), 0.5));

	// PPM render 
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; i++)
		{

			auto u = double(i) / (image_width - 1.0);
			auto v = double(j) / (image_height - 1.0);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color color = ray_color(r, world);
			write_color(std::cout, color);
			//write_color(std::cout, color(1, 0, 0));
		}
	}

	std::cerr << "\nDone.\n";

	return 1;
}