#include "wx_gl_viewport.h"

#include "wx_gl_viewport.h"
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <time.h>



using namespace std;

SF_Frame_gl::SF_Frame_gl(wxWindow* parent, const wxGLAttributes& canvasAttrs) : wxGLCanvas(parent, canvasAttrs)
{
	
	wxGLContextAttrs ctxAttrs;
    ctxAttrs.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();
    openGLContext = new wxGLContext(this, nullptr, &ctxAttrs);

    if (!openGLContext->IsOK())
    {
        delete openGLContext;
        openGLContext = nullptr;
    }

	layout = new SF_Wx_keyboard_layout("../res/UX/key_layout/wx_layout.xml");
	input_manager = new SF_Wx_input_manager(this, (SF_Wx_keyboard_layout*)layout);

	m_timer.SetOwner(this, wxID_ANY);
	m_timer.Start(1);

	Bind(wxEVT_PAINT, &SF_Frame_gl::OnPaint, this);
    Bind(wxEVT_SIZE, &SF_Frame_gl::OnSize, this);
	Bind(wxEVT_TIMER, &SF_Frame_gl::OnTimer, this);

}

SF_Frame_gl::~SF_Frame_gl()
{
	delete openGLContext;
}


void SF_Frame_gl::OnPaint(wxPaintEvent& event)
{
	

	wxPaintDC dc(this);
	if (!is_opengl_initialized)
	{
		return;
	}

	auto start = chrono::high_resolution_clock::now();

	if (deltasecond > 0) 
	{
		SetCurrent(*openGLContext);


		shader_program.set_mat4("camera", camera->calculate_matrix(deltasecond));
		shader_program.set_vec4("test", glm::vec4(0, 1, 0, 0.5));

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader_program.use_program();
		vao.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		SwapBuffers();
	}

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double> duration = end - start;
	deltasecond = duration.count();
}

void SF_Frame_gl::OnSize(wxSizeEvent& event)
{
	bool firstApperance = IsShownOnScreen() && !is_opengl_initialized;

    if (firstApperance)
    {
        initialize_opengl();
    }

    if (is_opengl_initialized)
    {
        auto viewPortSize = event.GetSize() * GetContentScaleFactor();
        glViewport(0, 0, viewPortSize.x, viewPortSize.y);
		camera->update_resolution(viewPortSize.x, viewPortSize.y);
    }

    event.Skip();
}

void SF_Frame_gl::OnTimer(wxTimerEvent& event)
{
	

	Refresh();
}

bool SF_Frame_gl::initialize_opengl()
{
	if (!openGLContext)
    {
        return false;
    }

    SetCurrent(*openGLContext);

	gladLoadGL();

    camera = new SF_Viewport_camera(input_manager, 90, 0.1, 1000);
	//camera->set_camera_location(glm::vec3(0, 0, -3));
	
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};
	

	SF_Shader_manager base_shader;
	base_shader.add_shader(vertexShaderSource, GL_VERTEX_SHADER);
	base_shader.add_shader(fragmentShaderSource, GL_FRAGMENT_SHADER);
	shader_program.create_shader_program(base_shader);

	vbo.init(vertices, sizeof(vertices));
	vao.init();
	vao.link_attribute(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), 0);
	

	is_opengl_initialized = true;
	return true;
}
