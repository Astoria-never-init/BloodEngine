#ifndef SF_CAMERA_CLASS_H
#define SF_CAMERA_CLASS_H

#include <core/input/base_input.h>
#include <core/graphics/camera/base_camera.h>



class SF_Viewport_camera : public SF_Virtual_camera
{
public:
	SF_Viewport_camera(SF_Input* _input_class, float _fow, float _near_plane, float _far_plane);
	SF_Viewport_camera(SF_Input* _input_class);

	void upgrade(float deltasecond);
private:

	bool first_click = true;
	SF_Input * input_class = 0x0;

};


#endif