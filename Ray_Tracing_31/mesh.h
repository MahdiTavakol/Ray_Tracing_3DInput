#ifndef MESH_H
#define MESH_H

#include "hittable.h"
#include "hittable_list.h"
#include "quad.h"

class mesh : public hittable {
public:
	mesh(const std::vector<point3>& vs, const std::vector<point3>& vts, const std::vector<point3>& vns, shared_ptr<material> _mat);
	mesh() {}
	virtual void initialize();
	virtual void set_bounding_box();
	aabb bounding_box() const override { return bbox; }
	bool hit(const ray& _r, interval _ray_t, hit_record& _rec) const override;
	virtual bool is_interior(double _a, double _b, hit_record& _rec) const;

protected:
	std::vector<point3> vs;
	std::vector<point3> vts;
	std::vector<point3> vns;
	shared_ptr<material> mat;

	int num_edges;
	
	aabb bbox;
	vec3 unit_n1, unit_n2;
	vec3 w1, w2;
	point3 Q1, Q2;
	double D1, D2;

	static vec3 interpolate(const std::vector<point3>& _triangle, const std::vector<point3>& _normals, const vec3& _point);
};

inline shared_ptr<hittable_list> box(const point3& _a, const point3& _b, shared_ptr<material> _mat)
{

	shared_ptr<hittable_list> sides = make_shared<hittable_list>();

	point3 min = point3(std::fmin(_a.x(), _b.x()), std::fmin(_a.y(), _b.y()), std::fmin(_a.z(), _b.z()));
	point3 max = point3(std::fmax(_a.x(), _b.x()), std::fmax(_a.y(), _b.y()), std::fmax(_a.z(), _b.z()));

	vec3 dx = vec3(max.x() - min.x(), 0, 0);
	vec3 dy = vec3(0, max.y() - min.y(), 0);
	vec3 dz = vec3(0, 0, max.z() - min.z());

	sides->add(make_shared<quad>(point3(min.x(), min.y(), max.z()), dx, dy, _mat));
	sides->add(make_shared<quad>(point3(max.x(), min.y(), max.z()), -dz, dy, _mat));
	sides->add(make_shared<quad>(point3(max.x(), min.y(), min.z()), -dx, dy, _mat));
	sides->add(make_shared<quad>(point3(min.x(), min.y(), min.z()), dz, dy, _mat));
	sides->add(make_shared<quad>(point3(min.x(), max.y(), max.z()), dx, -dz, _mat));
	sides->add(make_shared<quad>(point3(min.x(), min.y(), min.z()), dx, dz, _mat));

	return sides;

}

#endif