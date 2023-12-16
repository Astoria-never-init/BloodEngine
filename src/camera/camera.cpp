#include "camera.h"
#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <iostream>

using namespace std;

void SF_Virtual_camera::update_resolution(unsigned short _x, unsigned short _y)
{
	screen_aspect = (float)_x / _y;
}

void SF_Virtual_camera::add_rotation_vector(glm::vec3 vec)
{
	orientation = glm::normalize(orientation * glm::normalize(vec));
}

void SF_Virtual_camera::add_rotation_yaw(float angle_in_degree)
{
	glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(angle_in_degree), glm::normalize(glm::cross(orientation, up)));

	if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		orientation = newOrientation;
	}
}

void SF_Virtual_camera::add_rotation_yaw_pitch(float angle_in_degree)
{
}

void SF_Virtual_camera::add_location_world(glm::vec3 vec)
{
	position += vec;
}

void SF_Virtual_camera::add_location_relaitive(glm::vec3 vec)
{
}

glm::mat4 SF_Virtual_camera::calculate_matrix(float deltasecond)
{
	upgrade(deltasecond);

	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(fow), screen_aspect, near_plane, far_plane);

	return projection * view;
}

void SF_Viewport_camera::upgrade(float deltasecond)
{
	if (!input_class) 
	{
		return;
	}
	float speed = 0.2;//for delete

	float x, y;
	input_class->get_mouse_position(x, y);

	if (input_class->get_mouse_button(SF_Mouse_key::MOUSE_LEFT)) 
	{
		input_class->set_mouse_position(0.5, 0.5);
	}
	if (input_class->get_key_state(SF_Key::W)) 
	{
		add_location_world((speed) * orientation);
	}
	if (input_class->get_key_state(SF_Key::S))
	{
		add_location_world((-speed)*orientation);
	}
	if (input_class->get_key_state(SF_Key::D))
	{
		add_location_world((speed) * glm::normalize(glm::cross(orientation, up)));
	}
	if (input_class->get_key_state(SF_Key::A))
	{
		add_location_world((-speed)*glm::normalize(glm::cross(orientation, up)));
	}
}
