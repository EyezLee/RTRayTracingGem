#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3
{
	public:
		double e[3];

	public:
			vec3() : e{ 0, 0, 0 } {} // member initialization approach
			vec3(double e0, double e1, double e2) : e{ e0, e1, e2 } {}

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
};

// type alias
using point3 = vec3;
using color = vec3;

#endif