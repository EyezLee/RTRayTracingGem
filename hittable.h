#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtraytracinggem.h"

struct hit_record
{
	point3 p;
	double t;
	vec3 normal;
	shared_ptr<material> mat_ptr;
	
	// normal facing inward or outward
	bool front_face;
	
	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		// is back face when ray is in the same direction with outward normal (dot product > 0)
		if (dot(r.direction(), outward_normal) > 0.0)
		{
			front_face = false;
			normal = -outward_normal;
		}
		else
		{
			front_face = true;
			normal = outward_normal;
		}
	}
};

class hittable
{
	public:
		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif // !HITTABLE_H
