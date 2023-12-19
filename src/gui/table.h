#ifndef DB_GUI
#define DB_GUI
#include <wx/wx.h>
#include <glad/glad.h>
#include <wx/glcanvas.h>
#include <wx/colordlg.h>
#include <core/input/wx_input.h>
#include <core/graphics/viewport/wx_gl_viewport.h>



class DBGui : public wxApp 
{
public:
    ~DBGui();

    virtual bool OnInit() override;
    SF_Frame_gl* viewport_gl {nullptr};
};


#endif