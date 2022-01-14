#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtraytracinggem.h"

// forward declaration
struct hit_record;

class material
{
public:
	virtual bool scatter(const ray& ray_in, const hit_record& hit, color& attenuation, ray& scatter) const = 0;
};

class lambertian : material
{
public:
	color albedo;

public:
	lambertian(const color& color) : albedo(color) {}

	virtual bool scatter(const ray& ray_in, const hit_record& hit, color& attenuation, ray& scatter) const override
	{

	}
};

#endif // !MATERIAL_H
