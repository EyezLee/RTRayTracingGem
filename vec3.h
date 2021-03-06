#ifndef VEC3_H
#define VEC3_H

#include <iostream>

using std::sqrt;

class vec3
{
	public:
		double e[3];

	public:
		vec3() : e{ 0, 0, 0 } {} // member initialization approach
		vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}
		vec3(double e0) : e{ e0, e0, e0 } {}

		double x() const { return e[0]; } // const: be able to access member of a const instant
		double y() const { return e[1]; }
		double z() const { return e[2]; } 

		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); } // override operator
		double operator[](int i) const{return e[i]; }
		double& operator[](int i) { return e[i]; } // return a memory address

		vec3& operator+=(const vec3& v)
		{
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];

			// returns a copy of the current object allocated on stack
			// unless function return type is a reference
			return *this; // dereferenced pointer (this is the pointer)
		}

		vec3& operator*=(const double t)
		{
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}

		vec3& operator/=(const double t)
		{
			return *this *= 1 / t;
		}

		double length_squared() const
		{
			return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
		}

		double length() const
		{
			return sqrt(length_squared());
		}

		bool near_zero()
		{
			const auto s = 1e-8;
			return (fabs(e[0] < s) && fabs(e[1] < s) && fabs(e[2] < s));
		}
};

// type alias
using point3 = vec3;
using color = vec3;

// vec3 utility function
// inline: expand in line function. class memeber functions are implicit inline functions
inline std::ostream& operator<< (std::ostream &out, const vec3 &v)
{
	return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline vec3 operator-(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v)
{
	return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
	return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3& v, double t)
{
	return (1 / t) * v;
}

inline double dot(const vec3& u, const vec3& v)
{
	return u.e[0] * v.e[0]
		+ u.e[1] * v.e[1]
		+ u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v)
{
	return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
		u.e[2] * v.e[0] - u.e[0] * v.e[2],
		u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

inline vec3 random()
{
	return vec3(random_double(), random_double(), random_double());
}

inline vec3 random(double min, double max)
{
	return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

inline vec3 random_in_unit_disk()
{
	while (true)
	{
		vec3 p(random_double(-1, 1), random_double(-1, 1), 0);
		if (p.length_squared() >= 1) continue;

		return p;
	}
}

// diffuse - random distribution 
inline vec3 random_in_unit_sphere()
{
	// cube rejection method		
	while (true)
	{
		vec3 p = random(-1, 1);
		if (p.length_squared() >= 1) continue;

		return p;
	}
}

// diffuse - Lambertian distribution 
inline vec3 random_on_unit_sphere()
{
	return unit_vector(random_in_unit_sphere());
}

// diffuse - intuitive unit hemisphere distribution
inline vec3 random_in_hemisphere(const vec3& normal)
{
	vec3 vec_in_unit_sphere = random_in_unit_sphere();
	if (dot(vec_in_unit_sphere, normal) > 0) // same direction with normal
		return vec_in_unit_sphere;
	else return -vec_in_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3& v, const vec3& n, double refraction_ratio)
{
	auto cos_theta = fmin(dot(-v, n), 1.0);
	vec3 r_out_perpendicular = refraction_ratio * (v + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1 - r_out_perpendicular.length_squared())) * n;

	return r_out_perpendicular + r_out_parallel;
}

#endif
