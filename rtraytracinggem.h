#ifndef RTRAYTRACING_H
#define RTRAYTRACING_H

#include <cmath>
#include <limits>
#include <memory>

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

// common headers
#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif
