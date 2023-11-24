#ifndef DB_GUI
#define DB_GUI
#include <wx/wx.h>
#include <glad/glad.h>
#include <wx/glcanvas.h>
#include <wx/colordlg.h>






class OpenGLCanvas;
class DBGui : public wxApp 
{
public:
    virtual bool OnInit() override;
    OpenGLCanvas *openGLCanvas{nullptr};
};



class OpenGLCanvas : public wxGLCanvas
{
public:
    OpenGLCanvas(wxWindow *parent, const wxGLAttributes &canvasAttrs);
    ~OpenGLCanvas();

    bool InitializeOpenGLFunctions();
    bool InitializeOpenGL();

    void OnPaint(wxPaintEvent &event);
    void OnSize(wxSizeEvent &event);
    void OnKeyDown(wxKeyEvent& event);


private:

    

    //SF_Wx_input_manager input_manager;

    wxGLContext *openGLContext;
    bool isOpenGLInitialized{false};
};


#endif