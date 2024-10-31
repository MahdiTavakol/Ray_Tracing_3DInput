#ifndef HITTABLE_LIST_PARALLEL
#define HITTABLE_LIST_PARALLEL

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

class hittable_list_parallel : public hittable_list
{
	bool hit(const ray& r, interval ray_t, hit_record& rec) const override
	{
		hit_record temp_rec;
		hit_record_struct temp_rec_struct;
		int rank;
		int size;
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &size);
		int hit_anything = 0;
		int hit_anything_all = 0;
		auto closest_so_far = ray_t.max;

		for (const auto& object : objects)
		{
			if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
			{
				hit_anything = rank;
				closest_so_far = temp_rec.t;
				// fill the temp_rec_struct with temp_rec and then broadcast it.
				// Then after the broadcast I would know which proc has hit and then 
				// put its material into the rec.
				hit_anything = rank;
				temp_rec_struct = hit_record_to_struct(temp_rec);
			}
		}
		MPI_Allreduce(&hit_anything, &hit_anything_all, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
	
		if (hit_anything_all > size)
			std::cerr << "A ray hits objects in two different MPI ranks " << std::endl;
		int count = sizeof(hit_record_struct) / sizeof(double);
		MPI_Bcast(&temp_rec_struct, count, MPI_DOUBLE, hit_anything_all, MPI_COMM_WORLD);


		return hit_anything;
	}
};
#endif
