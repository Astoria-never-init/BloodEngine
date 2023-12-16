#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glm/glm.hpp>

#define USE_CAMERA_CLASSES

#ifdef USE_CAMERA_CLASSES
#include "viewport/input/input.h"
#endif


class SF_Virtual_camera
{
public:
	
	SF_Virtual_camera(float _fow, float _near_plane, float _far_plane) : fow(_fow), near_plane( _near_plane), far_plane( _far_plane) {}
	SF_Virtual_camera() {}

	virtual void update_resolution(unsigned short _x, unsigned short _y);
	virtual void add_rotation_vector(glm::vec3 vec);
	virtual void add_rotation_yaw(float angle_in_degree);
	virtual void add_rotation_yaw_pitch(float angle_in_degree);
	virtual void add_location_world(glm::vec3 vec);
	virtual void add_location_relaitive(glm::vec3 vec);
	virtual glm::mat4 calculate_matrix(float deltasecond);

protected:
	virtual void upgrade(float deltasecond) {}

	glm::vec3 position = glm::vec3(0);
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float fow, near_plane, far_plane, screen_aspect = 1.0f;
};

class SF_Viewport_camera : public SF_Virtual_camera
{
public:
	SF_Viewport_camera(SF_Input* _input_class, float _fow, float _near_plane, float _far_plane) : SF_Virtual_camera(_fow, _near_plane, _far_plane), input_class(_input_class) {}
	SF_Viewport_camera(SF_Input* _input_class) : input_class(_input_class) {}
	SF_Viewport_camera() {}

	void upgrade(float deltasecond);
private:

	SF_Input * input_class = 0x0;

};


#endif