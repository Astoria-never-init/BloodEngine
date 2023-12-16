#ifndef DB_GUI
#define DB_GUI
#include <wx/wx.h>
#include <glad/glad.h>
#include <wx/glcanvas.h>
#include <wx/colordlg.h>
#include "wx_input/wx_input_class.h"
#include "viewport/frame_gl.h"



class DBGui : public wxApp 
{
public:
    virtual bool OnInit() override;
    SF_Frame_gl* viewport_gl {nullptr};
};


#endif