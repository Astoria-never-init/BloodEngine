#include "shader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include <core/logger/logger.h>

bool compile_errors(unsigned int _target, int _type)
{
    GLint has_compiled;

    switch (_type)
    {
    case GL_COMPILE_STATUS:
        glGetShaderiv(_target, _type, &has_compiled);
        break;
    case GL_LINK_STATUS:
        glGetProgramiv(_target, _type, &has_compiled);
        break;
    
    default:
        break;
    }
	
	if (!has_compiled)
	{
		char *log = new char[1024];
        GLsizei len;
		glGetShaderInfoLog(_target, 1024, &len, log);

        SF_Log::message("Shader compiler", ((_type == GL_COMPILE_STATUS) ? "Compile shader error:" : "Link shader error:"), SF_Message_type::warning);
        SF_Log::message("Shader compiler", log, SF_Message_type::warning);

		delete[] log;
		return false;
	}
	return true;
}

SF_Shader::SF_Shader(const char *_source_code, int _type)
{
    create_shader(_source_code, _type);
}

bool SF_Shader::create_shader(const char *_source_code, int _type)
{
    source_code = _source_code;
    shader = glCreateShader(_type);
    glShaderSource(shader, 1, &source_code, NULL);
    glCompileShader(shader);
    if (!compile_errors(shader, GL_COMPILE_STATUS))
	{
		return false;
	}

    is_init = true;
    return true;
}

unsigned int SF_Shader::get_shader_id()
{
    if(is_init)
    {
        return shader;
    }
    return 0;
}

void SF_Shader::destroy()
{
    if(shader != 0)
    {
        glDeleteShader(shader);
        shader = 0;
    }
}

bool SF_Shader::is_compiled()
{
    return is_init;
}

SF_Shader_manager::~SF_Shader_manager()
{
    SF_Log::message("SF_Shader_manager", "destroy shader manager");
    if(!shaders.shader)
    {
        SF_Log::message("SF_Shader_manager", "nothing targets to destroy");
        return;
    }

    shader_list * current_element = &shaders;
    while(current_element->shader)
    {

        SF_Log::int_message("SF_Shader_manager", "destroy target", current_element->shader->get_shader_id());
        current_element->shader->destroy();
        current_element = current_element->next_shader_element;
    }
}

bool SF_Shader_manager::add_shader(const char *_source_code, int _type)
{
    SF_Shader *temp = new SF_Shader(_source_code, _type);
    if(!temp->is_compiled())
    {
        delete temp;
        return false;
    }

    shader_list * current_element = &shaders;

    for(unsigned short i = 0; i < shaders_count; i++)
    {
        if(!current_element)
        {
            SF_Log::message("SF_Shader_manager", "add shader failed - next_shader_element is nullptr", SF_Message_type::error);
            delete temp;
            return false;
        }
        current_element = current_element->next_shader_element;
    }

    current_element->shader = temp;
    current_element->next_shader_element = new shader_list;
    shaders_count++;

    

    return true;
}

void SF_Shader_manager::get_shader_array(SF_Shader *&shader_array)
{
    shader_array = (SF_Shader*)malloc(shaders_count * sizeof(SF_Shader));
    
    shader_list * current_element = &shaders;

    for(unsigned short i = 0; i < shaders_count; i++)
    {
        if(!current_element)
        {
            SF_Log::message("SF_Shader_manager", "get shader array failed - next_shader_element is nullptr", SF_Message_type::error);
        }
        shader_array[i] = *current_element->shader;
        current_element = current_element->next_shader_element;
    }
}

unsigned short SF_Shader_manager::get_shader_count()
{
    return shaders_count;
}

SF_Shader_program::SF_Shader_program(SF_Shader_manager& _shaders_manager, bool delete_shaders)
{
    create_shader_program(_shaders_manager, delete_shaders);
}

SF_Shader_program::~SF_Shader_program()
{
    if(shader_program != 0)
    {
        SF_Log::message("SF_Shader_program", "Destroy program");
        glDeleteProgram(shader_program);
    }
}

unsigned int SF_Shader_program::get_location(const char *name)
{
    if(!is_init)
    {
        SF_Log::message("SF_Shader_program", "Bind attribute faliled - program is null", SF_Message_type::warning);
        return false;
    }
    return glGetUniformLocation(shader_program, name);
}

bool SF_Shader_program::bind_attribute(GLuint index, const char *name)
{
    if(!is_init)
    {
        SF_Log::message("SF_Shader_program", "Bind attribute faliled - program is null", SF_Message_type::warning);
        return false;
    }
    glBindAttribLocation(shader_program, index, name);
    return true;
}

void SF_Shader_program::set_float(const char *name, float value)
{
    glUniform1f(get_location(name), value);
}

void SF_Shader_program::set_int(const char *name, int value)
{
    glUniform1i(get_location(name), value);
}

void SF_Shader_program::set_mat4(const char *name, glm::mat4 matrix)
{
	glUniformMatrix4fv(get_location(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void SF_Shader_program::set_vec4(const char *name, glm::vec4 vec4)
{
    glUniform4f(get_location(name), vec4.x, vec4.y, vec4.z, vec4.w);
}

void SF_Shader_program::set_vec3(const char *name, glm::vec3 vec3)
{
    glUniform3f(get_location(name), vec3.x, vec3.y, vec3.z);
}

void SF_Shader_program::set_vec2(const char *name, glm::vec2 vec2)
{
    glUniform2f(get_location(name), vec2.x, vec2.y);
}

void SF_Shader_program::set_texture2D(const char *name, GLuint texture)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	get_location(name);
	glUniform1f(texture, 0);
}

bool SF_Shader_program::create_shader_program(SF_Shader_manager &_shaders_manager, bool delete_shaders)
{
    SF_Shader * shaders;

    unsigned short shader_count = _shaders_manager.get_shader_count();

    if(shader_count != 0)
    {
        _shaders_manager.get_shader_array(shaders);
        shader_program = glCreateProgram();
        for(unsigned short i = 0; i < shader_count; i++)
        {
            glAttachShader(shader_program, shaders[i].get_shader_id());
        }
        glLinkProgram(shader_program);

        if(!compile_errors(shader_program, GL_LINK_STATUS))
        {
            SF_Log::message("SF_Shader_program", "Create shader program error", SF_Message_type::warning);
            return false;
        }
        if(delete_shaders)
        {
            SF_Log::int_message("SF_Shader_program", "Destroy shaders", shader_program);
            _shaders_manager.~SF_Shader_manager();
        }
        
    }
    else
    {
        SF_Log::message("SF_Shader_program", "Target shaders is null", SF_Message_type::warning);
        return false;
    }

    SF_Log::int_message("SF_Shader_program", "Create program", shader_program, SF_Message_type::success);
    is_init = true;
    return true;
}

void SF_Shader_program::use_program()
{
    if(!is_init)
    {
        SF_Log::message("SF_Shader_program", "program is null", SF_Message_type::warning);
        return;
    }
    glUseProgram(shader_program);
}

unsigned int SF_Shader_program::get_shader_program()
{
    return shader_program;
}
