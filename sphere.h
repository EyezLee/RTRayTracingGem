#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable
{
	public:
		point3 center;
		double radius;
		shared_ptr<material> mat_ptr;

	public:
		sphere() {}
		sphere(point3 cen, double r, shared_ptr<material> mat) : center(cen), radius(r), mat_ptr(mat) {};

		// const override means the inheritated function won't change any member variables
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	double a = r.direction().length_squared(); // dot product of the vector and itself: a * a * cos(0) = a^2
	double half_b = dot(r.direction(), oc);
	double c = oc.length_squared() - radius * radius;

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
	vec3 outward_normal = (rec.p - center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;

	return true;
}

#endif // !SPHERE_H
