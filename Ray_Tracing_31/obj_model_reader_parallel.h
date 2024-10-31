#ifndef OBJ_MODEL_READER_PARALLEL_H
#define OBJ_MODEL_READER_PARALLEL_H

#include <string>
#include <sstream>
#include <fstream>
#include <vector>

#include "color.h"
#include "material.h"
#include "hittable_list.h"
#include "hittable_list_parallel.h"
#include "vec3.h"
#include "triangle_mesh.h"
#include "obj_model_reader.h"
#include "mesh.h"
#include "mpi.h"

struct face_indx
{
	std::vector<int> v_indx;
	std::vector<int> vt_indx;
	std::vector<int> vn_indx;
	int num_edges;
	int mat_indx;
};

class obj_model_reader_parallel: public obj_model_reader 
{
public:
	obj_model_reader_parallel(std::string _obj_file_name, hittable_list_parallel* _world);
	void reader();

protected:
	hittable_list_parallel* world;

	void add_item() override;


private:
	int rank, size;
};


#endif
