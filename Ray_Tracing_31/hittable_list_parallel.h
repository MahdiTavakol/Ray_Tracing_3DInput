#ifndef HITTABLE_LIST_PARALLEL_H
#define HITTABLE_LIST_PARALLEL_H

#include "hittable_list.h"
#include "mpi.h"

struct hit_record_struct
{
	point3 p;
	vec3 normal;
	double t;
	double u;
	double v;
	double w;
	bool front_face;
};

hit_record_struct hit_record_to_struct(const hit_record&);


class hittable_list_parallel : public hittable_list {
public:

	void add(shared_ptr<hittable> object)
	{
		std::cout << "Point 9" << std::endl;
		std::cout << "Adding the object in the hittable list parallel " << std::endl;
		objects.push_back(object);
		//bbox = aabb(bbox, object->bounding_box());
		std::cout << "Finished adding the object in the hittable list parallel " << std::endl;
	}


	bool hit(const ray& r, interval ray_t, hit_record& rec) const override;


protected:
	aabb bbox;
};

#endif
