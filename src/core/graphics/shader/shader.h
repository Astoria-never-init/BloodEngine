#ifndef SF_SHADER_CLASS_H
#define SF_SHADER_CLASS_H

#include <glm/glm.hpp>

class SF_Shader
{
public:
	SF_Shader(const char* _source_code, int _type);
    SF_Shader(){}

	bool create_shader(const char* _source_code, int _type);
    bool is_compiled();
    unsigned int get_shader_id();
    void destroy();

private:
    unsigned int shader = 0;
    const char* source_code = 0x0;
    bool is_init = false;
};

class SF_Shader_manager
{
public:
    ~SF_Shader_manager();

    bool add_shader(const char* _source_code, int _type);
    void get_shader_array(SF_Shader *& shader_array);
    unsigned short get_shader_count();
private:

    
    struct shader_list
    {
        SF_Shader *shader = 0x0;
        shader_list *next_shader_element = 0x0;
    };

    shader_list shaders;
    unsigned short shaders_count = 0;
};

class SF_Shader_program
{
public:
	SF_Shader_program(SF_Shader_manager& _shaders_manager, bool delete_shaders_after_compile = false);
    SF_Shader_program(){}
    ~SF_Shader_program();

    unsigned int get_location(const char* name);
    bool bind_attribute(unsigned int index, const char* name);
    void set_float(const char* name, float value);
	void set_int(const char* name, int value);
	void set_mat4(const char* name, glm::mat4 matrix);
	void set_vec4(const char* name, glm::vec4 vec4);
	void set_vec3(const char* name, glm::vec3 vec3);
	void set_vec2(const char* name, glm::vec2 vec2);
    void set_texture2D(const char* name, unsigned int texture);

	bool create_shader_program(SF_Shader_manager& _shaders_manager, bool delete_shaders_after_compile = false);
    void use_program();
    unsigned int get_shader_program();

private:
    unsigned int shader_program = 0;
    const char* source_code = 0x0;
    bool is_init = false;
};

#endif