#ifndef SF_BUFFESR_CLASS_H
#define SF_BUFFESR_CLASS_H

class SF_Buffer
{
public:
    SF_Buffer(unsigned int _buffer_type) : buffer_type(_buffer_type){}
	SF_Buffer(){}
	
	virtual void bind();
	virtual void unbind();
	virtual void destroy();

	unsigned int get_id();
protected:
	virtual void create();

    unsigned int buffer_type = 0;
	unsigned int buffer = 0;
};

class SF_Ebo_buffer : public SF_Buffer
{
public:

	SF_Ebo_buffer();
	SF_Ebo_buffer(unsigned int* _indices, unsigned long _count);

	void init(unsigned int* _indices, unsigned long _count);

};

class SF_Vbo_buffer : public SF_Buffer
{
public:

	SF_Vbo_buffer();
	SF_Vbo_buffer(void* _data, unsigned long _size);

	void init(void* _data, unsigned long _size);
	
};

class SF_Vao_buffer : public SF_Buffer
{
public:

	SF_Vao_buffer();
	void link_attribute(SF_Vbo_buffer& _vbo, unsigned int _layout, unsigned int _num_components, unsigned int _type, signed long _stride, void* _offset);

	void init() { create(); }

	void bind() override;
	void unbind() override;
	void destroy() override;

private:
	void create() override;
	
};

class SF_Rbo_buffer : public SF_Buffer
{
public:

	SF_Rbo_buffer();

	void init() { create(); }

	void bind() override;
	void unbind() override;
	void destroy() override;

private:
	void create() override;
	
};

class SF_Ssbo_buffer : public SF_Buffer
{
public:

	SF_Ssbo_buffer();
	SF_Ssbo_buffer(unsigned int _shader_binding_layout, void *_data, unsigned long _size);

	void init(unsigned int _shader_binding_layout, void *_data, unsigned long _size);

};


#endif