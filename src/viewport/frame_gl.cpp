#include "frame_gl.h"

#include "gui/wx_input/wx_input_class.h"
#include <glm/gtc/type_ptr.hpp>
#include <thread>
#include <time.h>

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

		glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "camera"), 1, GL_FALSE, glm::value_ptr(camera->calculate_matrix(deltasecond)));
		glUniform4f(glGetUniformLocation(shaderProgram, "test"), 0, 1, 0, 0.5);
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
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

    camera = new SF_Viewport_camera(input_manager, 80, 0.1, 1000);
	
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
	};

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	is_opengl_initialized = true;
	return true;
}
