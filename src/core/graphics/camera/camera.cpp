#include "camera.h"
#include<glm/gtc/matrix_transform.hpp>
//#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

#include <core/logger/logger.h>


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
