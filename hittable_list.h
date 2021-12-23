#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : hittable
{
	public:
		std::vector<shared_ptr<hittable>> objects;

	public:
		hittable_list() {}
		hittable_list(shared_ptr<hittable> object) { add(object); }

		void add(shared_ptr<hittable> object) { objects.push_back(object); }
		void clear() { objects.clear(); }

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	bool hit_anything = false;
	double closest_so_far = t_max;
	hit_record temp_rec;

	for (const auto& object : objects)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

#endif // !HITTABLE_LIST_H
