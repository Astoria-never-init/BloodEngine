#include "camera.h"
#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <iostream>
#include <logger.h>

using namespace std;

void SF_Virtual_camera::update_resolution(unsigned short _x, unsigned short _y)
{
	screen_aspect = (float)_x / _y;
}

void SF_Virtual_camera::add_rotation_vector(glm::vec3 vec)
{
	//orientation = glm::normalize(orientation * glm::normalize(vec));
}

void SF_Virtual_camera::add_rotation_yaw(float angle_in_degree)
{
	glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-angle_in_degree), glm::normalize(glm::cross(orientation, up)));

	if (abs(glm::angle(newOrientation, up) - glm::radians(90.0f)) <= glm::radians(85.0f))
	{
		orientation = newOrientation;
	}
}

void SF_Virtual_camera::add_rotation_pitch(float angle_in_degree)
{
	orientation = glm::rotate(orientation, glm::radians(-angle_in_degree), up);
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

	

	//cout<<"\nMatrix = {\n";
	//cout<<"		"<<(projection * view)[0].x<<' '<<(projection * view)[0].y<<' '<<(projection * view)[0].z<<' '<<(projection * view)[0].w<<'\n';
	//cout<<"		"<<(projection * view)[1].x<<' '<<(projection * view)[1].y<<' '<<(projection * view)[1].z<<' '<<(projection * view)[1].w<<'\n';
	//cout<<"		"<<(projection * view)[2].x<<' '<<(projection * view)[2].y<<' '<<(projection * view)[2].z<<' '<<(projection * view)[2].w<<'\n';
	//cout<<"		"<<(projection * view)[3].x<<' '<<(projection * view)[3].y<<' '<<(projection * view)[3].z<<' '<<(projection * view)[3].w<<"\n\n";

	return projection * view;
}

void SF_Virtual_camera::set_camera_location(glm::vec3 _camera_position)
{
	position = _camera_position;
}

SF_Viewport_camera::SF_Viewport_camera(SF_Input * _input_class, float _fow, float _near_plane, float _far_plane) : SF_Virtual_camera(_fow, _near_plane, _far_plane), input_class(_input_class)
{
	if(!input_class)
	{
		SF_Log::message("SF_Viewport_camera", "input_class is null", SF_Message_type::error);
	}
}

SF_Viewport_camera::SF_Viewport_camera(SF_Input *_input_class) : input_class(_input_class)
{
	if(!input_class)
	{
		SF_Log::message("SF_Viewport_camera", "input_class is null", SF_Message_type::error);
	}
}

void SF_Viewport_camera::upgrade(float deltasecond)
{

	float speed = 0.1f;//for delete
	float sensitivity = 100.0f;//for delete

	if (input_class->get_mouse_button(SF_Mouse_key::MOUSE_LEFT)) 
	{
		if (first_click)
		{
			input_class->set_mouse_position(0.5f, 0.5f);
			first_click = false;
		}

		float rotX, rotY;
		input_class->get_mouse_position(rotX, rotY);
		rotX -= 0.5f; rotY -= 0.5f;
		
		add_rotation_yaw(rotY * sensitivity);
		add_rotation_pitch(rotX * sensitivity);

		input_class->set_mouse_position(0.5f, 0.5f);
	}
	else
	{
		first_click = true;
	}
	
	
	//add_location_world(-speed*orientation);

	
	if (input_class->get_key_state(SF_Key::W)) 
	{
		add_location_world(speed * orientation);
	}
	if (input_class->get_key_state(SF_Key::S))
	{
		add_location_world(-speed*orientation);
	}
	if (input_class->get_key_state(SF_Key::D))
	{
		add_location_world(speed * glm::normalize(glm::cross(orientation, up)));
	}
	if (input_class->get_key_state(SF_Key::A))
	{
		add_location_world(-speed*glm::normalize(glm::cross(orientation, up)));
	}
}
