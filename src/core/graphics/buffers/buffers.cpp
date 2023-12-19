#include "buffers.h"
#include <glad/glad.h>

#include <core/logger/logger.h>

void SF_Buffer::create()
{
    glGenBuffers(1, &buffer);
}

void SF_Buffer::bind()
{
    glBindBuffer(buffer_type, buffer);
}

void SF_Buffer::unbind()
{
    glBindBuffer(buffer_type, 0);
}

void SF_Buffer::destroy()
{
    glDeleteBuffers(1, &buffer);
}

unsigned int SF_Buffer::get_id()
{
    return buffer;
}

SF_Ebo_buffer::SF_Ebo_buffer() : SF_Buffer(GL_ELEMENT_ARRAY_BUFFER)
{
}

SF_Ebo_buffer::SF_Ebo_buffer(unsigned int *_indices, unsigned long _count) : SF_Buffer(GL_ELEMENT_ARRAY_BUFFER)
{
    init(_indices, _count);
}

void SF_Ebo_buffer::init(unsigned int *_indices, unsigned long _count)
{
   	create();
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _count * sizeof(unsigned int), _indices, GL_STATIC_DRAW);
}

SF_Vbo_buffer::SF_Vbo_buffer() : SF_Buffer(GL_ARRAY_BUFFER)
{
    
}

SF_Vbo_buffer::SF_Vbo_buffer(void *_data, unsigned long _size) : SF_Buffer(GL_ARRAY_BUFFER)
{
}

void SF_Vbo_buffer::init(void *_data, unsigned long _size)
{
    create();
	bind();
	glBufferData(buffer_type, _size, _data, GL_STATIC_DRAW);
    unbind();

}

SF_Vao_buffer::SF_Vao_buffer() : SF_Buffer()
{
}

void SF_Vao_buffer::link_attribute(SF_Vbo_buffer &_vbo, unsigned int _layout, unsigned int _num_components, unsigned int _type, signed long _stride, void *_offset)
{
    bind();
    _vbo.bind();
    glVertexAttribPointer(_layout, _num_components, _type, GL_FALSE, _stride, _offset);
	glEnableVertexAttribArray(_layout);
    unbind();
    _vbo.unbind();
}

void SF_Vao_buffer::bind()
{
    glBindVertexArray(buffer);
}

void SF_Vao_buffer::unbind()
{
    glBindVertexArray(0);
}

void SF_Vao_buffer::destroy()
{
    glDeleteVertexArrays(1, &buffer);
}

void SF_Vao_buffer::create()
{
    glGenVertexArrays(1, &buffer);
}

SF_Rbo_buffer::SF_Rbo_buffer() : SF_Buffer(GL_RENDERBUFFER)
{
}

void SF_Rbo_buffer::bind()
{
    glBindRenderbuffer(buffer_type, buffer);
}

void SF_Rbo_buffer::unbind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void SF_Rbo_buffer::destroy()
{
    glDeleteRenderbuffers(1, &buffer);
}

void SF_Rbo_buffer::create()
{
    glGenRenderbuffers(1, &buffer);
}

SF_Ssbo_buffer::SF_Ssbo_buffer() : SF_Buffer(GL_SHADER_STORAGE_BUFFER)
{
}

SF_Ssbo_buffer::SF_Ssbo_buffer(unsigned int _shader_binding_layout, void *_data, unsigned long _size) : SF_Buffer(GL_SHADER_STORAGE_BUFFER)
{
    init(_shader_binding_layout, _data, _size);
}

void SF_Ssbo_buffer::init(unsigned int _shader_binding_layout, void *_data, unsigned long _size)
{
    create();
    bind();
	glBufferData(buffer_type, _size, _data, GL_STATIC_DRAW);
	glBindBufferBase(buffer_type, _shader_binding_layout, buffer);
    unbind();
}
