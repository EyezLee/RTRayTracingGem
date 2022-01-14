#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtraytracinggem.h"

// forward declaration
struct hit_record;

class material
{
public:
	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scatter) const = 0;
};

class lambertian : material
{
public:
	color albedo;

public:
	lambertian(const color& color) : albedo(color) {}

	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scatter) const override
	{
		auto scatter_dir = rec.normal + random_on_unit_sphere();
		if (scatter_dir.near_zero())
			scatter_dir = rec.normal;

		scatter = ray(rec.p, scatter_dir);
		attenuation = albedo;

		return true;
	}
};

#endif // !MATERIAL_H
