#ifndef SF_BASE_CAMERA_CLASS_H
#define SF_BASE_CAMERA_CLASS_H

#include <glm/glm.hpp>



class SF_Virtual_camera
{
public:
	
	SF_Virtual_camera(float _fow, float _near_plane, float _far_plane) : fow(_fow), near_plane( _near_plane), far_plane( _far_plane) {}
	SF_Virtual_camera() {}

	virtual void update_resolution(unsigned short _x, unsigned short _y);
	virtual void add_rotation_vector(glm::vec3 vec);
	virtual void add_rotation_yaw(float angle_in_degree);
	virtual void add_rotation_pitch(float angle_in_degree);
	virtual void add_location_world(glm::vec3 vec);
	virtual void add_location_relaitive(glm::vec3 vec);
	virtual glm::mat4 calculate_matrix(float deltasecond);
	void set_camera_location(glm::vec3 _camera_position);

protected:
	virtual void upgrade(float deltasecond) {}

	glm::vec3 position = glm::vec3(0);
	glm::vec3 orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float fow, near_plane, far_plane, screen_aspect = 1.0f;
};

#endif