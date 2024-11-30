#ifndef CAMERA_DERIVED_H
#define CAMERA_DERIVED_H

/* This class was defined since if we have the _in->setup_camera(*camera) 
   inside the camera class we would have circular dependency */

#include "camera.h"
#include "input.h"
#include "parallel.h"

class camera_derived : public camera
{
	friend class input;
	friend class parallel;

public:

    camera_derived(const input* _in)
	{
		_in->setup_camera(this);
	}

	void move_camera(point3 _lookfrom) override {
		std::cout << "Point -4" << std::endl;
		this->lookfrom = _lookfrom;
		std::cout << "Point -5" << std::endl;
	}

};

#endif