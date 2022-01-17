#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtraytracinggem.h"

// forward declaration
struct hit_record;

class material {
    public:
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const = 0;
};


#endif // !MATERIAL_H



class lambertian : public material
{
public:
	color albedo;

public:
	lambertian(const color& c) : albedo(c) {}

	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		auto scatter_dir = rec.normal + random_on_unit_sphere();
		if (scatter_dir.near_zero())
			scatter_dir = rec.normal;

		scattered = ray(rec.p, scatter_dir);
		attenuation = albedo;

		return true;
	}
};


class metal : public material
{
public:
	color albedo;
	double fuzz;

public:
	metal(const color& color, double f) : albedo(color), fuzz(f) {}

	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected);
		attenuation = albedo;
		return(dot(reflected, rec.normal) > 0);
	}

};

