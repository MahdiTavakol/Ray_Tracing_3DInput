#include "obj_model_reader_parallel.h"


obj_model_reader_parallel::obj_model_reader_parallel(std::string _obj_file_name, hittable_list* _world, parallel* _para) :
	world(_world), para(_para)
{
	obj_file_name = _obj_file_name;
	v_num = 0;
	vt_num = 0;
	vn_num = 0;
}

void obj_model_reader_parallel::reader()
{
	if (!para->return_rank()) {
		//std::cout << FLERR;
		std::cout << " Started reading the obj file " << std::endl;
	}
	read_obj_file();
	if (!para->return_rank()) {
		//std::cout << FLERR;
		std::cout << "Finished reading the obj file " << std::endl;
		std::cout << "Started reading the mtl file " << std::endl;
	}
	read_mtl_file();
	if (!para->return_rank()) {
		//std::cout << FLERR;
		std::cout << "Finished reading the mtl file " << std::endl;
		std::cout << "Started adding the items " << std::endl;
	}
	add_item();
}


void obj_model_reader_parallel::add_item()
{
	int counter = 0;


	int size_per_rank = face_indexes.size() / para->return_size() + 1;
	int ilo = para->return_rank() * size_per_rank;
	int ihi = ilo + size_per_rank;


	//for (auto face : face_indexes)
	for (int i = ilo; i < ihi; i++)
	{
		auto face = face_indexes[i];
		counter++;
		//std::cout << "Adding the face " << counter << std::endl;
		shared_ptr<material> mat;
		int num_edges = face.num_edges;

		for (int j = 0; j < num_edges; j++)
		{
			if (j >= face.vt_indx.size()) std::cerr << "1-Out of bonds access from the rank " << para->return_rank() << std::endl;
			if (face.vt_indx[j] - 1 >= this->vs.size()) std::cerr << "2-Out of bonds access from the rank " << para->return_rank() << std::endl;
			if (face.vt_indx[j] - 1 >= this->vts.size()) std::cerr << "3-Out of bonds access from the rank " << para->return_rank() << std::endl;
			if (face.vt_indx[j] - 1 >= this->vns.size()) { 
				std::cout << "4-Out of bonds access from the rank " << para->return_rank() << std::endl;
				std::cout << face.vt_indx[j] << ">=" << this->vns.size() << std::endl;
				continue;
			}
			point3 v_j = this->vs[face.vt_indx[j] - 1]; // 1 based indexing in the obj file
			point3 vt_j = this->vts[face.vt_indx[j] - 1];
			point3 vn_j = this->vns[face.vt_indx[j] - 1];
			vs.push_back(v_j);
			vts.push_back(vt_j);
			vns.push_back(vn_j);
		}

		mat = materials[face.mat_indx];

		switch (num_edges)
		{
		case 3:
			world->add(make_shared<triangle_mesh>(vs, vts, vns, mat));
			break;
		case 4:
			world->add(make_shared<mesh>(vs, vts, vns, mat));
			break;
		}
	}

}



