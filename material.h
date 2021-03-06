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
	metal(const color& color, double f) : albedo(color), fuzz(f > 1 ? 1 : f) {}

	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz + random_in_unit_sphere());
		attenuation = albedo;
		return(dot(reflected, rec.normal) > 0);
	}

};

class dielectric : public material
{
public:
	double ir; // index of refraction

private:
	static double fresnel_reflectance(double cos_theta, double ref_idx)
	{
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 *= r0;
		return r0 + pow(1 - cos_theta, 5);
	}

public:
	dielectric(const double index_of_refraction) : ir(index_of_refraction) {}

	virtual bool scatter(const ray& ray_in, const hit_record& rec, color& attenuation, ray& scattered) const override
	{
		attenuation = color(1);

		auto refraction_ratio = rec.front_face ? (1 / ir) : ir;

		auto unit_ray_in_dir = unit_vector(ray_in.direction());
		auto cos_theta = fmin(dot(-unit_ray_in_dir, rec.normal), 1.0);
		auto sin_theta = sqrt(1 - cos_theta * cos_theta);

		// Snell's law of refraction: sin_theta_prime / eta_prime = sin_theta / eta
		// if sin_theta_prime > 1, means refraction is invalid, thus reflect
		bool cannot_refract = refraction_ratio * sin_theta > 1; 
		
		vec3 scatter_dir;

		if (cannot_refract)
		{
			// reflect
			scatter_dir = reflect(unit_ray_in_dir, rec.normal);
		}
		else
		{
			// refract
			scatter_dir = refract(unit_ray_in_dir, rec.normal, refraction_ratio);
		}

		scattered = ray(rec.p, scatter_dir);

		return true;
	}
};

