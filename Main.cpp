#include "rtraytracinggem.h"

#include "sphere.h"
#include "hittable_list.h"
#include <iostream>

color ray_color(const ray& r, const hittable_list& world, int depth)
{
	hit_record rec;

	if (depth <= 0) return color(0);

	if (world.hit(r, 0.001, MAX_DOUBLE, rec))
	{
		//return 0.5 * (rec.normal + color(1));
		//ray diffuse_ray = ray(rec.p, rec.normal + random_in_unit_sphere());
		//ray diffuse_ray = ray(rec.p, rec.normal + random_on_unit_sphere()); // more uniformly distributed than the first methods
		ray diffuse_ray = ray(rec.p, random_in_hemisphere(rec.normal)); // uniform distribution on p, without corresponding to normal 
		return 0.5 * ray_color(diffuse_ray, world, depth-1);
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
	const int samples_per_pixel = 100;
	const int ray_bounce_depth = 50;

	// camera
	camera cam;

	// world
	hittable_list world;
	//world.add(make_shared<sphere>(point3(0.25, 0, -1), 0.5));
	//world.add(make_shared <sphere>(point3(0, -100.5, -1), 100));

	// PPM render 
	std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	for (int j = image_height-1; j >= 0; j--)
	{
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

		for (int i = 0; i < image_width; i++)
		{

			color pixel_color = color(0);
			
			for (int s = 0; s < samples_per_pixel; s++)
			{
				auto u = (i + random_double()) / (image_width - 1.0);
				auto v = (j + random_double()) / (image_height - 1.0);
				pixel_color += ray_color(cam.get_ray(u, v), world, ray_bounce_depth);
			}
			write_color(std::cout, pixel_color, samples_per_pixel);
			//write_color(std::cout, color(1, 0, 0));
		}
	}

	std::cerr << "\nDone.\n";

	return 1;
}