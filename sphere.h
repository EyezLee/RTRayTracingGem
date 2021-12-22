#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
	public:
		point3 center;
		double radius;

	public:
		sphere() {}
		sphere(point3 cen, double r) : center(cen), radius(r) {};

		// const override means the inheritated function won't change any member variables
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	float a = r.direction().length_squared(); // dot product of the vector and itself: a * a * cos(0) = a^2
	float half_b = dot(r.direction(), oc);
	float c = oc.length_squared() - radius * radius;

	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;

	auto sqrt_discriminant = sqrt(discriminant);
	auto t = (-half_b - sqrt_discriminant) / a;

	// find nearest t in accepatble range
	if (t < t_min || t > t_max)
	{
		t = (-half_b + sqrt_discriminant) / a;
		if (t < t_min || t > t_max)
			return false;
	}

	rec.t = t;
	rec.p = r.origin() + t * r.direction();
	rec.normal = (rec.p - center) / radius;

	return true;
}

#endif // !SPHERE_H
