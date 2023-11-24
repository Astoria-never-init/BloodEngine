#include "wx_input_class.h"

SF_Wx_input_manager::SF_Wx_input_manager(wxWindow * window) : SF_Input()
{
    //key_layout = new key_remap[key_lenght];

    window->Bind(wxEVT_KEY_DOWN, &SF_Wx_input_manager::OnKeyDown, this);
}

void SF_Wx_input_manager::OnKeyDown(wxKeyEvent& event)
{
    int keycode = event.GetKeyCode();

    event.Skip();
}
