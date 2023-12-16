#include "table.h"
#include <wx/xrc/xmlres.h>
#include <iostream>

using namespace std;




bool DBGui::OnInit()
{
    
    cout<<"\nWork\n";
	wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load("../res/UX/resource.xrc");
    wxXmlResource::Get()->LoadAllFiles("rc");


    wxFrame* frame = wxXmlResource::Get()->LoadFrame(NULL, "B_Frame-main");

    wxPanel* frame_gl = (wxPanel*)frame->FindWindowByName("B_Panel-gl_viewport");


    wxGLAttributes vAttrs;
    vAttrs.PlatformDefaults().Defaults().EndList();

    if (wxGLCanvas::IsDisplaySupported(vAttrs))
    {
        viewport_gl = new SF_Frame_gl(frame_gl, vAttrs);
    }
    frame_gl->GetSizer()->Add(viewport_gl, 1, wxEXPAND);

    

    frame->Show(true);

    return true;

}
