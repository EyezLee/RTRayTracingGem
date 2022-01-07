#ifndef RTRAYTRACING_H
#define RTRAYTRACING_H

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// CONSTANTS
const double MAX_DOUBLE = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

// utility functions
inline double degrees_to_radians(double degrees)
{
	return degrees * PI / 180.0;
}

inline double random_double()
{
	// return random number in [0. 1)
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	// return random number between [min, max)
	return min + (max - min) * random_double();
}

// common headers
#include "ray.h"
#include "vec3.h"
#include "color.h"

#endif
