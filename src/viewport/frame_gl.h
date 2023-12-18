#ifndef FRAME_GL
#define FRAME_GL

#include <wx/wx.h>
#include <glad/glad.h>
#include <wx/glcanvas.h>
#include<iostream>
#include "input/input.h"
#include "camera/camera.h"

class SF_Frame_gl : public wxGLCanvas
{
public:
	SF_Frame_gl(wxWindow* parent, const wxGLAttributes& canvasAttrs);
	~SF_Frame_gl();

	void OnPaint(wxPaintEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnTimer(wxTimerEvent& event);

	bool initialize_opengl();
private:
	SF_Input * input_manager;
	void* layout;

	float deltasecond = 0.0f;

	wxGLContext* openGLContext;
	wxTimer m_timer;
	bool is_opengl_initialized{ false };

	SF_Input* input = 0x0;
	SF_Virtual_camera* camera;


	/*################################################################*/
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"uniform mat4 camera;\n"
		//"mat4 camera = mat4(1.0);\n"
		"void main()\n"
		"{\n"
		"   gl_Position = camera * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 test;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
		"}\n\0";
	GLuint VAO, VBO;
	GLuint shaderProgram;
};

#endif