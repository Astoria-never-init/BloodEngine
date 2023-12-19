#include "table.h"
#include <wx/xrc/xmlres.h>

#include <core/logger/logger.h>

DBGui::~DBGui()
{
    SF_Log::message("DBGui", "snus framework shutdown");
    SF_Log::message("", "\n");
}

bool DBGui::OnInit()
{
    SF_Log::message("DBGui", "starting snus work...");

	wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("../res/UX/resource.xrc");
    wxXmlResource::Get()->LoadAllFiles("rc");


    wxFrame* frame = wxXmlResource::Get()->LoadFrame(NULL, "B_Frame-main");

    wxPanel* frame_gl = (wxPanel*)frame->FindWindowByName("B_Panel-gl_viewport");

    SF_Log::message("DBGui", "xrc load success", SF_Message_type::success);

    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();

    if (wxGLCanvas::IsDisplaySupported(vAttrs))
    {
        viewport_gl = new SF_Frame_gl(frame_gl, vAttrs);
    }
    frame_gl->GetSizer()->Add(viewport_gl, 1, wxEXPAND);

    
    SF_Log::message("DBGui", "start GUI", SF_Message_type::success);
    frame->Show(true);

    return true;

    

}
