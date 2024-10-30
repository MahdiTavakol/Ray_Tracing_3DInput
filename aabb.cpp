#include "aabb.h"

aabb::aabb(const interval& _x, const interval& _y, const interval& _z) 
	:x(_x), y(_y), z(_z)
{
	pad_to_minimums();
}

aabb::aabb(const point3& a, const point3& b)
{
	x = interval(std::fmin(a[0], b[0]), std::fmax(a[0], b[0]));
	y = interval(std::fmin(a[1], b[1]), std::fmax(a[1], b[1]));
	z = interval(std::fmin(a[2], b[2]), std::fmax(a[2], b[2]));

	pad_to_minimums();
}

aabb::aabb(const aabb& box0, const aabb& box1)
{
	x = interval(box0.x, box1.x);
	y = interval(box0.y, box1.y);
	z = interval(box0.z, box1.z);
}

void aabb::pad_to_minimums()
{
	double delta = 0.0001;
	if (x.size() < delta) x = x.expand(delta);
	if (y.size() < delta) y = y.expand(delta);
	if (z.size() < delta) z = z.expand(delta);
}

const interval& aabb::axis_interval(int n) const {
	if (n == 1) return y;
	if (n == 2) return z;
	return x;
}

bool aabb::hit(const ray& r, interval ray_t) const
{
	const point3& ray_orig = r.origin();
	const vec3& ray_dir = r.direction();

	for (int axis = 0; axis < 3; axis++)
	{
		const interval& ax = axis_interval(axis);
		const double adinv = 1.0 / ray_dir[axis];

		auto t0 = (ax.min - ray_orig[axis]) * adinv;
		auto t1 = (ax.max - ray_orig[axis]) * adinv;

		if (t0 < t1)
		{
			if (t0 > ray_t.min) ray_t.min = t0;
			if (t1 < ray_t.max) ray_t.max = t1;
		}
		else
		{
			if (t1 > ray_t.min) ray_t.min = t1;
			if (t0 < ray_t.max) ray_t.max = t0;
		}

		if (ray_t.max <= ray_t.min)
			return false;
	}
	return true;
}

int aabb::longest_axis() const
{
	if (x.size() > y.size())
		return x.size() > z.size() ? 0 : 2;
	else
		return y.size() > z.size() ? 1 : 2;
}

const aabb aabb::empty = aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);

