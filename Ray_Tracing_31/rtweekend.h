#ifndef RT_WEEKEND
#define RT_WEEKEND


#include <cmath>
#include <iostream>
#include <limits>
#include <memory>


enum { RANDOM_SPHERES, CHECKER_BOARDS, EARTH_SPHERE, 
	PERLIN_SPHERE, QUADS, SIMPLE_LIGHT, TWO_LIGHTS,
	CORNELL_BOX, TWO_BOXES, TWO_BOXES_ROTATED, CORNELL_SMOKE
};


using std::make_shared;
using std::shared_ptr;

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degree)
{
	return degree * pi / 180.0;
}

inline double random_double()
{
	return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

inline int random_int(int min, int max)
{
	return int(random_double(min, max + 1));
}







#endif